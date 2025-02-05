#include <thread>
#include <condition_variable>
#include <mutex>
#include <chrono>
#include <queue>
#include <iostream>
using namespace std;
int main()
{
    int nr_produse = 0;
    bool gata = false;
    queue<int> produse;
    thread producator([&]()
                      {
for (int i = 0; i < 500; ++i) {
produse.push(i);
nr_produse++;
}
gata = true; });
    thread consumator([&]()
                      {
while (!gata) {
while (!produse.empty()) {
produse.pop();
nr_produse--;
}
} });
    producator.join();
    consumator.join();
    cout << "Numar produse: " << nr_produse << endl;
}