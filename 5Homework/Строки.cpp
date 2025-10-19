#include <iostream> 
#include <cstring> 
#include <cctype> 
#include <string>
#include <set>
using namespace std;

bool isPalindrome(const char* str) {
    int length = strlen(str);
    for (int i = 0; i < length / 2; ++i) {
        if (tolower(str[i]) != tolower(str[length - i - 1])) {
          return false;
       }
    }
    return true;
}

    int main() {
        // задание 1 
        char str[100];
        cout << "Write our sentence: ";
        cin.getline(str, 100);


        if (isPalindrome(str)) {
            cout << "It is polindrom" << endl;
        }
        else {
            cout << "It is not polindrom" <<endl;

        }
        // задание 2
        string s;
        cout << "Write sentence ";
        getline(cin, s);

        set<char> unique(s.begin(), s.end());

        cout << "Enter" << unique.size() << " (simbols: ";
        auto it = unique.begin();
        if (it != unique.end()) {
            cout << *it;
            while (++it != unique.end()) {
                cout << ", " << *it;
            }
        }
        cout << ")" << endl;

        // задание 3
        char str[100];
        cout << "Write our sentence: ";
        cin.getline(str, 100);
        int j = 0;
        for (int i = 0; str[i] != '\0' ; i++) {
            if (!isdigit(str[i])) {
                str[j] = str[i];
                j++;
            }
        }
        str[j] = '\0';
   
        cout << str;

        // задание 4

       char A[100], B[100];

        cout << "write line A: ";
        cin.getline(A, 100);
        cout << "write line B: ";
        cin.getline(B, 100);
        bool allFound = true;
        for (int i = 0; B[i] != '\0'; i++) {
            bool found = false;
            for (int j = 0; A[j] != '\0'; j++) {
                if (A[j] == B[i]) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                allFound = false;
                break;
            }
        }
        if (allFound) {
            cout << "yes";
        }
        else {
            cout << "no";
        }

       // задание 5
        string s;
        cout << "Введите строку: ";
        getline(cin, s);
        int vowels = 0, consonants = 0;
        for (char c : s) {
            char upperChar = toupper(c);
            if (isalpha(upperChar)) {
                if (upperChar == 'A' || upperChar == 'E' || upperChar == 'I' ||
                    upperChar == 'O' || upperChar == 'U' || upperChar == 'Y') {
                    vowels++;
                }
                else {
                    consonants++;
                }
            }
        }
        cout << "vowels " << vowels << endl;
        cout << "consonants: " << consonants << endl;

   // задание 6
        string text;
        int shift;

        cout << "text: ";
        getline(cin, text);
        cout << "shift: ";
        cin >> shift;

        for (char& c : text) {
            if (isupper(c)) {
                c = (c - 'A' + shift) % 26 + 'A';
            }
            else if (islower(c)) {
                c = (c - 'a' + shift) + 'a';
            }
        }

        cout << "new one: " << text << endl;

        // задание 7
        string s;
        cout << "write line: ";
        cin >> s;

        string result = "";
        int count = 1;

        for (int i = 1; i <= s.length(); i++) {
            if (i < s.length() && s[i] == s[i - 1]) {
                count++;
            }
            else {
                result += s[i - 1] + to_string(count);
                count = 1;
            }
        }

        cout << "new line: " << result << endl;


        // задание 8
        string text;
        cout << "write text: ";
        getline(cin, text);

        bool newSentence = true;

        for (char& c : text) {
            if (newSentence && isalpha(c)) {
                c = toupper(c);
                newSentence = false;
            }
            else {
                c = tolower(c);
            }

            if (c == '.' || c == '!' || c == '?') {
                newSentence = true;
            }
        }

        cout << "new text: " << text << endl;

       // задание 9 
        const int MAX_SIZE = 100;
        char str1[MAX_SIZE], str2[MAX_SIZE];

        cout << "write 1 line: ";
        cin.getline(str1, MAX_SIZE);
        cout << "write 2 line: ";
        cin.getline(str2, MAX_SIZE);

        int len1 = strlen(str1);
        int len2 = strlen(str2);

        int dp[MAX_SIZE][MAX_SIZE] = { 0 };
        int maxLen = 0, endPos = 0;

        for (int i = 1; i <= len1; i++) {
            for (int j = 1; j <= len2; j++) {
                if (str1[i - 1] == str2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    if (dp[i][j] > maxLen) {
                        maxLen = dp[i][j];
                        endPos = i - 1;
                    }
                }
            }
        }

        if (maxLen > 0) {
            cout << "the biggest line: ";
            for (int i = endPos - maxLen + 1; i <= endPos; i++) {
                cout << str1[i];
            }
            cout << endl;
            cout << "lenght: " << maxLen << endl;
        }
        else {
            cout << "Ops..." << endl;
        }
        // задание 10

        string text;
        cout << "write your line: ";
        getline(cin, text);
        int start = 0;
        for (int i = 0; i <= text.length(); i++) {
            if (i == text.length() || text[i] == ' ') {
                reverse(text.begin() + start, text.begin() + i);
                start = i + 1;
            }
        }
        cout << "result: " << text << endl;

        //задание 11
        string s;
        int k;
        cout << "write line: ";
        cin >> s;
        cout << "write k: ";
        cin >> k;

        cout << "substrings " << k << " with unique symbols:" << endl;

        for (int i = 0; i <= s.length() - k; i++) {
            string substring = s.substr(i, k);
            set<char> uniqueChars(substring.begin(), substring.end());

            if (uniqueChars.size() == k) {
                cout << substring << endl;
            }
        }

        return 0;
    }

