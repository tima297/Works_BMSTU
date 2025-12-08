#include <iostream>
#include <string>
using namespace std;

struct BankAccount {
    int accountNumber;
    string ownerName;
    int balance;
};

BankAccount accounts[100]; // Простой массив для хранения
int accountCount = 0; // Счетчик счетов

void createAccount() {
    cout << "\nСоздание нового счета:\n";
    cout << "Номер счета: ";
    cin >> accounts[accountCount].accountNumber;
    cout << "Имя владельца: ";
    cin >> accounts[accountCount].ownerName;
    accounts[accountCount].balance = 0;
    accountCount++;
    cout << "Счет создан!\n";
}

void depositMoney() {
    int num;
    double amount;
    cout << "\nПополнение счета:\n";
    cout << "Номер счета: ";
    cin >> num;

    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == num) {
            cout << "Сумма: ";
            cin >> amount;
            accounts[i].balance += amount;
            cout << "Успешно! Новый баланс: " << accounts[i].balance << endl;
            return;
        }
    }
    cout << "Счет не найден!\n";
}

void withdrawMoney() {
    int num;
    double amount;
    cout << "\nСнятие денег:\n";
    cout << "Номер счета: ";
    cin >> num;

    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == num) {
            cout << "Сумма: ";
            cin >> amount;
            if (amount <= accounts[i].balance) {
                accounts[i].balance -= amount;
                cout << "Успешно! Новый баланс: " << accounts[i].balance << endl;
            }
            else {
                cout << "Недостаточно средств!\n";
            }
            return;
        }
    }
    cout << "Счет не найден!\n";
}

void showAccount() {
    int num;
    cout << "\nПоказать счет:\n";
    cout << "Номер счета: ";
    cin >> num;

    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == num) {
            cout << "\nНомер: " << accounts[i].accountNumber << endl;
            cout << "Владелец: " << accounts[i].ownerName << endl;
            cout << "Баланс: " << accounts[i].balance << endl;
            return;
        }
    }
    cout << "Счет не найден!\n";
}

int main() {
    setlocale(LC_ALL, "Russian");
    int choice;

    do {
        cout << "\nМеню:\n";
        cout << "1. Создать счет\n";
        cout << "2. Пополнить\n";
        cout << "3. Снять\n";
        cout << "4. Показать счет\n";
        cout << "5. Выйти\n";
        cout << "Выбор: ";
        cin >> choice;

        switch (choice) {
        case 1: createAccount(); break;
        case 2: depositMoney(); break;
        case 3: withdrawMoney(); break;
        case 4: showAccount(); break;
        case 5: cout << "Выход\n"; break;
        default: cout << "Неверный выбор!\n";
        }
    } while (choice != 5);

    return 0;
}
