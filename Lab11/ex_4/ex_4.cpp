#include <vector>
#include <thread>
#include <atomic>
#include <iostream>
using namespace std;
atomic<int> Suma(0);
void patrat(int val)
{
    this_thread::sleep_for(std::chrono::microseconds(15));
    Suma += val * val;
}
int main()
{
    vector<thread> fire;
    for (int index = 1; index <= 20; index++)
    {
        fire.push_back(thread(&patrat, index));
    }
    for (auto &fir : fire)
    {
        fir.join();
    }
    cout << " Suma = " << Suma << endl;
    return 0;
}