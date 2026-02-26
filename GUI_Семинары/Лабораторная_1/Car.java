
public class Car {
    private static int nextId = 1;  // Для нумерации машин

    private int id;                 // Номер машины
    private double tankCapacity;    // Объем бака
    private double fuelLevel;       // Сколько топлива сейчас
    private double desiredFuel;     // Сколько хочет залить
    private double arrivalTime;     // Когда приехала
    private double startServiceTime; // Когда начала заправляться
    private double endServiceTime;   // Когда закончила

    public Car(double arrivalTime) {
        this.id = nextId++;
        this.arrivalTime = arrivalTime;

        // Разные машины - разный объем бака (40,50,60,70,80 литров)
        int[] caps = {40, 50, 60, 70, 80};
        tankCapacity = caps[(int)(Math.random() * caps.length)];

        // В баке осталось от 10% до 90% топлива
        fuelLevel = tankCapacity * (0.1 + Math.random() * 0.8);

        // Сколько нужно долить
        desiredFuel = tankCapacity - fuelLevel;

        // Обычно не заливают полный бак, а меньше
        if (desiredFuel > 5) {
            desiredFuel = 5 + Math.random() * (desiredFuel - 5);
        }
    }

    // Запомнить время начала и конца заправки
    public void startService(double time) { startServiceTime = time; }
    public void endService(double time) { endServiceTime = time; }

    // Сколько ждала в очереди и сколько заправлялась
    public double getWaitTime() { return startServiceTime - arrivalTime; }
    public double getServiceTime() { return endServiceTime - startServiceTime; }

    // Геттеры
    public int getId() { return id; }
    public double getDesiredFuel() { return desiredFuel; }
    public double getArrivalTime() { return arrivalTime; }
}