#include <iostream>
#include <cstring> 
#include <vector>
using namespace std;

int myStrLen(char* str) {
    char *ptr = str;
    while (*ptr != '\0') {
        ptr++;
    }
    return ptr - str;
}
void myStrCopy(char* destination, const char* source) {
    char* dest_first = destination;
    while (*source != '\0') {
        *destination = *source;
        destination++;
        source++;
    }
    *destination = '\0';
    cout << destination;
}

void myStrCat(char *ptr,  char *ptr1, char *ptr2) {
    char* ptr_first = ptr;
    while (*ptr1 != '\0') {
        *ptr = *ptr1;
        ptr++;
        ptr1++;
    }
    while (*ptr2 != '\0') {
        *ptr = *ptr2;
        ptr++;
        ptr2++;
    }
    *ptr = '\0';
    cout << ptr_first;
}

void myStrCat(char* ptr, char* ptr1, char* ptr2) {
    char* ptr_first = ptr;
    while (*ptr1 != '\0') {
        *ptr = *ptr1;
        ptr++;
        ptr1++;
    }
    while (*ptr2 != '\0') {
        *ptr = *ptr2;
        ptr++;
        ptr2++;
    }
    *ptr = '\0';
    cout << ptr_first;
}

void reverse( char* ptr1) {
    size_t length = strlen(ptr1);
    char* start = ptr1;
    char* end = ptr1 + length - 1; 

    while (start < end) {
        char t = *start;
        *start = *end;
        *end = t;

        start++;
        end--;
    }

    cout << ptr1;
}

  void findSubstring(const char* text, const char* word) {
      int t = 0;
      while (*text != '\0') {
           const char* w = word;
           const char* x = text;
          while (*x == *w && *w != '\0') {
              x++;
              w++;
              if (*w == '\0') {
                  t++;
              }
          }
          text++;
      }

    cout << t;
}


void findSpace( char* text) {
   char* t = text ;
   char* n = text;
      while (*t != '\0') {
          if (*t != ' ') {
              *t = *n;
              n++;
 }
          
          t++;
     
       
      }
      *n = '\0';

    cout << text;
}



void myStrCmp( char* ptr1, char* ptr2) {
    int p1 = 0;   
    int p2 = 0;
    while (*ptr1 != '\0') {
        p1++;
        ptr1++;
    }
    while (*ptr2 != '\0') {
        p2++;
        ptr2++;
    }
    cout << "The amount is:";
    if (p1 == p2) {
        cout << "Equale: 0";
    }
    else if(p1<p2)
    {
        cout << p1-p2;
    }
    else if (p1 > p2)
    {
        cout <<  p1 - p2;
    }
}

void parseTelemetry(const char* p) {


    while (*p != '\0') {

        while (*p == ' ') p++;
        if (*p == '\0') break;

        const char* name_start = p;
        while (*p != ':' && *p != '\0' && *p != ';') p++;
        if (*p != ':') break; 

        const char* name_end = p;
        p++;

        while (*p == ' ') p++;

        const char* value_start = p;
        while (*p != ';' && *p != '\0') p++;
        const char* value_end = p;

        std::cout << "Parameter: ";
        for (const char* c = name_start; c < name_end; c++) {
            std::cout << *c;
        }

        std::cout << " | Value: ";
        for (const char* c = value_start; c < value_end; c++) {
            std::cout << *c;
        }
        std::cout << std::endl;

        if (*p == ';') p++;
    }
}



void computeRMS(const vector<double>& signal) {
    if (signal.empty()) {
        cout << 0.0;
    }

    const double* p = signal.data();
    const double* end = p + signal.size(); 

    double sum_of_squares = 0.0;

    while (p < end) {
        sum_of_squares += (*p) * (*p);
        p++;
    }

   
   double result = sqrt(sum_of_squares / signal.size());
   cout << result;
}

struct Command {
    char name[20];     // название команды (фиксированный буфер)
    int value;         // числовой параметр (0, если нет)
};

