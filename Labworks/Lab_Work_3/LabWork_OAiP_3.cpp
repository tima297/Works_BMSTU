#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;
struct Product {
	string name;
	double price;
	int quantity;
};

// Функция чтения продуктов из файла
vector<Product> readProducts() {
    vector<Product> products; // создаем пустой вектор для продуктов
    ifstream file("products.txt"); // открываем файл для чтения

    // если файл не открылся, возвращаем пустой вектор
    if (!file) return products;

    string line;
    getline(file, line); // читаем первую строку (заголовок) и пропускаем её

    // читаем файл построчно до конца
    while (getline(file, line)) {
        if (line.empty()) continue; // пропускаем пустые строки

        // ищем позиции запятых в строке
        int pos1 = line.find(','); // позиция первой запятой
        int pos2 = line.find(',', pos1 + 1); // позиция второй запятой

        // если нашли обе запятые
        if (pos1 != -1 && pos2 != -1) {
            Product p;
            // извлекаем название (от начала до первой запятой)
            p.name = line.substr(0, pos1);
            // извлекаем цену (между первой и второй запятой)
            p.price = stod(line.substr(pos1 + 1, pos2 - pos1 - 1));
            // извлекаем количество (после второй запятой до конца)
            p.quantity = stoi(line.substr(pos2 + 1));
            // добавляем продукт в вектор
            products.push_back(p);
        }
    }
    file.close(); // закрываем файл
    return products; // возвращаем вектор с продуктами
}

// Функция записи продуктов в файл
void writeProducts(vector<Product> products) {
    ofstream file("products.txt"); // открываем файл для записи (перезаписываем)
    file << "Название,Цена,Количество" << endl; // записываем заголовок

    // проходим по всем продуктам и записываем их в файл
    for (int i = 0; i < products.size(); i++) {
        file << products[i].name << "," << products[i].price << "," << products[i].quantity << endl;
    }
    file.close(); // закрываем файл
}

// Функция добавления одного продукта
void addProduct() {
    Product p;
    cout << "Название: ";
    cin.ignore(); // очищаем буфер ввода
    getline(cin, p.name); // читаем название целиком
    cout << "Цена: ";
    cin >> p.price; // читаем цену
    cout << "Количество: ";
    cin >> p.quantity; // читаем количество

    // открываем файл в режиме добавления (не перезаписываем)
    ofstream file("products.txt", ios::app);
    file << p.name << "," << p.price << "," << p.quantity << endl;
    file.close();

    // записываем информацию о добавлении в файл output.txt
    ofstream out("output.txt", ios::app);
    out << "Добавлен: " << p.name << endl;
    out.close();
}

// Функция поиска продукта по названию
void searchProduct() {
    string name;
    cout << "Введите название: ";
    getline(cin, name); // читаем название для поиска
    vector<Product> products = readProducts(); // читаем все продукты из файла
    ofstream out("output.txt", ios::app); // открываем файл для логов
    out << "Поиск: " << name << endl; // записываем что ищем

    // ищем продукты, содержащие введенное название
    for (int i = 0; i < products.size(); i++) {
        // если название содержит искомую строку
        if (products[i].name.find(name) != -1) {
            // записываем найденный продукт в лог
            out << "Найден: " << products[i].name << " " << products[i].price << " " << products[i].quantity << endl;
        }
    }
    out.close(); // закрываем файл логов
}

// Функция сортировки продуктов
void sortProducts() {
    int choice;
    cout << "1 - по цене, 2 - по количеству: ";
    cin >> choice; // получаем выбор пользователя

    vector<Product> products = readProducts(); // читаем продукты из файла

    // сортируем пузырьком по цене
    if (choice == 1) {
        for (int i = 0; i < products.size() - 1; i++) {
            for (int j = 0; j < products.size() - i - 1; j++) {
                if (products[j].price > products[j + 1].price) {
                    swap(products[j], products[j + 1]); // меняем местами
                }
            }
        }
    }
    // сортируем пузырьком по количеству
    else {
        for (int i = 0; i < products.size() - 1; i++) {
            for (int j = 0; j < products.size() - i - 1; j++) {
                if (products[j].quantity > products[j + 1].quantity) {
                    swap(products[j], products[j + 1]); // меняем местами
                }
            }
        }
    }

    writeProducts(products); // записываем отсортированные продукты обратно в файл

    // записываем в лог что сортировка завершена
    ofstream out("output.txt", ios::app);
    out << "Сортировка завершена" << endl;
    out.close();
}

// Функция поиска продуктов по максимальной цене
void findCheapProducts() {
    double maxPrice;
    cout << "Максимальная цена: ";
    cin >> maxPrice; // получаем максимальную цену от пользователя

    vector<Product> products = readProducts(); // читаем все продукты
    ofstream out("output.txt", ios::app); // открываем файл логов
    out << "Продукты до " << maxPrice << ":" << endl;

    // ищем продукты с ценой не больше максимальной
    for (int i = 0; i < products.size(); i++) {
        if (products[i].price <= maxPrice) {
            // записываем подходящий продукт в лог
            out << products[i].name << " " << products[i].price << " " << products[i].quantity << endl;
        }
    }
    out.close(); // закрываем файл логов
}

// Функция показа всех продуктов
void showAll() {
    vector<Product> products = readProducts(); // читаем все продукты
    ofstream out("output.txt", ios::app); // открываем файл логов
    out << "Все продукты:" << endl;

    // записываем все продукты в лог
    for (int i = 0; i < products.size(); i++) {
        out << products[i].name << " " << products[i].price << " " << products[i].quantity << endl;
    }
    out.close(); // закрываем файл логов
}

// Функция создания файла и заполнения его продуктами
void createFile() {
    // создаем/очищаем файл и записываем заголовок
    ofstream file("products.txt");
    file << "Название,Цена,Количество" << endl;
    file.close();

    string name;
    double price;
    int quantity;

    // цикл для ввода продуктов
    while (true) {
        cout << "Название (пусто для выхода): ";
        getline(cin, name); // читаем название

        // если введена пустая строка - выходим из цикла
        if (name.empty()) break;

        cout << "Цена: ";
        cin >> price; // читаем цену
        cout << "Количество: ";
        cin >> quantity; // читаем количество
        cin.ignore(); // очищаем буфер

        // открываем файл в режиме добавления и записываем продукт
        ofstream file("products.txt", ios::app);
        file << name << "," << price << "," << quantity << endl;
        file.close();
    }
}

// Главная функция программы




int main()
{
    setlocale(LC_ALL, "Russian"); // устанавливаем русскую локаль


    cout << endl;
    int choice;
    // главный цикл меню
    do {
        // показываем меню
        cout << "1. Добавить\n2. Поиск\n3. Сортировка\n4. Добавить один\n5. Поиск по цене\n6. Показать все\n7. Выход\nВыбор: ";
        cin >> choice; // читаем выбор пользователя
        cin.ignore();
        // выполняем действие в зависимости от выбора
        switch (choice) {
        case 1: createFile(); break;     // создать/заполнить файл
        case 2: searchProduct(); break;  // поиск по названию
        case 3: sortProducts(); break;   // сортировка
        case 4: addProduct(); break;     // добавить один продукт
        case 5: findCheapProducts(); break; // поиск по цене
        case 6: showAll(); break;        // показать все продукты
        }
    } while (choice != 7); // выходим когда пользователь выберет 7

    return 0; // завершаем программу
}


