#include <iostream>
#include <cstring>
#include <cstdlib>
#include <iomanip>
using namespace std;

double** allocatePlate(int n, int m) {
    double** plate = new double* [n];
    for (int i = 0; i < n; i++) {
        plate[i] = new double[m];
        for (int j = 0; j < m; j++) {
            plate[i][j] = 20.0; 
        }
    }
    return plate;
}

void freePlate(double** plate, int n) {
    for (int i = 0; i < n; i++) {
        delete[] plate[i];
    }
    delete[] plate;
}

void updateTemperature(double** plate, int n, int m) {
    double** newPlate = allocatePlate(n, m);

    int centerX = n / 2;
    int centerY = m / 2;
    newPlate[centerX][centerY] = 100.0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == centerX && j == centerY) continue;

            double sum = 0.0;
            int count = 0;

            if (i > 0) { sum += plate[i - 1][j]; count++; }
            if (i < n - 1) { sum += plate[i + 1][j]; count++; }
            if (j > 0) { sum += plate[i][j - 1]; count++; }
            if (j < m - 1) { sum += plate[i][j + 1]; count++; }

            newPlate[i][j] = (count > 0) ? sum / count : plate[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            plate[i][j] = newPlate[i][j];
        }
    }

    freePlate(newPlate, n);
}
int main(){

int n = 5, m = 5, iterations = 10;
double** plate = allocatePlate(n, m);

cout << "Начальное распределение температуры:" << endl;
for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
        cout << fixed << setprecision(1) << plate[i][j] << " ";
    }
    cout << endl;
}

for (int k = 0; k < iterations; k++) {
    updateTemperature(plate, n, m);
}

cout << "\nПосле " << iterations << " итераций:" << endl;
for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
        cout << fixed << setprecision(1) << plate[i][j] << " ";
    }
    cout << endl;
}

freePlate(plate, n);
}