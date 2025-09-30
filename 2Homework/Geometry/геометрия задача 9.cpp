#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	int b = 1;
	const int a = 4;
	int j = 65;

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
	int x3 = arrayX[2];
	int x4 = arrayX[3];
	int y1 = arrayY[0];
	int y2 = arrayY[1];
	int y3 = arrayY[2];
	int y4 = arrayY[3];
	if (
		(x2 >= x4 && y2 >= y4 && x1 <= x3 && y1 <= y3) ||
		(x2 <= x4 && y2 <= y4 && x1 >= x3 && y1 >= y3)
		) {
		cout << "Your lines cross" << endl;
	}

	return 0;

}
