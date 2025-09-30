#include <iostream>
using namespace std;
int main()

{
    int a;
    int sum = 0;
    int max = 0;
    int min = 1000000;
    int maxInd = 0;
    int minInd = 0;
    cout << "Write the scale of your massive:";
    cin >> a;
    float* array = new float[a];
    for (int i = 0; i < a; i++) {
        cout << "write the " << i + 1 << " number:" << endl;
        cin >> array[i];

    }

    cout << "Your massive: ";
    for (int i = 0; i < a; i++) {
        cout << array[i]<<" ";

    }
    cout << " " << endl;


    for (int i = 0; i < a; i++) {
        if (array[i] > max) {
            max = array[i];
            maxInd = i;
        }


    }
    for (int i = 0; i < a; i++) {
        if (array[i] < min) {
            min = array[i];
            minInd = i;
        }


    }
    if (minInd==1 && maxInd==0) {
        for (int i = 0; i < a; i++) {
            cout << array[i]/2<<" ";
        }
    }
    else
        cout << "Ops...";








    return 0;


}
