public class Event implements Comparable<Event> {

    // Типы событий, которые могут происходить
    public enum EventType {
        CAR_ARRIVAL,    // Машина приехала
        SERVICE_END,    // Машина заправилась
        FUEL_DELIVERY,  // Привезли топливо
        PUMP_OPEN       // Открыли новую колонку
    }

    private EventType type;  // Что случилось
    private double time;      // Когда случилось
    private Object data;      // Дополнительная информация (например, какая колонка освободилась)

    public Event(EventType type, double time) {
        this(type, time, null);
    }

    public Event(EventType type, double time, Object data) {
        this.type = type;
        this.time = time;
        this.data = data;
    }

    // Нужно для сортировки - чтобы события обрабатывались по порядку
    public int compareTo(Event other) {
        return Double.compare(this.time, other.time);
    }

    // Простые методы для получения данных
    public EventType getType() { return type; }
    public double getTime() { return time; }
    public Object getData() { return data; }
}