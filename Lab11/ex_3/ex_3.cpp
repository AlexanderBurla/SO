#include <mutex>
#include <thread>
#include <vector>
#include <iostream>
using namespace std;
int Suma = 0;
mutex mt_suma;
void patrat(int val)
{
    this_thread::sleep_for(std::chrono::microseconds(15));
    int tmp = val * val;
    mt_suma.lock();
    Suma += tmp;
    mt_suma.unlock();
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