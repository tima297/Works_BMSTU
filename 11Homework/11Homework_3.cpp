#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

// Структура заказа
struct Order {
    string customerName;
    vector<string> items;
};

// Функция добавления заказа
void addOrder(queue<Order>& orders, const Order& order) {
    orders.push(order);
    cout << "Добавлен заказ от: " << order.customerName << endl;
}

// Функция обработки заказа
void processOrder(queue<Order>& orders) {
    if (orders.empty()) {
        cout << "Заказов нет\n";
        return;
    }

    Order current = orders.front();

    cout << "\n=== Обработка заказа ===\n";
    cout << "Клиент: " << current.customerName << endl;
    cout << "Товары: ";

    for (size_t i = 0; i < current.items.size(); i++) {
        cout << current.items[i];
        if (i < current.items.size() - 1) cout << ", ";
    }
    cout << "\nЗаказ выполнен!\n";

    orders.pop();
}

int main() {
    setlocale(LC_ALL, "Russian");
    queue<Order> ordersQueue;

    cout << "=== Обработка заказов ===\n\n";

    Order order1;
    order1.customerName = "Иван Петров";
    order1.items = { "Ноутбук", "Мышка" };

    Order order2;
    order2.customerName = "Мария Сидорова";
    order2.items = { "Телефон", "Чехол", "Наушники" };

    Order order3;
    order3.customerName = "Алексей Иванов";
    order3.items = { "Книга" };

    addOrder(ordersQueue, order1);
    addOrder(ordersQueue, order2);
    addOrder(ordersQueue, order3);

    cout << "\nВсего заказов: " << ordersQueue.size() << "\n\n";

    while (!ordersQueue.empty()) {
        processOrder(ordersQueue);
        cout << "Осталось заказов: " << ordersQueue.size() << "\n\n";
    }

    return 0;
}
