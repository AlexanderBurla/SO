#include <iostream>
#include <future>
#include <vector>
using namespace std;

// Funcție care calculează pătratul unui număr
int patrat(int val) {
    return val * val;
}

int main() {
    vector<future<int>> futures; // Vector de obiecte future<int>
    int suma = 0;

    // Lansează sarcini asincrone pentru a calcula pătratele numerelor de la 1 la 20
    for (int i = 1; i <= 20; ++i) {
        futures.push_back(async(&patrat, i));
    }

    // Iterează prin vectorul de future-uri, extrage valorile și calculează suma
    for (auto &f : futures) {
        suma += f.get(); // Extrage valoarea calculată și o adaugă la sumă
    }

    // Afișează rezultatul
    cout << "Suma = " << suma << endl;

    return 0;
}
