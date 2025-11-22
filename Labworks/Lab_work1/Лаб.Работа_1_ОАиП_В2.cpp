#include <iostream>
using namespace std;

int main()
{
    const int n = 10;
    int array[n];
    for (int i = 0; i < n; i++) {
        cout << "write the " << i + 1 << " number:" << endl;
        cin >> array[i];

    }
    for (int i = 0; i < n; i++) {
        cout << array[i] << " ";
    }
    cout << " "<<endl;


    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum = sum + array[i];
    }
    cout << "Summ of your elements " << sum << endl;


    int max = array[0];
    for (int i = 0; i < n; i++) {
        if (array[i] > max) {
            max = array[i];

        }
    }
    cout << "The biggest element: " << max << endl;


    void bubbleSort(int array[], int a); {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9 - i; j++) {
                if (array[j + 1] > array[j]) {
                    int c = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = c;

                }
            }

        }
        for (int i = 0; i < n; i++) {
            cout << array[i] << " ";
        }
    }



    return 0;
}
