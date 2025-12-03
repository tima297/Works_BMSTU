#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <sstream>

using namespace std;

int main() {
    // Создаем тестовые данные
    ofstream vibFile("vibration_log.txt");
    vibFile << "0.02\n0.05\n0.03\n0.10\n0.09\n0.07\n0.15\n0.04\n";
    vibFile.close();

    // Чтение данных в вектор
    ifstream input("vibration_log.txt");
    if (!input.is_open()) {
        cout << "Ошибка открытия файла!" << endl;
        return 1;
    }

    vector<double> amplitudes;
    double value;

    while (input >> value) {
        amplitudes.push_back(value);
    }
    input.close();

    // Анализ с использованием лямбда-функций

    // 1. Фильтрация значений (>0.05)
    vector<double> filtered;
    copy_if(amplitudes.begin(), amplitudes.end(),
        back_inserter(filtered),
        [](double x) { return x > 0.05; });

    // 2. Вычисление среднего значения
    double sumAll = accumulate(amplitudes.begin(), amplitudes.end(), 0.0);
    double averageAll = sumAll / amplitudes.size();

    double sumFiltered = accumulate(filtered.begin(), filtered.end(), 0.0);
    double averageFiltered = filtered.empty() ? 0 : sumFiltered / filtered.size();

    // 3. Нахождение минимума и максимума среди отфильтрованных
    double minVal = 0, maxVal = 0;
    if (!filtered.empty()) {
        auto [minIt, maxIt] = minmax_element(filtered.begin(), filtered.end());
        minVal = *minIt;
        maxVal = *maxIt;
    }

    // Создание отчета
    ofstream report("vibration_report.txt");
    report << fixed << setprecision(4);

    report << "Количество измерений: " << amplitudes.size() << endl;
    report << "Фильтрованные значения (>0.05): ";

    for (double val : filtered) {
        report << val << " ";
    }
    report << endl;

    report << "Среднее значение всех измерений: " << averageAll << endl;
    report << "Среднее значение фильтрованных: " << averageFiltered << endl;
    report << "Минимум среди фильтрованных: " << minVal << endl;
    report << "Максимум среди фильтрованных: " << maxVal << endl;

    report.close();

    cout << "Анализ вибрационных данных завершён. Отчёт сохранён в vibration_report.txt" << endl;

    return 0;
}