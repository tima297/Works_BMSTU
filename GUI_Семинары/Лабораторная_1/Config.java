import java.util.HashMap;
import java.util.Map;


public class Config {
    // Сколько дней будет работать заправка
    public static final int SIMULATION_DAYS = 7;
    // Это то же самое, но в минутах (7 дней * 24 часа * 60 минут)
    public static final double SIMULATION_END_TIME = SIMULATION_DAYS * 24 * 60;

    // Сколько колонок сначала и сколько можно добавить максимум
    public static final int INITIAL_PUMPS = 2;
    public static final int MAX_PUMPS = 10;
    // Скорость заправки (литров в минуту)
    public static final double DEFAULT_FLOW_RATE = 20.0;

    // Если очередь больше 12 минут, думаем о новой колонке
    public static final double QUEUE_THRESHOLD = 12.0;
    // Между открытием новых колонок должно пройти 2 дня
    public static final double EXPANSION_DELAY = 2 * 24 * 60;

    // Сколько топлива сначала и максимум
    public static final double INITIAL_FUEL = 10000.0;
    public static final double MAX_FUEL_CAPACITY = 10000.0;
    // Доставка топлива каждые 12 часов по 7000 литров
    public static final double DELIVERY_INTERVAL = 12 * 60;
    public static final double DELIVERY_VOLUME = 7000.0;
    public static final double DELIVERY_DURATION = 30.0;




    // Сколько машин приезжает в разное время суток
    public static final Map<Integer, Double> LAMBDA_BY_HOUR = new HashMap<>();
    static {
        for (int i = 0; i < 24; i++) {
            if (i >= 0 && i <= 5) LAMBDA_BY_HOUR.put(i, 0.03);   // Ночью - редко
            else if (i >= 6 && i <= 9) LAMBDA_BY_HOUR.put(i, 0.3); // Утром - много
            else if (i >= 10 && i <= 15) LAMBDA_BY_HOUR.put(i, 0.1); // Днем - средне
            else if (i >= 16 && i <= 19) LAMBDA_BY_HOUR.put(i, 0.5); // Вечером - пик
            else LAMBDA_BY_HOUR.put(i, 0.08); // Поздно вечером - мало
        }
    }
}