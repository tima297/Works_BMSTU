#include <iostream>
#include <string>
using namespace std;

struct Employee {
    string name;
    int age;
    string position;
    int salary;
};

int main() {
    setlocale(LC_ALL, "Russian");
    int n;
    cout << "Введите количество сотрудников: ";
    cin >> n;

    Employee employees[100]; // Простой массив, не динамический
    double totalSalary = 0;

    // Ввод данных
    for (int i = 0; i < n; i++) {
        cout << "\nСотрудник " << i + 1 << ":\n";
        cout << "Имя: ";
        cin >> employees[i].name;
        cout << "Возраст: ";
        cin >> employees[i].age;
        cout << "Должность: ";
        cin >> employees[i].position;
        cout << "Зарплата: ";
        cin >> employees[i].salary;
        totalSalary += employees[i].salary;
    }

    // Поиск самого молодого и старшего
    int youngest = 0, oldest = 0;
    for (int i = 1; i < n; i++) {
        if (employees[i].age < employees[youngest].age) youngest = i;
        if (employees[i].age > employees[oldest].age) oldest = i;
    }

    // Вывод результатов
    cout << "\nРезультаты:\n";
    cout << "Самый молодой: " << employees[youngest].name
        << ", возраст: " << employees[youngest].age
        << ", должность: " << employees[youngest].position
        << ", зарплата: " << employees[youngest].salary << endl;

    cout << "Самый старший: " << employees[oldest].name
        << ", возраст: " << employees[oldest].age
        << ", должность: " << employees[oldest].position
        << ", зарплата: " << employees[oldest].salary << endl;

    cout << "Средняя зарплата: " << totalSalary / n << endl;

    return 0;
}