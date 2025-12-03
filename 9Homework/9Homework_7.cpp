#include <vector>
#include <iostream> 
#include <numeric>
#include <fstream>
#include <string> 
#include <cctype>
#include <sstream>
#include <locale.h>
using namespace std;

int main() {
	setlocale(LC_ALL, "Rus");
	// number 1
	ofstream File("numbers.txt");
	if (File.is_open()) {
		File << 56 ;
		File << 76;
		File.close();
		cout << "All good" << endl;
	}
	else {
		cerr << "Shit" << endl;
	}
	ifstream inputFile("numbers.txt");

	if (!inputFile.is_open()) {
		cout << "Shit numbers.txt" << endl;
		return 1;
	}
	int number;       
	int count = 0;     
	int sum = 0;       

	
	while (inputFile >> number) {
		count++;        
		sum += number; 
	}



	inputFile.close();
	double average = (count > 0) ? static_cast<double>(sum) / count : 0;
	cout << "Количество чисел: " << count << endl;
	cout << "Сумма: " << sum << endl;
	cout << "Среднее: " << average << endl;

	return 0;
}