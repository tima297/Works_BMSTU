#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	int b = 1;
	int a = 0;
	int c = 0;
	cout << "Write the amount of corners:";
	cin >> c;
	a = c * 2;

	int* array = new int[a];
	for (int i = 0; i < a; i++) {
		cout << "Write the x" << b << endl;
		cin >> array[i];
		cout << "Write the y" << b << endl;
		cin >> array[i += 1];
		b += 1;


	}
	for (int i = 0; i < a; i++) {
		cout << array[i] << " ";

	}
	cout << " " << endl;
	double Cx = (array[0] + array[2] + array[4]) / 2;
    double Cy = (array[1] + array[3] + array[5]) / 2;
	cout << "The center of mass " << Cx <<";" << Cy;
	return 0;
}


