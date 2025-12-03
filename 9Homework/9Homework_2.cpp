#include <vector>
#include <iostream> 
#include <numeric>
#include <fstream>
#include <string> 
using namespace std;

int main() {


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
	ifstream inFile("input.txt");
	if (inFile.is_open()) {
		string line;
		int counter = 0;
		while (getline(inFile, line)) {
			cout << line << endl;
			counter++;

		}

		cout << counter << endl;
		inFile.close();
	}
	else {
		cerr << "Shit" << endl;
	}