#include <iostream>
#include<vector>
#include <cmath>
using namespace std;
int main()

{
    int a;
    int summ = 0;
    int max = 0;
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
        if (array[i] % 2 != 0) {
            newArray[j] = array[i];
            j++;
        }

    }

    cout << "Your new massive:";
    for (int i = 0; i < j; i++) {
        cout << newArray[i]<<"  ";
    }
    


    for (int i = 0; i < j; i++) {
        if (newArray[i] > max)
            max = newArray[i];

    }
    cout << "The biggest element from chetnue:" << max;




    return 0;


}
