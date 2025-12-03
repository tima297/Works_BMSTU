#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <iomanip>

using namespace std;

int main() {
    // Создаем тестовые данные
    ofstream dataFile("temperature_data.txt");
    dataFile << "Sensor1 22.5\n"
        << "Sensor2 21.8\n"
        << "Sensor3 23.1\n"
        << "Sensor1 22.7\n"
        << "Sensor2 22.0\n"
        << "Sensor3 23.3\n";
    dataFile.close();

    // Чтение данных из файла
    ifstream input("temperature_data.txt");
    if (!input.is_open()) {
        cout << "Ошибка открытия файла!" << endl;
        return 1;
    }

    // Храним данные для каждого датчика
    map<string, vector<double>> sensorData;

    string line;
    while (getline(input, line)) {
        stringstream ss(line);
        string sensorName;
        double temperature;

        if (ss >> sensorName >> temperature) {
            sensorData[sensorName].push_back(temperature);
        }
    }
    input.close();

    // Создаем отчет
    ofstream report("report.txt");

    for (const auto& [sensor, temps] : sensorData) {
        if (temps.empty()) continue;

        double minTemp = *min_element(temps.begin(), temps.end());
        double maxTemp = *max_element(temps.begin(), temps.end());
        double avgTemp = accumulate(temps.begin(), temps.end(), 0.0) / temps.size();

        report << fixed << setprecision(1);
        report << sensor << ": min = " << minTemp
            << ", max = " << maxTemp
            << ", avg = " << avgTemp << endl;
    }
    report.close();

    cout << "Отчёт о температурных данных сохранён в report.txt" << endl;

    return 0;
}