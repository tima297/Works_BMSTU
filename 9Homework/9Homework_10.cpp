#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <numeric>
#include <iomanip>

using namespace std;

int main() {
    // Создаем тестовые данные
    ofstream logFile("power_log.txt");
    logFile << "2025-11-09T08:00:00 MotorA 1.25\n"
        << "2025-11-09T08:00:00 PumpB 0.95\n"
        << "2025-11-09T08:30:00 MotorA 1.40\n"
        << "2025-11-09T08:30:00 PumpB 0.90\n"
        << "2025-11-09T09:00:00 MotorA 1.35\n";
    logFile.close();

    // Чтение данных
    ifstream input("power_log.txt");
    if (!input.is_open()) {
        cout << "Ошибка открытия файла!" << endl;
        return 1;
    }

    map<string, vector<double>> deviceData;

    string line;
    while (getline(input, line)) {
        stringstream ss(line);
        string timestamp, deviceName;
        double power;

        if (ss >> timestamp >> deviceName >> power) {
            deviceData[deviceName].push_back(power);
        }
    }
    input.close();

    // Создаем отчет
    ofstream report("energy_report.txt");
    report << fixed << setprecision(2);

    for (const auto& [device, powers] : deviceData) {
        int measurements = powers.size();
        double total = accumulate(powers.begin(), powers.end(), 0.0);
        double average = total / measurements;

        report << device << ": measurements = " << measurements
            << ", total = " << total << " kWh"
            << ", average = " << average << " kW" << endl;
    }
    report.close();

    cout << "Анализ завершён. Результаты сохранены в energy_report.txt" << endl;

    return 0;
}