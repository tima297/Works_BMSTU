
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <iomanip>

using namespace std;


double** allocateWeights(int n, int m) {
    double** weights = new double* [n];
    for (int i = 0; i < n; i++) {
        weights[i] = new double[m];
        for (int j = 0; j < m; j++) {
            // Инициализация случайными значениями от -1.0 до 1.0
            weights[i][j] = (rand() % 2001 - 1000) / 1000.0;
        }
    }
    return weights;
}

void normalizeWeights(double** weights, int n, int m) {
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < m; j++) {
            sum += abs(weights[i][j]);
        }
        if (sum > 1.0) {
            for (int j = 0; j < m; j++) {
                weights[i][j] /= sum;
            }
        }
    }
}

double* forward(double** weights, double* inputs, int n, int m) {
    double* outputs = new double[n];

    for (int i = 0; i < n; i++) {
        outputs[i] = 0.0;
        for (int j = 0; j < m; j++) {
            outputs[i] += weights[i][j] * inputs[j];
        }
    }

    return outputs;
}
int main() {
    int n = 3, m = 4; 

    double** weights = allocateWeights(n, m);
    double* inputs = new double[m];

    for (int j = 0; j < m; j++) {
        inputs[j] = (rand() % 100) / 10.0;
    }

    cout << "Матрица весов:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << fixed << setprecision(3) << weights[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nВходные сигналы:" << endl;
    for (int j = 0; j < m; j++) {
        cout << inputs[j] << " ";
    }
    cout << endl;

    double* outputs = forward(weights, inputs, n, m);

    cout << "\nВыходы нейронов:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Нейрон " << i << ": " << outputs[i] << endl;
    }

    cout << "\nПосле нормализации весов:" << endl;
    normalizeWeights(weights, n, m);

    cout << "Матрица весов:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << fixed << setprecision(3) << weights[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < n; i++) {
        delete[] weights[i];
    }
    delete[] weights;
    delete[] inputs;
    delete[] outputs;
}
}