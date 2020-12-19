#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
    int a;

    cin >> a;

    FILE* f;

    f = fopen("tabuada.txt", "r+");
    if(f == 0) {
        cout << "NAO FOI POSSIVEL ABRIR O ARQUIVO!\n\n";
        exit(1);
    }

    for(int i = 1; i <= 20; i++) {
        fprintf(f, "%d x %d = %d\n", a, i, a * i);
    }

    fclose(f);

    return 0;
}