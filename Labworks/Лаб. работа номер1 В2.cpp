#include <iostream>
using namespace std;

int main()
{
    float a = 0;
    cout << "Write the level of patrol in your car:";
    cin >> a;
    if (a > 50)
    {
        cout << "You have enough patrol"<<endl;
    }
    if (a>20 and a<50) {
        cout << "You should gas up your car "<<endl;

    }
    if (a < 20) {
        cout << "You haven't got enough patrol. You must refuel your car"<< endl ;
    }

    float b = 0;
    do
    {
        cout << "Write the number of liters you want to fill:";
        cin >> b;
    }
    while(b>0);
    if (b <= 0) {


        cout << "Ops... You write the wrong number";
    }
     
        return 0;
}

