#include <iostream>

using namespace std;

bool ehprimo(int x) {
    int qtddivisores = 0;

    for (int i = 1; i <= x; i++) {
        if (x % i == 0) {
            qtddivisores++;
        }
    }

    if (qtddivisores == 2) {
        return true;
    } else {
        return false;
    }
}

int main() {
    int a, b, somaprimos = 0;

    cin >> a >> b;

    if (a > b) {
        int aux = b;
        b = a;
        a = aux;
    }

    for (int i = a; i <= b; i++) {
        if (ehprimo(i)) {
            somaprimos += i;
        }
    }

    cout << somaprimos << endl;

    return 0;
}