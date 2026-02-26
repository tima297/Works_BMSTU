import java.util.Random;

/**
 * Генератор машин - создает новые машины и считает, когда следующая приедет
 */
public class CarGenerator {
    private Random random;              // Генератор случайных чисел
    private int totalCarsGenerated;     // Сколько всего машин создали

    public CarGenerator(int seed) {
        this.random = new Random(seed);
        this.totalCarsGenerated = 0;
    }

    /**
     * Посчитать, когда приедет следующая машина
     * Используется экспоненциальное распределение
     */
    public double generateNextArrival(double currentTime) {
        // Определяем час дня (0-23), чтобы знать интенсивность
        int hour = (int)((currentTime % (24 * 60)) / 60);
        double lambda = Config.LAMBDA_BY_HOUR.get(hour);

        // Формула для экспоненциального распределения
        double u = random.nextDouble();
        if (u == 0) u = 0.000001; // Защита от деления на ноль

        return currentTime - Math.log(u) / lambda;
    }

    /**
     * Создать новую машину
     */
    public Car generateCar(double arrivalTime) {
        totalCarsGenerated++;
        return new Car(arrivalTime);
    }

    public int getTotalCarsGenerated() { return totalCarsGenerated; }
}