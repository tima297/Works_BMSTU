#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    // Создаем тестовые файлы
    ofstream file1("file1.txt");
    file1 << "Первая строка\nВторая строка\nТретья строка\n";
    file1.close();

    ofstream file2("file2.txt");
    file2 << "Первая строка\nВторая строка\nТретья строка\n";
    file2.close();

    ifstream f1("file1.txt");
    ifstream f2("file2.txt");

    if (!f1.is_open() || !f2.is_open()) {
        cout << "Ошибка открытия файлов!" << endl;
        return 1;
    }

    string line1, line2;
    bool identical = true;

    while (getline(f1, line1)) {
        if (getline(f2, line2)) {
            if (line1 != line2) {
                identical = false;
                break;
            }
        }
        else {
            identical = false;  
            break;
        }
    }

    // Проверяем, остались ли строки во втором файле
    if (identical && getline(f2, line2)) {
        identical = false;
    }

    f1.close();
    f2.close();

    if (identical) {
        cout << "Файлы идентичны." << endl;
    }
    else {
        cout << "Файлы различаются." << endl;
    }

    return 0;
}