#include <iostream>
#include<climits>
using namespace std;
int main() {
    int n = 0;
    int matrix[100][100] ;

    cout << " Write amount of coordinates of your tringle" << endl;
    cin >> n; 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n-1; j++) {
            if (j % 2 != 0) {
                cout << "Write y" << i + 1 << " of your tringle " << endl;
                cin >> matrix[i][j];
            }
           
            else {
                cout << "Write x" << i + 1 << " of your tringle " << endl;
                cin >> matrix[i][j];
            }
        }
    }
    matrix[0][2] = matrix[1][2] = matrix[2][2] = 1;
    cout << "Put our coordinats into matrix:"<< endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;


    int S = fabs(matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1])
        - matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0])
        + matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0])) / 2;
    cout << "The squre of tringle is:" << S << endl;
   

    return 0;
}

