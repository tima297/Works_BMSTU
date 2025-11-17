#include <iostream>
#include <cstring>
using namespace std;

void swapPointers(int** a, int** b) {
	int c = **a;
	**a = **b;
	**b = c;
	cout << **a << endl;
	cout << **b << endl;


}
int main()
{

	int x = 0;
	int y = 0;
	cout << "Write the x and y amount: " << endl;
	cin >> x;
	cin >> y;
	int* p1 = &x;
	int* p2 = &y;
	cout << *p1 << endl;
	cout << *p2 << endl;
	swapPointers(&p1, &p2);
}