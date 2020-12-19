#include <iostream>

using namespace std;

void abertura(int m) {
    cout << "Tabuada do " << m << "\n\n";
}

int main() {
    int multiplicador = 2;

    abertura(multiplicador);

    for (int i = 1; i <= 10; i++) {
        cout << multiplicador << " x " << i << " = " << multiplicador * i << endl;
    }

    return 0;
}