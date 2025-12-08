
#include <iostream>
#include <string>
using namespace std;

struct Book {
    string title;
    string author;
    int year;
    string genre;
};

Book library[100]; // Простой массив книг
int bookCount = 0; // Количество книг

void addBook() {
    cout << "\nДобавить книгу:\n";
    cout << "Название: ";
    cin.ignore();
    getline(cin, library[bookCount].title);
    cout << "Автор: ";
    getline(cin, library[bookCount].author);
    cout << "Год: ";
    cin >> library[bookCount].year;
    cout << "Жанр: ";
    cin >> library[bookCount].genre;
    bookCount++;
    cout << "Книга добавлена!\n";
}

void removeBook() {
    string title;
    cout << "\nУдалить книгу:\n";
    cout << "Название: ";
    cin.ignore();
    getline(cin, title);

    for (int i = 0; i < bookCount; i++) {
        if (library[i].title == title) {
            // Сдвигаем все книги после удаленной
            for (int j = i; j < bookCount - 1; j++) {
                library[j] = library[j + 1];
            }
            bookCount--;
            cout << "Книга удалена!\n";
            return;
        }
    }
    cout << "Книга не найдена!\n";
}

void findBooks() {
    string author;
    cout << "\nНайти книги автора:\n";
    cout << "Автор: ";
    cin.ignore();
    getline(cin, author);

    cout << "\nНайденные книги:\n";
    bool found = false;
    for (int i = 0; i < bookCount; i++) {
        if (library[i].author == author) {
            cout << "- " << library[i].title
                << " (" << library[i].year
                << "), жанр: " << library[i].genre << endl;
            found = true;
        }
    }
    if (!found) cout << "Книги не найдены\n";
}

void showAllBooks() {
    cout << "\nВсе книги (" << bookCount << "):\n";
    for (int i = 0; i < bookCount; i++) {
        cout << i + 1 << ". " << library[i].title
            << " - " << library[i].author
            << " (" << library[i].year
            << "), жанр: " << library[i].genre << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    int choice;

    do {
        cout << "\nБиблиотека:\n";
        cout << "1. Добавить книгу\n";
        cout << "2. Удалить книгу\n";
        cout << "3. Найти по автору\n";
        cout << "4. Показать все\n";
        cout << "5. Выйти\n";
        cout << "Выбор: ";
        cin >> choice;

        switch (choice) {
        case 1: addBook(); break;
        case 2: removeBook(); break;
        case 3: findBooks(); break;
        case 4: showAllBooks(); break;
        case 5: cout << "Выход\n"; break;
        default: cout << "Неверный выбор!\n";
        }
    } while (choice != 5);

    return 0;
}