#include <iostream>
#include<vector>
#include <cmath>
using namespace std;
int main()
{
    int a;
    cout << "Write the scale of your massive:";
    cin >> a;
    int* array = new int[a];
    for (int i = 0; i < a; i++) {
        cout << "write the " << i+1 << " number:" << endl;
        cin >> array[i];

    }
    cout << "Your massive:";
    for (int i = 0; i < a; i++) {
        cout << array[i];

    }
    for (int i = 0; i < a; i++) {
        if (array[i] > pow(2, i))
        cout << array[i]<<endl;
        

    }
    return 0;
}
