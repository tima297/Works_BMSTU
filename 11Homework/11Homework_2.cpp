#include <iostream>
#include <queue>
#include <string>
using namespace std;

// Функция добавления события
void addEvent(queue<string>& events, const string& event) {
    events.push(event);
    cout << "Добавлено: " << event << endl;
}

// Функция обработки событий
void processEvents(queue<string>& events) {
    if (events.empty()) {
        cout << "Событий нет\n";
        return;
    }

    cout << "Обрабатывается: " << events.front() << endl;
    events.pop();
}

int main() {
    setlocale(LC_ALL, "Russian");
    queue<string> networkEvents;

    cout << "=== Обработка сетевых событий ===\n\n";

    addEvent(networkEvents, "GET /api/users");
    addEvent(networkEvents, "POST /api/login");
    addEvent(networkEvents, "DELETE /api/item/123");

    cout << "\nВсего событий: " << networkEvents.size() << "\n\n";

    // Обрабатываем события
    while (!networkEvents.empty()) {
        processEvents(networkEvents);
        cout << "Осталось событий: " << networkEvents.size() << "\n\n";
    }

    return 0;
}
