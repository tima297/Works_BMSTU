#include <iostream>
using namespace std;

int main() {

    int n = 0;
    cout << "Write amount of calls and rows" << endl;
    cin >> n;

    int matrix[100][100];
    int num = 1;
    int top = 0, bottom = n - 1, left = 0, right = n- 1;

    while (num <= n * n) {
        for (int j = left; j <= right; j++) {
            matrix[top][j] = num++;
        }
        top++;

        for (int i = top; i <= bottom; i++) {
            matrix[i][right] = num++;
        }
        right--;

        for (int j = right; j >= left; j--) {
            matrix[bottom][j] = num++;
        }
        bottom--;

        for (int i = bottom; i >= top; i--) {
            matrix[i][left] = num++;
        }
        left++;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}