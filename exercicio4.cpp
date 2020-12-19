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
    int x;

    cin >> x;

    if (ehprimo(x)) {
        cout << "EH PRIMO!\n";
    } else {
        cout << "NAO EH PRIMO!\n";
    }

    return 0;
}