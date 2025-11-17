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
int main()
{

    int rows = 0, cols = 0;
    cout << "Write the rows and cols of your massive: " << endl;
    cin >> rows;
    cin >> cols;
    int** array = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        array[i] = new int[cols];
    }
    cout << " Write your numbers" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cin >> array[i][j];

        }
    }
    cout << "Your massive:\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < rows; ++i) {
        delete[] array[i];
    }
    delete[] array;

    // задача 4 
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