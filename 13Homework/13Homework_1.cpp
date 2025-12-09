#include <iostream>
#include <string>
using namespace std;

// Класс Книга
class Book {
private:
    string title;    
    string author;   
    int year;     

public:
    // Конструктор - создает книгу с данными
    Book(string t, string a, int y) {
        title = t;
        author = a;
        year = y;
    }

    // Метод для вывода информации
    void displayInfo() {
        cout << "Название: " << title
            << ", Автор: " << author
            << ", Год выпуска: " << year << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    // Создаем книгу
    Book myBook("Гарри Поттер", "Джоан Роулинг", 1997);

    // Выводим информацию
    myBook.displayInfo();

    return 0;
}
