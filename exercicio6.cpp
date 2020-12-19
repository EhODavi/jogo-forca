#include <iostream>

using namespace std;

int somavetor(int vetorinteiros[], int n) {
    int soma = 0;

    for (int i = 0; i < n; i++) {
        soma += vetorinteiros[i];
    }

    return soma;
}

int main() {
    int n;

    cin >> n;

    int vetorinteiros[n];

    for (int i = 0; i < n; i++) {
        cin >> vetorinteiros[i];
    }

    cout << somavetor(vetorinteiros, n) << endl;

    return 0;
}