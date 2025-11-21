#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Product {
    string name;
    double price;
    int quantity;
};

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
}

void searchProduct() {
    string name;
    cout << "Введите название: ";
    getline(cin, name);

    ifstream file("products.txt");
    string line;
    bool found = false;

    while (getline(file, line)) {
        int pos1 = line.find(',');
        int pos2 = line.find(',', pos1 + 1);

        if (pos1 != -1 && pos2 != -1) {
            string productName = line.substr(0, pos1);
            if (productName.find(name) != -1) {
                string priceStr = line.substr(pos1 + 1, pos2 - pos1 - 1);
                string quantityStr = line.substr(pos2 + 1);
                cout << productName << ", " << priceStr << ", " << quantityStr << endl;
                found = true;
            }
        }
    }
    file.close();

    if (!found) {
        cout << "Ничего не найдено" << endl;
    }
}

void sortProducts() {
    // Читаем все продукты в массив
    Product products[100];
    int count = 0;

    ifstream file("products.txt");
    string line;

    while (getline(file, line) && count < 100) {
        int pos1 = line.find(',');
        int pos2 = line.find(',', pos1 + 1);

        if (pos1 != -1 && pos2 != -1) {
            products[count].name = line.substr(0, pos1);
            products[count].price = stod(line.substr(pos1 + 1, pos2 - pos1 - 1));
            products[count].quantity = stoi(line.substr(pos2 + 1));
            count++;
        }
    }
    file.close();

    int choice;
    cout << "1 - по цене, 2 - по количеству: ";
    cin >> choice;
    cin.ignore();

    // Сортировка пузырьком
    if (choice == 1) {
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (products[j].price > products[j + 1].price) {
                    swap(products[j], products[j + 1]);
                }
            }
        }
    }
    else {
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (products[j].quantity > products[j + 1].quantity) {
                    swap(products[j], products[j + 1]);
                }
            }
        }
    }

    // Запись
    ofstream outFile("products.txt");
    for (int i = 0; i < count; i++) {
        outFile << products[i].name << "," << products[i].price << "," << products[i].quantity << "\n";
    }
    outFile.close();

    cout << "Сортировка завершена!\n";
}

void findCheapProducts() {
    double maxPrice;
    cout << "Максимальная цена: ";
    cin >> maxPrice;
    cin.ignore();

    ifstream file("products.txt");
    string line;
    bool found = false;

    while (getline(file, line)) {
        int pos1 = line.find(',');
        int pos2 = line.find(',', pos1 + 1);

        if (pos1 != -1 && pos2 != -1) {
            string productName = line.substr(0, pos1);
            double price = stod(line.substr(pos1 + 1, pos2 - pos1 - 1));

            if (price <= maxPrice) {
                string quantityStr = line.substr(pos2 + 1);
                cout << productName << ", " << price << ", " << quantityStr << endl;
                found = true;
            }
        }
    }
    file.close();

    if (!found) {
        cout << "Нет продуктов по такой цене" << endl;
    }
}

void showAll() {
    ifstream file("products.txt");
    string line;

    while (getline(file, line)) {
        int pos1 = line.find(',');
        int pos2 = line.find(',', pos1 + 1);

        if (pos1 != -1 && pos2 != -1) {
            string productName = line.substr(0, pos1);
            string priceStr = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string quantityStr = line.substr(pos2 + 1);
            cout << productName << ", " << priceStr << ", " << quantityStr << endl;
        }
    }
    file.close();
}

int main() {
    setlocale(LC_ALL, "Russian");
    int choice;

    // Создаем файл 
    ofstream file("products.txt", ios::app);
    file.close();

    do {
        cout << "1. Добавить продукт\n2. Поиск\n3. Сортировка\n4. Поиск по цене\n5. Показать все\n6. Выход\nВыбор: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: addProduct(); break;
        case 2: searchProduct(); break;
        case 3: sortProducts(); break;
        case 4: findCheapProducts(); break;
        case 5: showAll(); break;
        case 6: cout << "Выход..." << endl; break;
        default: cout << "Неверный выбор!" << endl;
        }
    } while (choice != 6);

    return 0;
}

