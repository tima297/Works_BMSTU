#include <iostream>
using namespace std;
int main() {
	int n;

	int matrix[50][50];

	cout << " Write number of rows and cols" << endl;
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << "Write element of your matrix" << endl;

			cin >> matrix[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;


	int mainSum = 0;
	for (int j = 0; j < n; j++) {
		mainSum += matrix[0][j];
	}

    for (int i = 1; i < n; i++) {
        int rowSum = 0;
        for (int j = 0; j < n; j++) {
            rowSum += matrix[i][j];
        }
        if (rowSum != mainSum) {
            cout << "NO" << endl;
            return 0;
        }
    }

    for (int j = 0; j < n; j++) {
        int colSum = 0;
        for (int i = 0; i < n; i++) {
            colSum += matrix[i][j];
        }
        if (colSum != mainSum) {
            cout << "NO" << endl;
            return 0;
        }
    }

    int mainDiagSum = 0;
    for (int i = 0; i < n; i++) {
        mainDiagSum += matrix[i][i];
    }
    if (mainDiagSum != mainSum) {
        cout << "NO" << endl;
        return 0;
    }

    int secondaryDiagSum = 0;
    for (int i = 0; i < n; i++) {
        secondaryDiagSum += matrix[i][n - 1 - i];
    }
    if (secondaryDiagSum != mainSum) {
        cout << "NO" << endl;
        return 0;
    }
    cout << "YES " << mainSum << endl;

	return 0;
}