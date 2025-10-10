#include <iostream>
using namespace std;
int main() {
	int n;
	
	int matrix [100][100];
	int transposed[100][100];
	int transposed2[100][100];
	int transposed3[100][100];
	int transposed4[100][100];


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
			cout << matrix[i][j]<<" ";
		}
		cout << endl;
	}
	cout << endl;
 //1
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			transposed[j][i] = matrix[i][j]; 
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << transposed[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;
	//2
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int z;
			z = matrix[i][j];
			matrix[i][j] = transposed2[n - j - 1][n - i - 1];
		    transposed2[n - j - 1][n - i - 1] = z;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << transposed2[i][j] << " ";
		}

		cout << endl;
	}
	//3
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			transposed3[i][j] = matrix[i][n - 1 - j];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {

			cout << transposed3[i][j] << "\t";
		}
		cout << endl;
	}


	cout << endl;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			transposed4[i][j] = matrix [n - 1 - i][j];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {

			cout << transposed4[i][j] << "\t";
		}
		cout << endl;
	}



	
}
