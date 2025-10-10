#include <iostream>
#include<climits>
using namespace std;
int main() {
    int n=0;
    int m=0;
    int matrix[100][100];

    cout << " Write number of rows and cols" << endl;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << "Write element of your matrix" << endl;

            cin >> matrix[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    int row_min[100], row_max[100];
    for (int i = 0; i < n; i++) {
        row_min[i] = INT_MAX;
        row_max[i] = INT_MIN;
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] < row_min[i]) row_min[i] = matrix[i][j];
            if (matrix[i][j] > row_max[i]) row_max[i] = matrix[i][j];
        }
    }

    int col_min[100], col_max[100];
    for (int j = 0; j < m; j++) {
        col_min[j] = INT_MAX;
        col_max[j] = INT_MIN;
        for (int i = 0; i < n; i++) {
            if (matrix[i][j] < col_min[j]) col_min[j] = matrix[i][j];
            if (matrix[i][j] > col_max[j]) col_max[j] = matrix[i][j];
        }
    }

    bool found = false;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            if (matrix[i][j] == row_min[i] && matrix[i][j] == col_max[j]) {
                cout << "A " << matrix[i][j] << " " << " positoin:" << i + 1 << " " << j + 1 << endl;
                found = true;
            }

            else if (matrix[i][j] == row_max[i] && matrix[i][j] == col_min[j]) {
                cout << "B " << matrix[i][j] << " " << " positoin:" << i + 1 << " " << j + 1 << endl;
                found = true;
            }
    }
    if (!found) {
        cout << "NONE" << endl;
    }
   
    return 0;
}
