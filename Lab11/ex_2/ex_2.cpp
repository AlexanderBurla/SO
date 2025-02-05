#include <iostream>
#include <vector>
#include <thread>
using namespace std;
int Suma = 0;
void patrat(int val)
{
    this_thread::sleep_for(std::chrono::microseconds(15));
    Suma += val * val;
}
int main()
{
    vector<thread> fire;
    for (int i = 1; i <= 20; i++)
    {
        fire.push_back(thread(&patrat, i));
    }
    for (auto &fir : fire)
    {
        fir.join();
    }
    cout << " Suma = " << Suma << endl;
    return 0;
}

//chmod +x script.sh
//./script.sh
