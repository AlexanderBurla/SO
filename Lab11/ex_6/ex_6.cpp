#include <thread>
#include <condition_variable>
#include <mutex>
#include <chrono>
#include <queue>
#include <iostream>
using namespace std;
mutex mt;
condition_variable variabila_conditie;
int main()
{
    bool notificare = false;
    int valoare = 100;
    thread afisare([&]()
                   {
/*
unique_lock<mutex> incuietoare(mt);
while (!notificare) {
variabila_conditie.wait(incuietoare);
}
*/
cout << "Valoarea este " << valoare << endl; });
    thread atribuire([&]()
                     {
valoare = 20;
/*
notificare = true;
variabila_conditie.notify_one();
*/ });
    afisare.join();
    atribuire.join();
    return 0;
}