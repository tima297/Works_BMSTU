#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Product {
    string name;
    double price;
    int quantity;
};

// Чтение списка продуктов из файла
vector<Product> readProducts() {
    vector<Product> products;
    ifstream file("products.txt");
    string line;
    getline(file, line); // Пропустить заголовок
    while (getline(file, line)) {
        if (line.empty()) continue;
        int pos1 = line.find(',');
        int pos2 = line.find(',', pos1 + 1);
        if (pos1 != -1 && pos2 != -1) {
            Product p;
            p.name = line.substr(0, pos1);
            p.price = stod(line.substr(pos1 + 1, pos2 - pos1 - 1));
            p.quantity = stoi(line.substr(pos2 + 1));
            products.push_back(p);
        }
    }
    return products;
}

// Запись списка продуктов в файл
void writeProducts(const vector<Product>& products) {
    ofstream file("products.txt");
    file << "Название,Цена,Количество\n";
    for (const auto& p : products) {
        file << p.name << "," << p.price << "," << p.quantity << "\n";
    }
}

void createFile() {
    ofstream file("products.txt");
    file << "Название,Цена,Количество\n";
    file.close();
    string name;
    double price;
    int quantity;
    while (true) {
        cout << "Название (пусто для выхода): ";
        getline(cin, name);
        if (name.empty()) break;
        cout << "Цена: ";
        cin >> price;
        cout << "Количество: ";
        cin >> quantity;
        cin.ignore();
        ofstream file("products.txt", ios::app);
        file << name << "," << price << "," << quantity << "\n";
        file.close();
        ofstream out("output.txt", ios::app);
        out << "Добавлен: " << name << "\n";
        out.close();
    }
}

void addProduct() {
    Product p;
    cout << "Название: ";
    getline(cin, p.name);
    cout << "Цена: ";
    cin >> p.price;
    cout << "Количество: ";
    cin >> p.quantity;
    cin.ignore();
    ofstream file("products.txt", ios::app);
    file << p.name << "," << p.price << "," << p.quantity << "\n";
    file.close();
    ofstream out("output.txt", ios::app);
    out << "Добавлен: " << p.name << "\n";
    out.close();
}

void searchProduct() {
    string name;
    cout << "Введите название: ";
    getline(cin, name);
    vector<Product> products = readProducts();
    bool found = false;
    ofstream out("output.txt", ios::app);
    out << "Поиск: " << name << "\n";
    for (const auto& p : products) {
        if (p.name.find(name) != string::npos) {
            out << "Найден: " << p.name << " " << p.price << " " << p.quantity << "\n";
            cout << p.name << ", " << p.price << ", " << p.quantity << endl;
            found = true;
        }
    }
    if (!found) cout << "Продукт не найден!" << endl;
    out.close();
}

void sortProducts() {
    int choice;
    cout << "1 - по цене, 2 - по количеству: ";
    cin >> choice;
    cin.ignore();
    vector<Product> products = readProducts();
    if (choice == 1) {
        sort(products.begin(), products.end(), [](const Product& a, const Product& b) { return a.price < b.price; });
    }
    else {
        sort(products.begin(), products.end(), [](const Product& a, const Product& b) { return a.quantity < b.quantity; });
    }
    writeProducts(products);
    ofstream out("output.txt", ios::app);
    out << "Сортировка завершена\n";
    out.close();
    cout << "Сортировка завершена!\n";
}

void findCheapProducts() {
    double maxPrice;
    cout << "Максимальная цена: ";
    cin >> maxPrice;
    cin.ignore();
    vector<Product> products = readProducts();
    bool found = false;
    ofstream out("output.txt", ios::app);
    out << "Продукты до " << maxPrice << ":\n";
    for (const auto& p : products) {
        if (p.price <= maxPrice) {
            out << p.name << " " << p.price << " " << p.quantity << "\n";
            cout << p.name << ", " << p.price << ", " << p.quantity << endl;
            found = true;
        }
    }
    if (!found) cout << "Таких продуктов нет!\n";
    out.close();
}

void showAll() {
    vector<Product> products = readProducts();
    ofstream out("output.txt", ios::app);
    out << "Все продукты:\n";
    for (const auto& p : products) {
        out << p.name << " " << p.price << " " << p.quantity << "\n";
        cout << p.name << ", " << p.price << ", " << p.quantity << endl;
    }
    out.close();
}

int main() {
    setlocale(LC_ALL, "Russian");
    int choice;
    do {
        cout << "1. Создать/заполнить файл\n2. Поиск\n3. Сортировка\n4. Добавить продукт\n5. Поиск по цене\n6. Показать все\n7. Выход\nВыбор: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 1: createFile(); break;
        case 2: searchProduct(); break;
        case 3: sortProducts(); break;
        case 4: addProduct(); break;
        case 5: findCheapProducts(); break;
        case 6: showAll(); break;
        }
    } while (choice != 7);
    return 0;
}