#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	int b=1;
	const int a=4;
	int c = 0;

	int array1[a];
	int array2[a];
	for (int i = 0; i < a; i++) {
		cout << "Write the x" << b <<"and y" <<b<< endl;
		cin >> array1[i];
		cin >> array2[i];
		b += 1;


	}
	for (int i = 0; i < a; i++) {
		cout << array1[i] << " "<< array2[i]<<" ";

	}
	cout << " " << endl;
	double A = sqrt(pow(array1[1] - array1[0], 2) + pow(array2[1] - array2[0], 2));
	double B = sqrt(pow(array1[2] - array1[1], 2) + pow(array2[2] - array2[1], 2));
	double C = sqrt(pow(array1[2] - array1[0], 2) + pow(array2[3] - array2[0], 2));
	if (pow(C, 2) == pow(A, 2) + pow(B, 2)) {
		cout << "Diagonal" << C << endl;
	}
	
	return 0;
  

 

