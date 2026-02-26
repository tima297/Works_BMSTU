import java.util.*;

/**
 * Сама заправка - здесь есть колонки, очередь, бензовозы
 */
public class GasStation {
    private List<FuelPump> pumps;        // Все колонки
    private Queue<Car> queue;             // Очередь машин
    private double fuelReserve;           // Сколько топлива осталось
    private double maxFuelCapacity;       // Максимум топлива
    private double lastDeliveryTime;      // Когда последний раз привозили
    private double deliveryInterval;      // Как часто привозят
    private double deliveryVolume;        // Сколько привозят
    private double deliveryDuration;      // Сколько времени занимает доставка

    // Для расширения заправки (добавления новых колонок)
    private boolean expansionScheduled;   // Запланировано ли открытие
    private double lastExpansionTriggerTime; // Когда в последний раз проверяли условие
    private int totalExpansions;          // Сколько всего открыли новых колонок
    private double queueThreshold;        // Порог очереди (когда открывать)
    private double expansionDelay;        // Задержка между открытиями
    private int maxPumps;                 // Максимум колонок

    public GasStation() {
        // Создаем начальные колонки
        pumps = new ArrayList<>();
        for (int i = 0; i < Config.INITIAL_PUMPS; i++) {
            pumps.add(new FuelPump(Config.DEFAULT_FLOW_RATE, 0));
        }

        queue = new LinkedList<>();
        fuelReserve = Config.INITIAL_FUEL;
        maxFuelCapacity = Config.MAX_FUEL_CAPACITY;
        lastDeliveryTime = 0;
        deliveryInterval = Config.DELIVERY_INTERVAL;
        deliveryVolume = Config.DELIVERY_VOLUME;
        deliveryDuration = Config.DELIVERY_DURATION;

        expansionScheduled = false;
        lastExpansionTriggerTime = -1;
        totalExpansions = 0;
        queueThreshold = Config.QUEUE_THRESHOLD;
        expansionDelay = Config.EXPANSION_DELAY;
        maxPumps = Config.MAX_PUMPS;
    }

    /**
     * Найти свободную колонку
     */
    public FuelPump findFreePump() {
        for (FuelPump p : pumps) {
            if (!p.isBusy()) return p;
        }
        return null;
    }

    /**
     * Попробовать начать заправку
     */
    public boolean tryStartService(FuelPump pump, Car car, double currentTime) {
        if (fuelReserve < car.getDesiredFuel()) return false; // Не хватает топлива
        pump.serve(car, currentTime);
        return true;
    }

    /**
     * Завершить заправку
     */
    public void completeService(FuelPump pump, double currentTime) {
        Car car = pump.getCurrentCar();
        if (car != null) {
            fuelReserve -= car.getDesiredFuel(); // Списываем топливо
            pump.release(currentTime);
        }
    }

    /**
     * Добавить машину в очередь
     */
    public void addCarToQueue(Car car) {
        queue.add(car);
    }

    /**
     * Взять следующую машину из очереди
     */
    public Car getNextCarFromQueue() {
        return queue.poll();
    }

    /**
     * Посмотреть первую машину (не удаляя её)
     */
    public Car peekNextCar() {
        return queue.peek();
    }

    public int getQueueSize() {
        return queue.size();
    }

    /**
     * Хватит ли топлива?
     */
    public boolean hasEnoughFuel(double desiredFuel) {
        return fuelReserve >= desiredFuel;
    }

    /**
     * Проверить, нужно ли открывать новую колонку
     */
    public boolean checkExpansionCondition(double waitTime, double currentTime) {
        if (waitTime > queueThreshold && !expansionScheduled &&
                pumps.size() < maxPumps &&
                (lastExpansionTriggerTime < 0 || currentTime - lastExpansionTriggerTime > expansionDelay)) {

            expansionScheduled = true;
            lastExpansionTriggerTime = currentTime;
            return true;
        }
        return false;
    }

    /**
     * Можно ли проверять условие расширения?
     */
    public boolean shouldCheckExpansion() {
        return !expansionScheduled && pumps.size() < maxPumps;
    }

    /**
     * Добавить новую колонку
     */
    public void addNewPump(double currentTime) {
        if (pumps.size() < maxPumps) {
            int day = (int)(currentTime / (24 * 60)); // На какой день открыли
            pumps.add(new FuelPump(Config.DEFAULT_FLOW_RATE, day));
            totalExpansions++;
            expansionScheduled = false; // Можно снова планировать
        }
    }

    /**
     * Принять доставку топлива
     */
    public void deliverFuel(double currentTime) {
        fuelReserve = Math.min(fuelReserve + deliveryVolume, maxFuelCapacity);
        lastDeliveryTime = currentTime;
    }

    // Геттеры
    public List<FuelPump> getPumps() { return pumps; }
    public Queue<Car> getQueue() { return queue; }
    public double getFuelReserve() { return fuelReserve; }
    public double getDeliveryInterval() { return deliveryInterval; }
    public int getTotalExpansions() { return totalExpansions; }
    public int getPumpCount() { return pumps.size(); }
    public double getQueueThreshold() { return queueThreshold; }
    public double getExpansionDelay() { return expansionDelay; }
    public int getMaxPumps() { return maxPumps; }
}