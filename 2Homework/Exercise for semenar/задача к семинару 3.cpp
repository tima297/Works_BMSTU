#include <iostream>
#include<vector>
#include <cmath>
using namespace std;
int main()

{
    int a,c;
    int sum = 0;
    int max = 0;
    int min=1000000;
    int maxInd = 0;
    int minInd = 0;
    cout << "Write the scale of your massive:";
    cin >> a;
    int* array = new int[a];
    int* newArray = new int[a];
    int j = 0;
    for (int i = 0; i < a; i++) {
        cout << "write the " << i + 1 << " number:" << endl;
        cin >> array[i];

    }

    cout << "Your massive:";
    for (int i = 0; i < a; i++) {
        cout << array[i];

    }

   
    for (int i = 0; i < a; i++) {
        if (array[i] > max) {
            max = array[i];
            maxInd = i;
        }
        c = array[maxInd];;
        array[maxInd] = array[a - 1];
        array[a - 1] = c;

    }

    for (int i = 0; i < a; i++) {
        if (array[i] < min) {
            min = array[i];
            minInd = i;
        }
        int  d = array[minInd];;
        array[minInd] = array[0];
        array[0] = d;
    }



    
    cout << "Your new massive:";
    for (int i = 0; i < a; i++) {
        cout << array[i];

    }

    return 0;


}
