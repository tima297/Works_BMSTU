#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <algorithm>

using namespace std;

// Задача 1. Анализатор текстового файла
void task1() {
    cout << "=== Задача 1: Анализатор текстового файла ===\n";

    string filename = "book.txt";
    string targetWord = "герой";

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла: " << filename << endl;
        return;
    }

    ofstream result("analysis_results.txt");
    result << "Поиск слова: \"" << targetWord << "\"\n";
    result << "================================\n";

    string line;
    int lineNum = 1;
    int total = 0;

    while (getline(file, line)) {
        size_t pos = 0;
        while ((pos = line.find(targetWord, pos)) != string::npos) {
            // Проверяем, что это отдельное слово
            bool isWord = true;
            if (pos > 0 && isalnum(line[pos - 1])) isWord = false;
            if (pos + targetWord.length() < line.length() &&
                isalnum(line[pos + targetWord.length()])) isWord = false;

            if (isWord) {
                result << "Строка " << lineNum << ", позиция " << pos
                    << ": " << line << endl;
                total++;
            }
            pos += targetWord.length();
        }
        lineNum++;
    }

    result << "================================\n";
    result << "Всего найдено: " << total << endl;

    file.close();
    result.close();

    cout << "Найдено " << total << " вхождений слова \"" << targetWord << "\"\n";
    cout << "Результаты в analysis_results.txt\n\n";
}

