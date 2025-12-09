#include <iostream>
using namespace std;

class Rectangle {
private:
    double length;  
    double width;  

public:
    Rectangle(double l, double w) {
        length = l;
        width = w;
    }

    // Метод для вычисления площади
    double calculateArea() {
        return length * width;
    }

    // Метод для вычисления периметра
    double calculatePerimeter() {
        return 2 * (length + width);
    }

    void displayInfo() {
        cout << "Длина: " << length
            << ", Ширина: " << width
            << ", Площадь: " << calculateArea()
            << ", Периметр: " << calculatePerimeter() << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    // Создаем прямоугольник
    Rectangle myRect(5.5, 3.2);

    myRect.displayInfo();

    return 0;
}
