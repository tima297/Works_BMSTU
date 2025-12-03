#include <vector>
#include <iostream> 
#include <numeric>
#include <fstream>
#include <string> 
#include <cctype>
using namespace std;

int main() {

	// number 1
	ofstream File("input.txt");
	if (File.is_open()) {
		File << "This is first sentece" << endl;
		File << "This is second sentece" << endl;
		File << "This is third sentece" << endl;
		File.close();
		cout << "All good" << endl;
	}
	else {
		cerr << "Shit" << endl;
	}
	ifstream inputFile("input.txt");

	if (!inputFile.is_open()) {
		cout << "Shit input.txt" << endl;
		return 1;
	}
	char ch;
	int totalChars = 0;



	while (inputFile.get(ch)) {
		totalChars++;

	}
	inputFile.close();

	cout << "Файл успешно скопирован." << endl;
	cout << "Letters: " << totalChars << endl;

	return 0;
}
