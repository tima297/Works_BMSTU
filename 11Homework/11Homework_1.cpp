#include <iostream>
#include <queue>
#include <string>
using namespace std;

// Функция добавления человека в очередь
void addToQueue(queue<string>& q, const string& person) {
    q.push(person);
    cout << person << " встал(а) в очередь.\n";
}

// Функция обработки человека из очереди
void processQueue(queue<string>& q) {
    if (q.empty()) {
        cout << "Очередь пуста!\n";
        return;
    }

    cout << q.front() << " обслужен(а).\n";
    q.pop();
}

int main() {
    queue<string> supermarketQueue;

    cout << "=== Очередь в магазине ===\n\n";

    addToQueue(supermarketQueue, "Анна");
    addToQueue(supermarketQueue, "Иван");
    addToQueue(supermarketQueue, "Мария");

    cout << "\nВ очереди: " << supermarketQueue.size() << " человек(а)\n\n";

    while (!supermarketQueue.empty()) {
        processQueue(supermarketQueue);
        cout << "Осталось: " << supermarketQueue.size() << " человек(а)\n\n";
    }

    processQueue(supermarketQueue);

    return 0;
}