void parseCommand(const char* input, std::vector<Command>& buffer) {
    const char* p = input;
    Command cmd = {};  // Инициализируем нулями

    // Пропускаем начальные пробелы
    while (*p == ' ') p++;

    // Читаем имя команды (до пробела или конца строки)
    const char* name_start = p;
    while (*p != ' ' && *p != '\0') p++;

    // Копируем имя команды в буфер
    int name_length = p - name_start;
    if (name_length > 19) name_length = 19;  // Ограничиваем длину
    std::strncpy(cmd.name, name_start, name_length);
    cmd.name[name_length] = '\0';  // Завершаем строку

    // Если есть пробел, читаем число после него
    if (*p == ' ') {
        p++; // Пропускаем пробел

        // Пропускаем пробелы перед числом
        while (*p == ' ') p++;

        // Читаем число
        if (*p >= '0' && *p <= '9') {
            int num = 0;
            while (*p >= '0' && *p <= '9') {
                num = num * 10 + (*p - '0');
                p++;
            }
            cmd.value = num;
        }
    }

    // Добавляем команду в буфер
    buffer.push_back(cmd);
}

void printCommands(const std::vector<Command>& buffer) {
    for (const auto& cmd : buffer) {
        std::cout << "Command: " << cmd.name << ", Value: " << cmd.value << std::endl;
    }
}



int main() {
    // задача 1 
	
    char str[100];
    cout << "write down the sentese: ";
    cin.getline(str, 1000);
    cout << "Sentense: " << str << endl;
    cout << "Length of your sentence:" << myStrLen(str) << endl;
    


    // задача 2
    char str[100];
    char dest[100];
    cout << "write down the sentese: ";
    cin.getline(str, 100);
    cout << "Sentence: " << str << endl;
    cout << "Copy sentence:";
    myStrCopy( dest, str);
    

  // задача 3 
    char str1[100];
    char str2[100];
    char result[100];
    cout << "write down the 1 sentese: ";
    cin.getline(str1, 100);
    cout << "write down the 2 sentese: ";
    cin.getline(str2, 100);
    cout << "New sentence:";
    myStrCat(result, str1, str2);

    // задача 4
    char str1[100];
    char simbol;
    int t = 0;
    cout << "write down the 1 sentese: ";
    cin.getline(str1, 100);
    cout << "write the letter you want to find:";
    cin >> simbol;
    char tolower(char srt1[100]);
    char *ptr = str1;
    while (*ptr != '\0') {
        if (*ptr == simbol) {
            t++;
        }
        ptr++;
    }


    cout << "Amount of yor letter:" << t << endl;


    // задача 5
    char str1[100];
    auto t = ' ';
    cout << "write down the 1 sentese: ";
    cin.getline(str1, 100);
    cout << "write the letter you want to find:";
    char* ptr = str1;
    while (*ptr != '\0') {
        if (*ptr == t) {
            *ptr = '_';
        }
        ptr++;
    }
    cout << "Your sentence: " << str1 << endl;


    // задача 6
    char str[100];
    cout << "write down the sentese: ";
    cin.getline(str, 100);
    cout << "Sentense: " << str << endl;
    cout << "reeversed:";
    reverse(str);

    // задача 8
   char str[100];
    char word[100];
    cout << "write down the sentese: ";
    cin.getline(str, 100);
    cout << "write down the word: ";
    cin.getline(word, 100);
    cout << "Sentense: " << str << endl;
    cout << "how many words:";
    findSubstring(str,word);

    // задача 9
    char str[100];
    char word[100];
    cout << "write down the sentese: ";
    cin.getline(str, 100);
    cout << "Sentense: " << str << endl;
    findSpace(str);


    // задача 10
    char str1[100];
    char str2[100];
    char result[100];
    cout << "write down the 1 sentese: ";
    cin.getline(str1, 100);
    cout << "write down the 2 sentese: ";
    cin.getline(str2, 100);
    myStrCmp(str1, str2);

    // задача 11 и 12
    int n = 0;
    cout << " How many numbers you whant to count:";
    cin >> n;
    vector<int> elements (n);
    for (int i = 0; i < n; i++) {
        cin >> elements[i];

    };
    int* p = elements.data();
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += *p;
        *p = *p + 10;
        p++;
    };

    cout << "Summ: " << sum << endl;
    for (int i = 0; i < n; i++) {
        cout << elements[i] << endl;

    };

     задача 13
    char str1[100];
    cout << "write down the 1 sentese: ";
    cin.getline(str1, 100);
    parseTelemetry(str1);

    // задача 14

    int n = 0;
    cout << " How many numbers you whant to count:";
    cin >> n;
    vector<double> elements(n);
    for (int i = 0; i < n; i++) {
        cin >> elements[i];

    };
   computeRMS(elements);

   // задача 15
   std::vector<Command> buffer;

   parseCommand("FORWARD 10", buffer);
   parseCommand("TURN 90", buffer);
   parseCommand("STOP", buffer);

   printCommands(buffer);

}

