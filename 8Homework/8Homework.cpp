#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>

using namespace std;

// Task 1
void task1() {
    cout << "=== Task 1: Simple unique_ptr ===" << endl;
    unique_ptr<int> ptr = make_unique<int>(10);
    cout << "Value: " << *ptr << endl;
    *ptr = 25;
    cout << "New value: " << *ptr << endl;
}

// Task 2
void task2() {
    cout << "\n=== Task 2: Array with unique_ptr ===" << endl;
    int n;
    cout << "Enter array size: ";
    cin >> n;

    unique_ptr<int[]> arr = make_unique<int[]>(n);
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    cout << "Array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Task 3
void fillArray(unique_ptr<int[]>& arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i * i;
    }
}

void task3() {
    cout << "\n=== Task 3: Fill array with squares ===" << endl;
    int n = 5;
    unique_ptr<int[]> arr = make_unique<int[]>(n);
    fillArray(arr, n);

    cout << "Squares: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Task 4
void task4() {
    cout << "\n=== Task 4: Transfer ownership with std::move ===" << endl;
    unique_ptr<int> ptr1 = make_unique<int>(42);
    cout << "ptr1: " << *ptr1 << endl;

    unique_ptr<int> ptr2 = move(ptr1);
    cout << "After move:" << endl;
    cout << "ptr1 is null: " << (ptr1 == nullptr) << endl;
    cout << "ptr2: " << *ptr2 << endl;
}

// Task 5
void task5() {
    cout << "\n=== Task 5: 2D table ===" << endl;
    int n = 3, m = 4;
    unique_ptr<int[]> arr = make_unique<int[]>(n * m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            arr[i * m + j] = i * j;
        }
    }

    cout << "Table:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << setw(3) << arr[i * m + j] << " ";
        }
        cout << endl;
    }
}

// Task 6
void task6() {
    cout << "\n=== Task 6: Shared ownership ===" << endl;
    shared_ptr<int> ptr1 = make_shared<int>(100);
    cout << "use_count after ptr1: " << ptr1.use_count() << endl;

    shared_ptr<int> ptr2 = ptr1;
    cout << "use_count after ptr2: " << ptr1.use_count() << endl;

    shared_ptr<int> ptr3 = ptr1;
    cout << "use_count after ptr3: " << ptr1.use_count() << endl;

    ptr2.reset();
    cout << "use_count after ptr2 reset: " << ptr1.use_count() << endl;
}

// Task 7
void task7() {
    cout << "\n=== Task 7: Character analysis ===" << endl;
    string text = "Hello World";
    unique_ptr<char[]> arr = make_unique<char[]>(text.length() + 1);
    strcpy(arr.get(), text.c_str());

    int vowels = 0, consonants = 0;
    string vowelChars = "aeiouAEIOU";

    for (int i = 0; i < text.length(); i++) {
        if (isalpha(arr[i])) {
            if (vowelChars.find(arr[i]) != string::npos) {
                vowels++;
            }
            else {
                consonants++;
            }
        }
    }

    cout << "Text: " << text << endl;
    cout << "Vowels: " << vowels << endl;
    cout << "Consonants: " << consonants << endl;

    unique_ptr<char[]> vowelArray = make_unique<char[]>(vowels + 1);
    int index = 0;
    for (int i = 0; i < text.length(); i++) {
        if (vowelChars.find(arr[i]) != string::npos) {
            vowelArray[index++] = arr[i];
        }
    }
    vowelArray[vowels] = '\0';

    cout << "Vowels only: " << vowelArray.get() << endl;
}

// Task 8
void task8() {
    cout << "\n=== Task 8: Multiple arrays ===" << endl;
    int size = 5;

    unique_ptr<double[]> temp = make_unique<double[]>(size);
    unique_ptr<double[]> pressure = make_unique<double[]>(size);
    unique_ptr<double[]> humidity = make_unique<double[]>(size);

    for (int i = 0; i < size; i++) {
        temp[i] = 20.0 + i * 2.5;
        pressure[i] = 1000.0 + i * 10.0;
        humidity[i] = 50.0 + i * 5.0;
    }

    auto calculateAverage = [](unique_ptr<double[]>& arr, int n) {
        double sum = 0;
        for (int i = 0; i < n; i++) {
            sum += arr[i];
        }
        return sum / n;
        };

    cout << fixed << setprecision(2);
    cout << "Parameter\tAverage Value" << endl;
    cout << "Temperature\t" << calculateAverage(temp, size) << endl;
    cout << "Pressure\t" << calculateAverage(pressure, size) << endl;
    cout << "Humidity\t" << calculateAverage(humidity, size) << endl;
}

// Task 9
void processA(shared_ptr<vector<int>> buf) {
    for (auto& val : *buf) {
        val += 1;
    }
}

