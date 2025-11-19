#include <iostream>
#include <cstring>


using namespace std;

int main() {
    setlocale(LC_ALL, "RU");
    char sent[1000];

    cout << "Введите строку из 10 слов: ";
    cin.getline(sent, 1000);
    cout << "Строка:" << sent << endl;

    // 1. Количество слов, оканчивающихся на 'a'
    int countEndA = 0;
    const char* ptr1 = sent;

    while (*ptr1 != '\0') {
        // Пропускаем пробелы
        while (*ptr1 == ' ') {
            ptr1++;
        }

        if (*ptr1 == '\0') break;

        // Находим конец слова
        while (*ptr1 != ' ' && *ptr1 != '\0') {
            ptr1++;
        }

        char lastChar = *(ptr1 - 1);
        if (lastChar == 'a') {
            countEndA++;
        }


        if (*ptr1 == '\0') break;
        ptr1++;
    }
    cout << "1. Количество слов, оканчивающихся на 'a': " << countEndA << endl;

    // 2. Длина самого короткого слова
    int minlength = 1000;
    const char* ptr2 = sent;

    while (*ptr2 != '\0') {
        while (*ptr2 == ' ') {
            ptr2++;
        }

        if (*ptr2 == '\0') break;

        // Находим первый символ слова (начало слова)
        const char* firstCharPtr = ptr2;

        // Находим последний символ слова (конец слова)
        while (*ptr2 != ' ' && *ptr2 != '\0') {
            ptr2++;
        }

        // Указатель на последний символ слова
        const char* lastCharPtr = ptr2 - 1;

        // Длина слова
        int wordlength = lastCharPtr - firstCharPtr + 1;

        // Обновляем самую короткую длину
        if (wordlength > 0 && wordlength < minlength) {
            minlength = wordlength;
        }

        if (*ptr2 == '\0') break;
        ptr2++;
    }

    cout << "2. Длина самого короткого слова: " << minlength << endl;


    // 3. Количество букв 'b' во втором слове
    int countB = 0;
    int wordCount = 0;
    const char* ptr3 = sent;

    while (*ptr3 != '\0' && wordCount < 2) {
        // Пропускаем пробелы
        while (*ptr3 == ' ') {
            ptr3++;
        }

        if (*ptr3 == '\0') break;

        wordCount++;

        // Если это второе слово
        if (wordCount == 2) {
            // Считаем буквы 'b' в этом слове
            while (*ptr3 != ' ' && *ptr3 != '\0') {
                if (*ptr3 == 'b') {
                    countB++;
                }
                ptr3++;
            }
            break;
        }
        else {
            // Пропускаем первое слово
            while (*ptr3 != ' ' && *ptr3 != '\0') {
                ptr3++;
            }
        }

        if (*ptr3 == '\0') break;
        ptr3++;
    }
    cout << "3. Количество букв 'b' во втором слове: " << countB << endl;


    // 4. Замена заглавных букв на строчные
    char lowerSent[1000];

    char* dest = lowerSent;

    // Копируем строку с помощью strcpy
    strcpy_s(lowerSent, sent);

    // Преобразуем к нижнему регистру
    char* ptr4 = lowerSent;
    while (*ptr4 != '\0') {
        if (*ptr4 >= 'A' && *ptr4 <= 'Z') {
            *ptr4 = *ptr4 + ('a' - 'A');
        }
        ptr4++;
    }
    cout << "4. Строка в нижнем регистре: " << lowerSent << endl;


    // 5. Количество слов с одинаковыми первым и последним символами
    int countFirstLast = 0;
    const char* ptr5 = sent;

    while (*ptr5 != '\0') {
        // Пропускаем пробелы
        while (*ptr5 == ' ') {
            ptr5++;
        }

        if (*ptr5 == '\0') break;

        // Находим начало слова
        const char* wordStart = ptr5;
        char firstChar = *ptr5;

        // Находим конец слова
        while (*ptr5 != ' ' && *ptr5 != '\0') {
            ptr5++;
        }

        // Проверяем последний символ
        if (ptr5 > wordStart) {
            char lastChar = *(ptr5 - 1);
            // Приводим к нижнему регистру для сравнения
            if (firstChar >= 'A' && firstChar <= 'Z') {
                firstChar = firstChar + ('a' - 'A');
            }
            if (lastChar >= 'A' && lastChar <= 'Z') {
                lastChar = lastChar + ('a' - 'A');
            }

            if (firstChar == lastChar) {
                countFirstLast++;
            }
        }

        if (*ptr5 == '\0') break;
        ptr5++;
    }
    cout << "5. Количество слов с одинаковыми первым и последним символами: " << countFirstLast << endl;

    // 6.Поиск самой короткой общей подстроки
    char words[10][100];
    int wordCountTotal = 0;
    const char* ptr = sent;

    // Разбиваем на слова
    while (*ptr != '\0' && wordCountTotal < 10) {
        while (*ptr == ' ') ptr++;
        if (*ptr == '\0') break;

        int i = 0;
        while (*ptr != ' ' && *ptr != '\0' && i < 99) {
            words[wordCountTotal][i++] = *ptr++;
        }
        words[wordCountTotal][i] = '\0';
        wordCountTotal++;
    }

    // Ищем самую короткую общую подстроку
    char shortest[100] = "";
    int minLen = 1000;

    // Проверяем все пары слов
    for (int i = 0; i < wordCountTotal; i++) {
        for (int j = i + 1; j < wordCountTotal; j++) {
            char word1[100], word2[100];
            strcpy_s(word1, words[i]);
            strcpy_s(word2, words[j]);

            // Ищем общие подстроки начиная с самых коротких
            for (int len = 1; len <= strlen(word1) && len < minLen; len++) {
                for (int pos1 = 0; pos1 <= strlen(word1) - len; pos1++) {
                    // Извлекаем подстроку из первого слова
                    char substr[100];
                    strncpy_s(substr, word1 + pos1, len);
                    substr[len] = '\0';

                    // Есть ли эта подстрока во втором слове
                    if (strstr(word2, substr) != nullptr) {
                        if (len < minLen) {
                            minLen = len;
                            strcpy_s(shortest, substr);
                        }
                    }
                }
            }
        }
    }

    if (minLen < 1000) {
        cout << "6. Самая короткая общая подстрока: \"" << shortest << "\" (длина: " << minLen << ")" << endl;
    }
    else {
        cout << "6. Общая подстрока не найдена" << endl;
    }


    return 0;
}
