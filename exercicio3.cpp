#include <iostream>

using namespace std;

int main() {
    int x, n, soma = 0;

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> x;

        if (x % 2 == 0) {
            soma += x;
        }
    }

    cout << soma << endl;

    return 0;
}