void processB(shared_ptr<vector<int>> buf) {
    for (auto& val : *buf) {
        val *= 2;
    }
}

void task9() {
    cout << "\n=== Task 9: Shared buffer ===" << endl;
    shared_ptr<vector<int>> buffer = make_shared<vector<int>>();

    for (int i = 1; i <= 10; i++) {
        buffer->push_back(i);
    }

    cout << "Initial: ";
    for (auto val : *buffer) cout << val << " ";
    cout << endl;

    processA(buffer);
    cout << "After processA: ";
    for (auto val : *buffer) cout << val << " ";
    cout << endl;

    processB(buffer);
    cout << "After processB: ";
    for (auto val : *buffer) cout << val << " ";
    cout << endl;
}

// Task 10
unique_ptr<int[]> createArray(int n) {
    unique_ptr<int[]> arr = make_unique<int[]>(n);
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
    return arr;
}

void task10() {
    cout << "\n=== Task 10: Return unique_ptr from function ===" << endl;
    int n = 6;
    unique_ptr<int[]> arr = createArray(n);

    cout << "Array from function: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Task 11
void task11() {
    cout << "\n=== Task 11: Signal processing ===" << endl;
    vector<double> signals = { 25.4, 27.1, 30.0, 29.5, 28.3 };

    auto mean = [](unique_ptr<double[]>& data, int n) {
        double sum = 0;
        for (int i = 0; i < n; i++) {
            sum += data[i];
        }
        return sum / n;
        };

    auto normalize = [](unique_ptr<double[]>& data, int n, double maxVal) {
        for (int i = 0; i < n; i++) {
            data[i] /= maxVal;
        }
        };

    auto copyBack = [](unique_ptr<double[]>& source, vector<double>& dest, int n) {
        for (int i = 0; i < n; i++) {
            dest[i] = source[i];
        }
        };

    int n = signals.size();
    unique_ptr<double[]> signalArray = make_unique<double[]>(n);
    for (int i = 0; i < n; i++) {
        signalArray[i] = signals[i];
    }

    double avg = mean(signalArray, n);
    double maxSignal = *max_element(signals.begin(), signals.end());

    normalize(signalArray, n, maxSignal);
    copyBack(signalArray, signals, n);

    cout << fixed << setprecision(3);
    cout << "Original data: ";
    for (auto val : signals) cout << val << " ";
    cout << "\nAverage: " << avg << endl;
    cout << "Normalized signals: ";
    for (auto val : signals) cout << val << " ";
    cout << endl;
}

// Task 12
void task12() {
    cout << "\n=== Task 12: Log filtering ===" << endl;
    vector<string> logs = {
        "INFO: Start",
        "ERROR: Disk failure",
        "WARNING: Low memory",
        "ERROR: Disk failure",
        "INFO: Stop"
    };

    shared_ptr<vector<string>> pLogs = make_shared<vector<string>>(logs);

    vector<string> errors;
    auto isError = [](const string& log) {
        return log.find("ERROR") != string::npos;
        };

    copy_if(pLogs->begin(), pLogs->end(), back_inserter(errors), isError);

    sort(errors.begin(), errors.end());
    errors.erase(unique(errors.begin(), errors.end()), errors.end());

    cout << "Original log:" << endl;
    for (const auto& log : *pLogs) {
        cout << log << endl;
    }

    cout << "\nErrors:" << endl;
    for (const auto& error : errors) {
        cout << error << endl;
    }
}

// Task 13
void task13() {
    cout << "\n=== Task 13: Text assembly ===" << endl;
    unique_ptr<string> part1 = make_unique<string>("Sensor data:");
    unique_ptr<string> part2 = make_unique<string>("Voltage stable.");
    unique_ptr<string> part3 = make_unique<string>("System nominal.");

    vector<unique_ptr<string>> reportParts;
    reportParts.push_back(move(part1));
    reportParts.push_back(move(part2));
    reportParts.push_back(move(part3));

    auto concatParts = [](vector<unique_ptr<string>>& parts) {
        string result;
        for (auto& part : parts) {
            result += *part + "\n";
        }
        return result;
        };

    auto countWord = [](const string& text, const string& word) {
        int count = 0;
        size_t pos = 0;
        while ((pos = text.find(word, pos)) != string::npos) {
            count++;
            pos += word.length();
        }
        return count;
        };

    string report = concatParts(reportParts);
    int dataCount = countWord(report, "data");

    cout << "Report:\n" << report << endl;
    cout << "Word 'data' appears " << dataCount << " times" << endl;
}

int main() {
    task1();
    task2();
    task3();
    task4();
    task5();
    task6();
    task7();
    task8();
    task9();
    task10();
    task11();
    task12();
    task13();

    return 0;
}