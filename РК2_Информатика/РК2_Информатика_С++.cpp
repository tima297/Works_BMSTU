#include <iostream>
#include <string>
using namespace std;

// Базовый класс Банковский счет
class BankAccount {
protected:
    string accountNumber;  // номер счета
    string ownerName;      // имя владельца
    double balance;        // баланс

public:
    // Конструктор
    BankAccount(string accNum, string name, double startBalance = 0) {
        accountNumber = accNum;
        ownerName = name;
        balance = startBalance;
    }

    // Пополнение
    void deposit(double amount) {
        balance += amount;
        cout << "Пополнение: +" << amount << " руб. Баланс: " << balance << " руб." << endl;
    }

    // Снятие
    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Ошибка: недостаточно средств!" << endl;
            return false;
        }
        balance -= amount;
        cout << "Снятие: -" << amount << " руб. Баланс: " << balance << " руб." << endl;
        return true;
    }

    // Информация о счете
    void showInfo() {
        cout << "=== Информация о счете ===" << endl;
        cout << "Номер: " << accountNumber << endl;
        cout << "Владелец: " << ownerName << endl;
        cout << "Баланс: " << balance << " руб." << endl;
        cout << "==========================" << endl;
    }
};

// Сберегательный счет с процентами
class SavingsAccount : public BankAccount {
private:
    double interestRate;  // процентная ставка

public:
    // Конструктор
    SavingsAccount(string accNum, string name, double startBalance = 0, double rate = 0)
        : BankAccount(accNum, name, startBalance) {
        interestRate = rate;
    }

    // Начисление процентов
    void addInterest() {
        double interest = balance * interestRate / 100;
        balance += interest;
        cout << "Начислены проценты: +" << interest << " руб." << endl;
        cout << "Ставка: " << interestRate << "%" << endl;
        cout << "Новый баланс: " << balance << " руб." << endl;
    }

    // Информация о сберегательном счете
    void showInfo() {
        cout << "=== Сберегательный счет ===" << endl;
        cout << "Номер: " << accountNumber << endl;
        cout << "Владелец: " << ownerName << endl;
        cout << "Баланс: " << balance << " руб." << endl;
        cout << "Процентная ставка: " << interestRate << "%" << endl;
        cout << "============================" << endl;
    }
};

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    cout << "БАНКОВСКАЯ СИСТЕМА" << endl;
    cout << "==================" << endl;

    // Обычный счет
    cout << "\n1. Обычный банковский счет:" << endl;
    BankAccount account1("1234567890", "Иванов Иван", 10000);
    account1.showInfo();

    account1.deposit(5000);
    account1.withdraw(3000);
    account1.withdraw(20000);  // попытка снять больше чем есть

    // Сберегательный счет
    cout << "\n\n2. Сберегательный счет:" << endl;
    SavingsAccount account2("9876543210", "Петрова Мария", 50000, 5.5);
    account2.showInfo();

    account2.deposit(10000);
    account2.withdraw(5000);

    cout << "\n3. Начисление процентов:" << endl;
    account2.addInterest();

    cout << "\n4. Еще одно начисление после пополнения:" << endl;
    account2.deposit(15000);
    account2.addInterest();

    // Второй сберегательный счет
    cout << "\n\n5. Второй сберегательный счет (без процентов):" << endl;
    SavingsAccount account3("5555555555", "Сидоров Алексей", 10000, 0);
    account3.showInfo();
    account3.addInterest();

    cout << "\n==================" << endl;
    cout << "ПРОГРАММА ЗАВЕРШЕНА" << endl;

    return 0;
}
