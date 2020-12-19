#include <iostream>

using namespace std;

long long int potencia(int a, int b) {
    long long int resultado = 1;

    for(int i = 0; i < b; i++) {
        resultado *= a;
    }

    return resultado;
}

int main() {
    int a, b;

    cin >> a >> b;

    cout << potencia(a, b) << endl;

    return 0;
}

