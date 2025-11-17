#include <iostream>
#include <cstring>
using namespace std;

int** transpose(int** matrix, int n, int m) {

    int** result = new int* [m];
    for (int i = 0; i < m; i++) {
        result[i] = new int[n];
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = matrix[j][i];
        }
    }

    return result;
}

void sortRowsBySum(int** arr, int n, int m) {
    pair<int, int*>* rows = new pair<int, int*>[n];

    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j < m; j++) {
            sum += arr[i][j];
        }
        rows[i] = make_pair(sum, arr[i]);
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (rows[j].first > rows[j + 1].first) {
                swap(rows[j], rows[j + 1]);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        arr[i] = rows[i].second;
    }

    delete[] rows;
}
int main() {
    int n = 2, m = 3;

    int** matrix = new int* [n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[m];
    }

    int counter = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i][j] = counter++;
        }
    }

    cout << "Massive" << n << "x" << m << ":\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    int** transposed = transpose(matrix, n, m);

    cout << "\nNew massive " << m << "x" << n << ":\n";
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << transposed[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    for (int i = 0; i < m; i++) {
        delete[] transposed[i];
    }
    delete[] transposed;
}