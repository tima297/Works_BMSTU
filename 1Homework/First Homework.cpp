#include <iostream>
using namespace std;

int main()
{
    int i;
    int s;
    int x, b,y, r,k,t;
    char c;
    int a = 0;

    //1
    cout << "Write number in centimeters:\n";
     cin >> a;
     b = a / 100;
     t = a % 100; 
     cout << b << " m and "<< t << " cm"<< endl;


//2
     cout << "Write 2 numbers of width and length :\n";
     cin >> x >> y;
    c = x * y;
   cout << "The size of your square is: " << c << " cm "<< endl;


   //3
   cout << "Write temperature in calcium: \n";
   cin >> k;
   int F=((k*9)/5)+32 ;
   cout << "Your temperature in kelvin is: " << F << endl;

   //4
   cout << "Write number :\n";
   cin >> r;
   if (r % 2 == 0 ) {
       cout << "This number is chetnoe \n";
   }
   else
       cout << "This number is nechetnoe " << endl;

   
   //5
    cout << "Write number :\n";
    cin >> r;
    if (r%5==0 and r%3!=0) {
         cout << "This number is divided by 5 \n";
     } 
    if (r % 3==0 and r%5!=0) {
         cout << "This number is divided by 3 "<<endl;

     }
    if (r % 3 == 0 and r % 5 == 0) {
        cout << "This number is divided by 3 and 5 " << endl;

    }
    else
        cout << " Ops..Nothing";

    //6
    cout << "Write number :\n";
    cin >> r;
    if ( r<18) {
        cout << "You are a child \n";
    }
    if (r> 18 and r<60) {
        cout << "You are an adult " << endl;

    }
    if (r>60) {
        cout << "You are old " << endl;

    }
    //7
    cout << "Write random number: \n";
    cin >> k;
    for (int i = 1; i <= k; i++) {
        a = i * i;
        cout << a << endl;
    }
    //8
    cout << "Write the length of your sentence"<<endl;
    cin >> a;
    char* array = new char[a];
    cout << "Write yor sentence letter by letter "<<endl;
    for (int i = 0; i < a; i++) {
        cout << " write " << i + 1 << " letter:" << endl;
        cin >> array[i];

    }
    cout << "Your sentence: ";
    for (int i = 0; i < a; i++) {
        cout << array[i];
    }
    for (int i = 0; i < a; i++) {
        s = 0;
        if (array[i] = ('i', 'e' , 'u' , 'o' , 'a' ));
        s += 1;


    }
    cout << "The amount of vocals:"<< s <<endl;

   
    //8 v2 
    cout << "inter your sentence: ";

    while (cin.get(c) && c != '\n') {

        if (c == 'a' || c == 'A'||
            c == 'e'  ||c == 'E'||
            c == 'i'  ||c == 'I'||
            c == 'o'  ||c == 'O'||
            c == 'u' || c == 'U') {
            a++;
        }
    }

    cout << "the number of vocals" << a << endl;


    //9 

    cout << "Write random number: ";
    cin >> a;
    int sum = 0;
    for (int i = 1; i <= a; i++) {
        if (i % 2 == 0 or i % 5 == 0) {
            cout << " The number: " << i << endl;
            sum = sum + i;
        }

    }

    cout << " Result of summ: " << sum<< endl;


    //10
    cout << "Write number :\n";
    cin >> r;
    if (r <0 ) {
        cout << "Number is smaller than zero \n";
    }
    if (r == 0) {
        cout << "It is zero" << endl;

    }
    if (r > 0) {
        cout << "Number is bigger than zero " << endl;

    }
    //11
    cout << "ASCII table (32-126):" << endl;
    cout << "Cod\tSimbol" << endl;
    cout << "---\t------" << endl;

    for (int i = 32; i <= 126; i++) {
        cout << i << "\t'" << static_cast<char>(i) << "'" << endl;
    }
    


    return(0);


}




  



