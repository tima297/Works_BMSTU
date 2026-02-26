import java.util.*;

/**
 * Сбор и отображение статистики работы заправки
 * Считает всё, что нужно для отчёта
 */
public class Statistics {
    private int totalArrived;        // Сколько машин приехало
    private int totalServed;          // Сколько обслужили
    private int totalRefusals;        // Сколько отказали (нет топлива)
    private double totalWaitTime;     // Общее время ожидания
    private double maxWaitTime;       // Максимальное ожидание
    private double totalServiceTime;  // Общее время заправки
    private int maxQueueLength;       // Самая длинная очередь
    private List<Double> fuelLevels;  // Уровни топлива (для среднего)
    private double minFuelReserve;    // Минимальный остаток топлива
    private int totalDeliveries;      // Сколько доставок было

    public Statistics() {
        totalArrived = 0;
        totalServed = 0;
        totalRefusals = 0;
        totalWaitTime = 0;
        maxWaitTime = 0;
        totalServiceTime = 0;
        maxQueueLength = 0;
        fuelLevels = new ArrayList<>();
        minFuelReserve = Double.MAX_VALUE;
        totalDeliveries = 0;
    }

    // Простые методы для записи событий
    public void recordArrival() { totalArrived++; }
    public void recordRefusal() { totalRefusals++; }
    public void recordDelivery() { totalDeliveries++; }

    /**
     * Записать информацию обслуженной машины
     */
    public void recordService(Car car) {
        totalServed++;
        double wait = car.getWaitTime();
        totalWaitTime += wait;
        maxWaitTime = Math.max(maxWaitTime, wait);
        totalServiceTime += car.getServiceTime();
    }

    /**
     * Обновить максимальную длину очереди
     */
    public void updateQueueLength(int queueSize, double currentTime) {
        maxQueueLength = Math.max(maxQueueLength, queueSize);
    }

    /**
     * Записать уровень топлива в определённый момент
     */
    public void recordFuelLevel(double fuelLevel, double currentTime) {
        fuelLevels.add(fuelLevel);
        minFuelReserve = Math.min(minFuelReserve, fuelLevel);
    }

    /**
     * Посчитать среднее время ожидания
     */
    public double getAverageWaitTime() {
        return totalServed > 0 ? totalWaitTime / totalServed : 0;
    }

    /**
     * Посчитать средний уровень топлива
     */
    public double getAverageFuelLevel() {
        double sum = 0;
        for (double f : fuelLevels) sum += f;
        return fuelLevels.isEmpty() ? 0 : sum / fuelLevels.size();
    }

    /**
     * Напечатать красивый отчёт
     */
    public void printReport(GasStation gs, double endTime) {
        System.out.println("\n=== РЕЗУЛЬТАТЫ СИМУЛЯЦИИ АЗС (" + Config.SIMULATION_DAYS + " дней) ===\n");
        System.out.println("Прибыло автомобилей: " + totalArrived);
        System.out.println("Обслужено: " + totalServed);
        System.out.println("Отказов (нет топлива): " + totalRefusals);
        System.out.printf("Ср. ожидание в очереди: %.2f мин\n", getAverageWaitTime());
        System.out.printf("Макс. ожидание: %.2f мин\n", maxWaitTime);
        System.out.println("Макс. длина очереди: " + maxQueueLength);
        System.out.println("Колонок в начале: " + Config.INITIAL_PUMPS);
        System.out.println("Колонок в конце: " + gs.getPumpCount() +
                " (+" + gs.getTotalExpansions() + " открыто)");
        System.out.println("Доставок топлива: " + totalDeliveries);
        System.out.printf("Ср. остаток топлива: %.0f л\n", getAverageFuelLevel());
        System.out.printf("Мин. остаток топлива: %.0f л\n", minFuelReserve);

        System.out.print("Загрузка колонок: ");
        for (FuelPump p : gs.getPumps()) {
            System.out.printf("#%d: %.0f%% ", p.getId(), (p.getTotalWorkTime() / endTime) * 100);
        }
        System.out.println();
    }
}