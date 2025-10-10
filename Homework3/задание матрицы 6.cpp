#include <iostream>
#include <cmath>

using namespace std;

int main() {
    cout << " sistem of "<<endl;
    cout << "2x + 3y = 13" << endl;
    cout << "5x - y = 9" << endl;
    cout << endl;

    double a11 = 2, a12 = 3;  
    double a21 = 5, a22 = -1; 
    double b1 = 13, b2 = 9;  

    
    double det_main = a11 * a22 - a12 * a21;

    if (abs(det_main) < 1e-10) {
        cout << "The systeam havent got one answer" << endl;
        return 0;
    }


    double det_x = b1 * a22 - a12 * b2;   
    double det_y = a11 * b2 - b1 * a21;   

    double x = det_x / det_main;
    double y = det_y / det_main;


    cout << "Answer " << endl;
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;

  
    cout << "\nCheck:" << endl;
    double check1 = 2 * x + 3 * y;
    double check2 = 5 * x - y;
    cout << "2*" << x << " + 3*" << y << " = " << check1;
    cout << " (should be 13)" << endl;
    cout << "5*" << x << " - " << y << " = " << check2;
    cout << " (should be 9)" << endl;

    return 0;
}