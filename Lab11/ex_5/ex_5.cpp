#include <iostream>
#include <future>
#include <chrono>
using namespace std;
int patrat(int val)
{
    return val * val;
}
int main()
{
    auto ret = async(&patrat, 10);
    int valoare = ret.get();
    cout << "Firul a returnat valoarea: " << valoare << endl;
    return 0;
}