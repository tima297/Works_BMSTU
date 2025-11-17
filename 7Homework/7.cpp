#include <iostream>
#include <cstring>
using namespace std;

int sumElements(int** arr, int n, int m) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            sum += *(*(arr + i) + j);
        }
    }
    return sum;
}

void sortWords(char** words, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(*(words + j), *(words + j + 1)) > 0) {
                swap(*(words + j), *(words + j + 1));
            }
        }
    }
}

int main() {
    const char* initialWords[] = { "banana", "apple", "cherry", "date", "elderberry", "fig", "grape" };
    int n = 3, m = 5;
    int** arr = new int* [n];
    int counter = 1;
    for (int i = 0; i < n; i++) {
        *(arr + i) = new int[m];
        for (int j = 0; j < m; j++) {
            *(*(arr + i) + j) = counter++;
        }
    }

    cout << "massive:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << *(*(arr + i) + j) << " ";
        }
        cout << endl;
    }

    cout << "Summ of elements: " << sumElements(arr, n, m) << endl;

    for (int i = 0; i < n; i++) {
        delete[] * (arr + i);
    }
    delete[] arr;

    
}