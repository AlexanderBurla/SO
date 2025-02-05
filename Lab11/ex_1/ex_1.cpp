#include <thread>
#include <iostream>
using namespace std;
void functie(int val) // functia care implementeaza firul de executie
{
    cout << "In firul de executie " << val << endl;
}
int main()
{
    thread fir(&functie, 1234);
    fir.join(); // se asteata terminarea firului de executie
    cout << "In afara firului de executie" << endl;
    getchar();
    return 0;
}

//g++ ex_2.cpp -o e