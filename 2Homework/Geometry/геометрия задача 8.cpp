#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	int b = 1;
	const int a = 2;
	int j = 65;
	float s;


	int arrayX[a];
	int arrayY[a];
	for (int i = 0; i < a; i++) {
		cout << "Write the x" << b << " and y" << b << " for point " << static_cast<char>(j) << endl;
		cin >> arrayX[i];
		cin >> arrayY[i];
		b += 1;
		j += 1;


	}
	for (int i = 0; i < a; i++) {
		cout << arrayX[i] << " " << arrayY[i] << " ";

	}
	cout << " " << endl;
	int x1 = arrayX[0];
	int x2 = arrayX[1];
	int y1 = arrayY[0];
	int y2 = arrayY[1];
	s = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
		cout << "The distance between this points "<< s << endl;
	

	return 0;

}

