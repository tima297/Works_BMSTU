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
	ifstream file("input.txt");


	if (file.is_open()) {
		string word;
		int count = 0;
		while (file >> word) {
			count++;
		}

		file.close();

		cout << "Word " << count << endl;

		return 0;
	}
}