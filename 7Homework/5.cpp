#include <iostream>
#include <cstring>
using namespace std;

int sumElements(int** arr, int n, int m) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            sum += *(*(arr + i) + j);
        }
    }
    return sum;
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
    int n = 4, m = 3;
    int** arr = new int* [n];


    int data[4][3] = { {1, 2, 3}, {9, 1, 1}, {4, 5, 6}, {2, 2, 2} };
    for (int i = 0; i < n; i++) {
        arr[i] = new int[m];
        for (int j = 0; j < m; j++) {
            arr[i][j] = data[i][j];
        }
    }

    cout << "befor:" << endl;
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j < m; j++) {
            cout << arr[i][j] << " ";
            sum += arr[i][j];
        }
        cout << " (summ: " << sum << ")" << endl;
    }

    sortRowsBySum(arr, n, m);

    cout << "\nafter:" << endl;
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j < m; j++) {
            cout << arr[i][j] << " ";
            sum += arr[i][j];
        }
        cout << " (summ: " << sum << ")" << endl;
    }


    for (int i = 0; i < n; i++) {
        delete[] arr[i];
    }
    delete[] arr;
}
