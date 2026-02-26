
public class FuelPump {
    private static int nextId = 1;  // Для нумерации колонок

    private int id;                 // Номер колонки
    private double flowRate;        // Скорость подачи топлива
    private boolean busy;           // Занята или свободна
    private Car currentCar;         // Какая машина сейчас заправляется
    private double totalWorkTime;   // Сколько всего проработала (для статистики)
    private double lastStartTime;   // Когда начали заправлять последнюю машину
    private int openedAtDay;        // На какой день открыли колонку

    public FuelPump(double flowRate, int openedAtDay) {
        this.id = nextId++;
        this.flowRate = flowRate;
        this.busy = false;
        this.currentCar = null;
        this.totalWorkTime = 0;
        this.lastStartTime = 0;
        this.openedAtDay = openedAtDay;
    }

    public double serve(Car car, double currentTime) {
        busy = true;
        currentCar = car;
        lastStartTime = currentTime;
        car.startService(currentTime);

        // Сколько нужно времени по формуле (объем / скорость)
        double baseServiceTime = car.getDesiredFuel() / flowRate;

        // Добавляем случайное время на оплату и прочее (от 0 до 5 минут)
        double randomDelay = Math.random() * 6.0;

        double serviceTime = baseServiceTime + randomDelay;
        car.endService(currentTime + serviceTime);
        return serviceTime;
    }

    /**
     * Освободить колонку (машина уехала)
     */
    public void release(double currentTime) {
        totalWorkTime += currentTime - lastStartTime;  // Добавляем время работы
        busy = false;
        currentCar = null;
    }

    // Простые геттеры
    public int getId() { return id; }
    public boolean isBusy() { return busy; }
    public Car getCurrentCar() { return currentCar; }
    public double getTotalWorkTime() { return totalWorkTime; }
}