import java.util.PriorityQueue;
import java.util.Random;

/**
 * Главный класс симуляции - здесь всё происходит
 */
public class Simulation {
    private PriorityQueue<Event> events;  // Очередь событий (всегда отсортирована по времени)
    private GasStation gasStation;         // Наша заправка
    private CarGenerator carGenerator;     // Генератор машин
    private Statistics stats;              // Статистика
    private double currentTime;            // Текущее время в симуляции
    private double endTime;                // Когда закончить

    public Simulation() {
        events = new PriorityQueue<>();
        gasStation = new GasStation();
        carGenerator = new CarGenerator(new Random().nextInt());
        stats = new Statistics();
        currentTime = 0;
        endTime = Config.SIMULATION_END_TIME;
    }

    /**
     * Запустить симуляцию
     */
    public void run() {
        // Планируем первую машину и первую поставку топлива
        events.add(new Event(Event.EventType.CAR_ARRIVAL, carGenerator.generateNextArrival(0)));
        events.add(new Event(Event.EventType.FUEL_DELIVERY, gasStation.getDeliveryInterval()));

        // Главный цикл - пока есть события и не вышли за время
        while (!events.isEmpty() && currentTime < endTime) {
            Event e = events.poll();  // Берём самое ближайшее событие
            currentTime = e.getTime();

            if (currentTime > endTime) break;

            // Обрабатываем событие в зависимости от его типа
            switch (e.getType()) {
                case CAR_ARRIVAL: processArrival(e); break;
                case SERVICE_END: processServiceEnd(e); break;
                case FUEL_DELIVERY: processDelivery(e); break;
                case PUMP_OPEN: processPumpOpen(e); break;
            }

            // Собираем статистику
            stats.updateQueueLength(gasStation.getQueueSize(), currentTime);

            // Каждый час записываем уровень топлива
            if (currentTime % 60 < 1) {
                stats.recordFuelLevel(gasStation.getFuelReserve(), currentTime);
            }
        }

        // Печатаем отчёт
        stats.printReport(gasStation, currentTime);
    }

    /**
     * Обработка приезда машины
     */
    private void processArrival(Event e) {
        Car car = carGenerator.generateCar(currentTime);
        stats.recordArrival();

        // Проверяем, хватит ли топлива
        if (!gasStation.hasEnoughFuel(car.getDesiredFuel())) {
            stats.recordRefusal(); // Не хватило - отказ
        } else {
            FuelPump pump = gasStation.findFreePump();

            if (pump != null) {
                // Есть свободная колонка - сразу заправляем
                double serviceTime = pump.serve(car, currentTime);
                stats.recordService(car);
                events.add(new Event(Event.EventType.SERVICE_END,
                        currentTime + serviceTime, pump));
            } else {
                // Все колонки заняты - в очередь
                gasStation.addCarToQueue(car);
            }
        }

        // Планируем следующую машину
        double nextArrival = carGenerator.generateNextArrival(currentTime);
        if (nextArrival < endTime) {
            events.add(new Event(Event.EventType.CAR_ARRIVAL, nextArrival));
        }
    }

    /**
     * Обработка окончания заправки
     */
    private void processServiceEnd(Event e) {
        FuelPump pump = (FuelPump) e.getData();
        gasStation.completeService(pump, currentTime);

        // Если есть очередь - берём следующую машину
        if (!gasStation.getQueue().isEmpty()) {
            Car nextCar = gasStation.getNextCarFromQueue();
            double waitTime = currentTime - nextCar.getArrivalTime();

            // Проверяем, не пора ли открыть новую колонку
            if (gasStation.checkExpansionCondition(waitTime, currentTime)) {
                schedulePumpOpening(currentTime);
            }

            // Если хватает топлива - заправляем
            if (gasStation.hasEnoughFuel(nextCar.getDesiredFuel())) {
                double serviceTime = pump.serve(nextCar, currentTime);
                stats.recordService(nextCar);
                events.add(new Event(Event.EventType.SERVICE_END,
                        currentTime + serviceTime, pump));
            } else {
                stats.recordRefusal();
            }
        }

        // Ещё раз проверяем условие для первой машины в очереди
        if (!gasStation.getQueue().isEmpty() && gasStation.shouldCheckExpansion()) {
            Car firstInQueue = gasStation.peekNextCar();
            if (firstInQueue != null) {
                double waitTime = currentTime - firstInQueue.getArrivalTime();
                if (gasStation.checkExpansionCondition(waitTime, currentTime)) {
                    schedulePumpOpening(currentTime);
                }
            }
        }
    }

    /**
     * Обработка доставки топлива
     */
    private void processDelivery(Event e) {
        gasStation.deliverFuel(currentTime);
        stats.recordDelivery();
        stats.recordFuelLevel(gasStation.getFuelReserve(), currentTime);

        // Планируем следующую доставку
        double nextDelivery = currentTime + gasStation.getDeliveryInterval();
        if (nextDelivery < endTime) {
            events.add(new Event(Event.EventType.FUEL_DELIVERY, nextDelivery));
        }
    }

    /**
     * Обработка открытия новой колонки
     */
    private void processPumpOpen(Event e) {
        gasStation.addNewPump(currentTime);
        System.out.printf("[t=%.2f] ОТКРЫТА НОВАЯ КОЛОНКА! Всего колонок: %d\n",
                currentTime, gasStation.getPumpCount());

        // Если есть очередь - сразу начинаем обслуживать
        if (!gasStation.getQueue().isEmpty()) {
            FuelPump newPump = gasStation.findFreePump();
            if (newPump != null) {
                Car car = gasStation.getNextCarFromQueue();
                if (gasStation.hasEnoughFuel(car.getDesiredFuel())) {
                    double serviceTime = newPump.serve(car, currentTime);
                    stats.recordService(car);
                    events.add(new Event(Event.EventType.SERVICE_END,
                            currentTime + serviceTime, newPump));
                } else {
                    stats.recordRefusal();
                }
            }
        }
    }

    /**
     * Запланировать открытие новой колонки через некоторое время
     */
    private void schedulePumpOpening(double currentTime) {
        double openTime = currentTime + Config.EXPANSION_DELAY;
        if (openTime < endTime && gasStation.getPumpCount() < Config.MAX_PUMPS) {
            events.add(new Event(Event.EventType.PUMP_OPEN, openTime));
            System.out.printf("[t=%.2f] ЗАПЛАНИРОВАНО открытие новой колонки на t=%.2f\n",
                    currentTime, openTime);
        }
    }

    public static void main(String[] args) {
        Simulation sim = new Simulation();
        sim.run();
    }
}