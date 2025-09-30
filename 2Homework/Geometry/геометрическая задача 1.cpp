#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	
	int b = 1;
	const int n=6;
	int array[n];
	for (int i = 0; i <n; i++) {
		cout << "Write the x"<< b <<endl;
		cin >> array[i];
		cout << "Write the y" << b << endl;
		cin >> array[i+=1];
		b += 1;
		
	
	}
	for (int i = 0; i < n; i++) {
		cout<<array[i];
		
	}
	cout << " "<< endl;
	float S =(abs(array[0]*(array[2]-array[5])+array[2]*(array[5]-array[1])+array[4]*(array[1]-array[3])))/2;
	cout << "S=" << S;
	return 0;
}

