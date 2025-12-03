#include <vector>
#include <iostream> 
#include <numeric>
#include <fstream>
#include <string> 
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
	ofstream outputFile("copy.txt");
	if (!inputFile.is_open()) {
		cout << "Shit input.txt" << endl;
		return 1;
	}
	if (!outputFile.is_open()) {
		cout << "Shit copy.txt" << endl;
		return 1;
	}
	string line;
	int lineCount = 0;


	while (getline(inputFile, line)) {

		outputFile << line << endl;
		lineCount++;

		inputFile.close();
		outputFile.close();


		cout << "Файл успешно скопирован." << endl;
		cout << "Количество скопированных строк: " << lineCount << endl;

		return 0;
	}
}