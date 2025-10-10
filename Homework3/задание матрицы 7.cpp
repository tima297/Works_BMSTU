#include <iostream>
#include <cmath>

using namespace std;

int main() {
    cout << " sistem of your  " << endl;
    cout << "x + y + z =6" << endl;
    cout << "2x - y + 3z = 14" << endl;
    cout << "-x + 4y - z = 2" << endl;
    cout << endl;

    double a11 = 1, a12 = 1, a13=1;
    double a21 = 2, a22 = -1, a23= 3;
    double a31 = -1, a32 = 4, a33= -1;
    double b1 = 6, b2 = 14, b3=2;


    double det_main = a11 * a22 *a33+a12*a23*a31+a13*a21*a32 -
        a13*a22*a31-a11*a23*a32-a12*a21*a33;

    if (abs(det_main) < 1e-10) {
        cout << "The systeam havent got one answer" << endl;
        return 0;
    }


    double det_x = b1 * a22 * a33 + b2 * a23 * b3 + a13 * a21 * a32 -
        a13 * a22 * b3 - b1 * a23 * a32 - a12 * b2 * a33;
    double det_y = a11 * b2 * a33 + b1 * a23 * a31 + a13 * a21 * b3 -
        a13 * b2 * a31 - a11 * a23 * b3 - b1 * a21 * a33;
    double det_z= a11 * a22 * b3 + a12 * a23 * a31 + b1 * a21 * a32 -
        b1 * a22 * a31 - a11 * b2 * a32 - a12 * a21 * b3;

    double x = det_x / det_main;
    double y = det_y / det_main;
    double z = det_z / det_main;


    cout << "Answer " << endl;
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;
    cout << "z = " << z << endl;



  
    return 0;
}
