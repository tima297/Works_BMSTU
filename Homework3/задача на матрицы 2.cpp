#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    int  x, y, theta;

    cout << "Введите координаты точки (x y): ";
    cin >> x >> y;

    cout << "Введите угол поворота в градусах: ";
    cin >> theta;

    double theta_rad = theta * M_PI / 180.0;

    double cos_theta = cos(theta_rad);
    double sin_theta = sin(theta_rad);

    double x_new = cos_theta * x + sin_theta * y;
    double y_new = -sin_theta * x + cos_theta * y;

    cout << "Исходная точка: (" << x << ", " << y << ")" << endl;
    cout << "Угол поворота: " << theta << " градусов" << endl;
    cout << "Повернутая точка: (" << x_new << ", " << y_new << ")" << endl;

    return 0;
}