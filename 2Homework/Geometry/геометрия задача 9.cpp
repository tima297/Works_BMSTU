﻿#include <iostream>
using namespace std;

int main() {
    setlocale(LC_ALL, "RU");

    int n1, n2;
    double x1[100], y1[100], x2[100], y2[100];

    cout << "Введите количество вершин первого многоугольника (до 100): ";
    cin >> n1;
    for (int i = 0; i < n1; i++) {
        cout << "Вершина" << i + 1 << "(x y):" << endl;
        cin >> x1[i] >> y1[i];
    }

    cout << "Введите количество вершин второго многоугольника (до 100): ";
    cin >> n2;
    for (int i = 0; i < n2; i++) {
        cout << "Вершина" << i + 1 << "(x y):" << endl;
        cin >> x2[i] >> y2[i];
    }

    // Проверка пересечения
    for (int i = 0; i < n1; i++) {
        double Ax = x1[i], Ay = y1[i];
        double Bx = x1[(i + 1) % n1], By = y1[(i + 1) % n1];

        for (int j = 0; j < n2; j++) {
            double Cx = x2[j], Cy = y2[j];
            double Dx = x2[(j + 1) % n2], Dy = y2[(j + 1) % n2];

            double v1 = (Bx - Ax) * (Cy - Ay) - (By - Ay) * (Cx - Ax);
            double v2 = (Bx - Ax) * (Dy - Ay) - (By - Ay) * (Dx - Ax);
            double v3 = (Dx - Cx) * (Ay - Cy) - (Dy - Cy) * (Ax - Cx);
            double v4 = (Dx - Cx) * (By - Cy) - (Dy - Cy) * (Bx - Cx);

            if (v1 * v2 < 0 && v3 * v4 < 0) {
                cout << "ПЕРЕСЕКАЮТСЯ" << endl;
                return 0;
            }
        }
    }

    cout << "НЕ пересекаются" << endl;
    return 0;
}