// Задача 2. Редактор конфигурационных файлов
void task2() {
    cout << "=== Задача 2: Редактор конфигурационных файлов ===\n";

    string filename = "config.txt";

    // Создаем тестовый файл
    ofstream testFile(filename);
    testFile << "server_ip=192.168.1.1\n";
    testFile << "port=8080\n";
    testFile << "timeout=30\n";
    testFile << "max_connections=100\n";
    testFile.close();

    // Читаем весь файл
    ifstream inFile(filename);
    vector<string> lines;
    string line;

    while (getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();

    // Ищем и заменяем
    string key = "timeout=";
    string newValue = "60";

    for (auto& l : lines) {
        if (l.find(key) == 0) { // Начинается с ключа
            l = key + newValue;
            cout << "Изменено: " << l << endl;
        }
    }

    // Записываем обратно
    ofstream outFile(filename);
    for (const auto& l : lines) {
        outFile << l << endl;
    }
    outFile.close();

    cout << "Файл обновлен\n\n";
}

// Задача 3. Разделитель лог-файлов
void task3() {
    cout << "=== Задача 3: Разделитель лог-файлов ===\n";

    string inputFile = "application.log";

    // Создаем тестовый лог-файл
    ofstream testLog(inputFile);
    for (int i = 1; i <= 250; i++) {
        testLog << "Лог запись #" << i << " - "
            << "Сообщение системы " << i * 10 << endl;
    }
    testLog.close();

    ifstream logFile(inputFile);
    if (!logFile.is_open()) {
        cerr << "Ошибка открытия файла\n";
        return;
    }

    const int LINES_PER_FILE = 50;
    int fileCount = 1;
    int lineCount = 0;

    ofstream currentOut;
    ofstream indexFile("log_index.txt");

    string line;
    indexFile << "Индекс лог-файлов\n";
    indexFile << "==================\n";

    while (getline(logFile, line)) {
        if (lineCount % LINES_PER_FILE == 0) {
            if (currentOut.is_open()) {
                currentOut.close();
            }
            string outName = "log_part" + to_string(fileCount) + ".txt";
            currentOut.open(outName);
            indexFile << "log_part" << fileCount << ".txt: строки "
                << lineCount + 1 << " - ";
            fileCount++;
        }

        currentOut << line << endl;
        lineCount++;

        if (lineCount % LINES_PER_FILE == 0) {
            indexFile << lineCount << endl;
        }
    }

    if (lineCount % LINES_PER_FILE != 0) {
        indexFile << lineCount << endl;
    }

    if (currentOut.is_open()) {
        currentOut.close();
    }

    logFile.close();
    indexFile.close();

    cout << "Файл разделен на " << fileCount - 1 << " частей\n";
    cout << "Создан файл индекса: log_index.txt\n\n";
}

// Задача 4. Работа с бинарными файлами
void task4() {
    cout << "=== Задача 4: Работа с бинарными файлами ===\n";

    int numbers[] = { 15, 23, 7, 42, 18, 91, 3, 56, 77, 10 };
    int count = sizeof(numbers) / sizeof(numbers[0]);

    // Запись в бинарный файл
    ofstream outFile("numbers.bin", ios::binary);
    outFile.write(reinterpret_cast<char*>(numbers), sizeof(numbers));
    outFile.close();

    // Чтение из бинарного файла
    ifstream inFile("numbers.bin", ios::binary);

    // Определяем размер файла
    inFile.seekg(0, ios::end);
    size_t fileSize = inFile.tellg();
    inFile.seekg(0, ios::beg);

    // Читаем данные
    int* readNumbers = new int[count];
    inFile.read(reinterpret_cast<char*>(readNumbers), fileSize);
    inFile.close();

    // Выводим результат
    int sum = 0;
    cout << "Прочитанные числа: ";
    for (int i = 0; i < count; i++) {
        cout << readNumbers[i] << " ";
        sum += readNumbers[i];
    }
    cout << "\nРазмер файла: " << fileSize << " байт\n";
    cout << "Сумма чисел: " << sum << endl;

    delete[] readNumbers;
    cout << endl;
}

// Задача 5. Работа со структурой Student
struct Student {
    int id;
    char name[50];
    int age;
    double average_grade;
};

void task5() {
    cout << "=== Задача 5: Работа со структурой Student ===\n";

    Student students[] = {
        {1, "Иван Петров", 20, 4.5},
        {2, "Мария Сидорова", 19, 4.8},
        {3, "Алексей Иванов", 21, 4.2}
    };

    // Запись в файл
    ofstream outFile("students.dat", ios::binary);
    for (int i = 0; i < 3; i++) {
        outFile.write(reinterpret_cast<char*>(&students[i]), sizeof(Student));
    }
    outFile.close();

    // Чтение из файла
    ifstream inFile("students.dat", ios::binary);

    // Определяем количество студентов
    inFile.seekg(0, ios::end);
    streampos fileSize = inFile.tellg();
    int studentCount = fileSize / sizeof(Student);
    inFile.seekg(0, ios::beg);

    cout << "Всего студентов в файле: " << studentCount << endl;
    cout << "\nСписок студентов:\n";
    cout << "========================================\n";

    Student currentStudent;
    double maxGrade = 0;
    string topStudent;

    for (int i = 0; i < studentCount; i++) {
        inFile.read(reinterpret_cast<char*>(&currentStudent), sizeof(Student));

        cout << "ID: " << currentStudent.id << endl;
        cout << "Имя: " << currentStudent.name << endl;
        cout << "Возраст: " << currentStudent.age << endl;
        cout << "Средний балл: " << currentStudent.average_grade << endl;
        cout << "----------------------------------------\n";

        if (currentStudent.average_grade > maxGrade) {
            maxGrade = currentStudent.average_grade;
            topStudent = currentStudent.name;
        }
    }

    inFile.close();

    cout << "\nЛучший студент: " << topStudent
        << " (средний балл: " << maxGrade << ")\n\n";
}

// Задача 6. Создание CSV файла
void task6() {
    cout << "=== Задача 6: Создание CSV файла с товарами ===\n";

    srand(time(0)); // Инициализация генератора случайных чисел

    ofstream csvFile("products.csv");

    // Заголовки
    csvFile << "id,name,category,price,quantity\n";

    // Массивы для случайных данных
    string categories[] = { "Электроника", "Одежда", "Книги", "Продукты", "Спорт" };
    string products[] = { "Ноутбук", "Смартфон", "Футболка", "Джинсы",
                        "Книга", "Наушники", "Хлеб", "Молоко", "Мяч", "Кроссовки" };

    // Генерация 20 товаров
    for (int i = 1; i <= 20; i++) {
        string name = products[rand() % 10] + " " + to_string(i);
        string category = categories[rand() % 5];
        double price = 100 + rand() % 9900; // 100-10000
        int quantity = 1 + rand() % 100; // 1-100

        csvFile << i << ","
            << name << ","
            << category << ","
            << fixed << setprecision(2) << price << ","
            << quantity << "\n";
    }

    csvFile.close();

    // Проверка файла
    ifstream checkFile("products.csv");
    int lines = 0;
    string line;

    while (getline(checkFile, line)) {
        lines++;
    }
    checkFile.close();

    cout << "Файл products.csv создан\n";
    cout << "Количество записей: " << lines - 1 << " (плюс заголовок)\n\n";
}

// Задача 7. Анализ CSV файла
struct Product {
    int id;
    string name;
    string category;
    double price;
    int quantity;
};

void task7() {
    cout << "=== Задача 7: Анализ CSV файла ===\n";

    ifstream csvFile("products.csv");
    if (!csvFile.is_open()) {
        cerr << "Файл products.csv не найден\n";
        return;
    }

    vector<Product> products;
    string line;

    // Пропускаем заголовок
    getline(csvFile, line);

    // Читаем данные
    while (getline(csvFile, line)) {
        stringstream ss(line);
        string token;
        Product p;

        // ID
        getline(ss, token, ',');
        p.id = stoi(token);

        // Название
        getline(ss, p.name, ',');

        // Категория
        getline(ss, p.category, ',');

        // Цена
        getline(ss, token, ',');
        p.price = stod(token);

        // Количество
        getline(ss, token, ',');
        p.quantity = stoi(token);

        products.push_back(p);
    }
    csvFile.close();

    // Анализ
    double totalValue = 0;
    int totalQuantity = 0;
    Product cheapest = products[0];
    Product mostExpensive = products[0];

    cout << "\nСписок товаров:\n";
    cout << "=================================================================\n";
    for (const auto& p : products) {
        cout << setw(3) << p.id << " | "
            << setw(20) << left << p.name.substr(0, 20) << " | "
            << setw(12) << p.category << " | "
            << setw(8) << right << fixed << setprecision(2) << p.price << " | "
            << setw(4) << p.quantity << " | "
            << setw(10) << fixed << setprecision(2) << (p.price * p.quantity)
            << " руб.\n";

        totalValue += p.price * p.quantity;
        totalQuantity += p.quantity;

        if (p.price < cheapest.price) cheapest = p;
        if (p.price > mostExpensive.price) mostExpensive = p;
    }

    cout << "\nСтатистика:\n";
    cout << "Общая стоимость товаров: " << fixed << setprecision(2)
        << totalValue << " руб.\n";
    cout << "Общее количество товаров: " << totalQuantity << " шт.\n";
    cout << "Самый дорогой товар: " << mostExpensive.name
        << " (" << mostExpensive.price << " руб.)\n";
    cout << "Самый дешевый товар: " << cheapest.name
        << " (" << cheapest.price << " руб.)\n\n";
}

// Задача 8. Фильтрация товаров с лямбдами
void task8() {
    cout << "=== Задача 8: Фильтрация товаров ===\n";

    // Читаем данные (используем код из задачи 7)
    ifstream csvFile("products.csv");
    if (!csvFile.is_open()) {
        cerr << "Файл не найден\n";
        return;
    }

    vector<Product> products;
    string line;
    getline(csvFile, line); // Пропускаем заголовок

    while (getline(csvFile, line)) {
        stringstream ss(line);
        string token;
        Product p;

        getline(ss, token, ',');
        p.id = stoi(token);
        getline(ss, p.name, ',');
        getline(ss, p.category, ',');
        getline(ss, token, ',');
        p.price = stod(token);
        getline(ss, token, ',');
        p.quantity = stoi(token);

        products.push_back(p);
    }
    csvFile.close();

    // Лямбда-функции для фильтрации
    auto expensiveFilter = [](const Product& p) { return p.price > 5000; };
    auto electronicsFilter = [](const Product& p) { return p.category == "Электроника"; };
    auto inStockFilter = [](const Product& p) { return p.quantity > 10; };

    cout << "\nВыберите фильтр:\n";
    cout << "1. Товары дороже 5000 руб.\n";
    cout << "2. Электроника\n";
    cout << "3. В наличии более 10 шт.\n";
    cout << "Ваш выбор: ";

    int choice;
    cin >> choice;

    vector<Product> filtered;

    // Применяем выбранный фильтр
    switch (choice) {
    case 1:
        copy_if(products.begin(), products.end(), back_inserter(filtered), expensiveFilter);
        break;
    case 2:
        copy_if(products.begin(), products.end(), back_inserter(filtered), electronicsFilter);
        break;
    case 3:
        copy_if(products.begin(), products.end(), back_inserter(filtered), inStockFilter);
        break;
    default:
        cout << "Неверный выбор\n";
        return;
    }

    // Сохраняем отфильтрованные данные
    ofstream outFile("filtered_products.csv");
    outFile << "id,name,category,price,quantity\n";

    for (const auto& p : filtered) {
        outFile << p.id << "," << p.name << "," << p.category << ","
            << fixed << setprecision(2) << p.price << "," << p.quantity << "\n";
    }
    outFile.close();

    cout << "\nНайдено товаров: " << filtered.size() << endl;
    cout << "Результаты сохранены в filtered_products.csv\n\n";
}

// Задача 9. Сортировка товаров
void task9() {
    cout << "=== Задача 9: Сортировка товаров ===\n";

    // Читаем данные
    ifstream csvFile("products.csv");
    if (!csvFile.is_open()) {
        cerr << "Файл не найден\n";
        return;
    }

    vector<Product> products;
    string line;
    getline(csvFile, line);

    while (getline(csvFile, line)) {
        stringstream ss(line);
        string token;
        Product p;

        getline(ss, token, ',');
        p.id = stoi(token);
        getline(ss, p.name, ',');
        getline(ss, p.category, ',');
        getline(ss, token, ',');
        p.price = stod(token);
        getline(ss, token, ',');
        p.quantity = stoi(token);

        products.push_back(p);
    }
    csvFile.close();

    cout << "\nВыберите тип сортировки:\n";
    cout << "1. По цене (возрастание)\n";
    cout << "2. По цене (убывание)\n";
    cout << "3. По названию (А-Я)\n";
    cout << "4. По количеству (убывание)\n";
    cout << "Ваш выбор: ";

    int choice;
    cin >> choice;

    // Лямбда-функции для сортировки
    switch (choice) {
    case 1:
        sort(products.begin(), products.end(),
            [](const Product& a, const Product& b) { return a.price < b.price; });
        break;
    case 2:
        sort(products.begin(), products.end(),
            [](const Product& a, const Product& b) { return a.price > b.price; });
        break;
    case 3:
        sort(products.begin(), products.end(),
            [](const Product& a, const Product& b) { return a.name < b.name; });
        break;
    case 4:
        sort(products.begin(), products.end(),
            [](const Product& a, const Product& b) { return a.quantity > b.quantity; });
        break;
    default:
        cout << "Неверный выбор\n";
        return;
    }

    // Сохраняем отсортированные данные
    ofstream outFile("sorted_products.csv");
    outFile << "id,name,category,price,quantity\n";

    for (const auto& p : products) {
        outFile << p.id << "," << p.name << "," << p.category << ","
            << fixed << setprecision(2) << p.price << "," << p.quantity << "\n";
    }
    outFile.close();

    cout << "\nСортировка завершена\n";
    cout << "Результаты сохранены в sorted_products.csv\n\n";
}

// Задача 10. Работа с JSON конфигурацией
void task10() {
    cout << "=== Задача 10: Работа с JSON конфигурацией ===\n";

    // Создание конфигурации
    ofstream jsonFile("config.json");
    jsonFile << "{\n";
    jsonFile << "  \"app_name\": \"My Application\",\n";
    jsonFile << "  \"version\": \"1.0.0\",\n";
    jsonFile << "  \"settings\": {\n";
    jsonFile << "    \"max_connections\": 100,\n";
    jsonFile << "    \"timeout\": 30,\n";
    jsonFile << "    \"debug_mode\": true\n";
    jsonFile << "  },\n";
    jsonFile << "  \"database\": {\n";
    jsonFile << "    \"host\": \"localhost\",\n";
    jsonFile << "    \"port\": 5432,\n";
    jsonFile << "    \"username\": \"admin\"\n";
    jsonFile << "  }\n";
    jsonFile << "}";
    jsonFile.close();

    cout << "Файл config.json создан\n\n";

    // Чтение и изменение конфигурации
    ifstream inFile("config.json");
    vector<string> lines;

    while (getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();

    // Изменяем timeout
    cout << "Изменяем timeout с 30 на 60...\n";

    for (auto& l : lines) {
        if (l.find("\"timeout\":") != string::npos) {
            size_t pos = l.find("30");
            if (pos != string::npos) {
                l.replace(pos, 2, "60");
            }
        }
    }

    // Записываем обратно
    ofstream outFile("config.json");
    for (const auto& l : lines) {
        outFile << l << "\n";
    }
    outFile.close();

    cout << "Конфигурация обновлена\n\n";
}

// Задача 11. Обработчик данных с датчиков
void task11() {
    cout << "=== Задача 11: Обработчик данных с датчиков ===\n";

    // Создаем тестовые данные
    ofstream sensorFile("sensor_data.txt");
    sensorFile << "25.3\n";
    sensorFile << "-12.7\n";
    sensorFile << "38.9\n";
    sensorFile << "999.9\n";  // ошибка датчика
    sensorFile << "22.1\n";
    sensorFile << "-60.5\n";  // некорректное значение
    sensorFile << "18.7\n";
    sensorFile << "45.2\n";
    sensorFile << "-5.3\n";
    sensorFile << "200.0\n";  // ошибка
    sensorFile.close();

    // Читаем данные
    ifstream inFile("sensor_data.txt");
    vector<double> temperatures;
    double temp;

    while (inFile >> temp) {
        temperatures.push_back(temp);
    }
    inFile.close();

    cout << "Всего измерений: " << temperatures.size() << endl;
    cout << "Исходные данные: ";
    for (double t : temperatures) cout << t << " ";
    cout << endl;

    // Фильтрация с помощью лямбды
    auto validTemp = [](double t) { return t >= -50 && t <= 50; };

    vector<double> filtered;
    copy_if(temperatures.begin(), temperatures.end(),
        back_inserter(filtered), validTemp);

    // Вычисляем среднюю температуру
    double sum = 0;
    for (double t : filtered) sum += t;
    double average = filtered.empty() ? 0 : sum / filtered.size();

    // Сохраняем отфильтрованные данные
    ofstream outFile("filtered_sensor_data.txt");
    outFile << "Отфильтрованные данные датчиков\n";
    outFile << "================================\n";
    for (double t : filtered) {
        outFile << t << "\n";
    }
    outFile << "================================\n";
    outFile << "Корректных измерений: " << filtered.size() << "\n";
    outFile << "Средняя температура: " << fixed << setprecision(2)
        << average << "°C\n";
    outFile.close();

    cout << "\nКорректных измерений: " << filtered.size() << endl;
    cout << "Средняя температура: " << fixed << setprecision(2)
        << average << "°C\n";
    cout << "Результаты в filtered_sensor_data.txt\n\n";
}

// Задача 12. Сравнение скорости записи
#include <chrono>

void task12() {
    cout << "=== Задача 12: Сравнение скорости записи ===\n";

    // Создаем вектор с данными
    vector<int> data;
    for (int i = 0; i < 100000; i++) {
        data.push_back(rand() % 1000);
    }

    // Лямбда для измерения времени
    auto measureTime = [](const function<void()>& func) {
        auto start = chrono::high_resolution_clock::now();
        func();
        auto end = chrono::high_resolution_clock::now();
        return chrono::duration<double>(end - start).count();
        };

    // Метод 1: Запись по одному числу
    double time1 = measureTime([&]() {
        ofstream file1("method1.bin", ios::binary);
        for (int num : data) {
            file1.write(reinterpret_cast<char*>(&num), sizeof(num));
        }
        file1.close();
        });

    // Метод 2: Запись всех чисел сразу
    double time2 = measureTime([&]() {
        ofstream file2("method2.bin", ios::binary);
        file2.write(reinterpret_cast<char*>(data.data()),
            data.size() * sizeof(int));
        file2.close();
        });

    cout << "\nРезультаты сравнения:\n";
    cout << "Метод 1 (по одному): " << fixed << setprecision(4)
        << time1 << " секунд\n";
    cout << "Мод 2 (все сразу): " << time2 << " секунд\n";

    if (time1 < time2) {
        cout << "Метод 1 быстрее на " << (time2 - time1) << " секунд\n";
    }
    else {
        cout << "Метод 2 быстрее на " << (time1 - time2) << " секунд\n";
    }

    // Удаляем временные файлы
    remove("method1.bin");
    remove("method2.bin");

    cout << "\nТестовые файлы удалены\n\n";
}

int main() {
    // Выполняем все задачи
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

    cout << "Все задачи выполнены!\n";
    return 0;
}