#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cstring>
#include <ctime>
#include "forca.h"

using namespace std;

char palavrasecreta[TAMANHO_PALAVRA];
double pontos = QUANTIDADE_DE_PONTOS_INICIAL;
char chutes[26];
int chutesdados = 0;
int totalchutes;

bool letraexiste(char letra) {

    for (int j = 0; j < strlen(palavrasecreta); j++) {
        if (letra == palavrasecreta[j]) {
            return true;
        }
    }

    return false;
}

int chuteserrados() {
    int erros = 0;

    for (int i = 0; i < chutesdados; i++) {

        if (!letraexiste(chutes[i])) {
            erros++;
        }
    }

    return erros;
}

bool jachutou(char letra) {
    bool achou = false;
    for (int j = 0; j < chutesdados; j++) {
        if (chutes[j] == letra) {
            achou = true;
            break;
        }
    }

    return achou;
}

bool enforcou() {
    return chuteserrados() >= 5;
}

bool ganhou() {
    for (int i = 0; i < strlen(palavrasecreta); i++) {
        if (!jachutou(palavrasecreta[i])) {
            return false;
        }
    }

    return true;
}

void abertura() {
    cout << "/****************/\n";
    cout << "/ Jogo de Forca */\n";
    cout << "/****************/\n\n";
}

void chuta() {
    char chute;
    cout << "Qual letra? ";
    cin >> chute;

    if (chute >= 'A' && chute <= 'Z') {

        if (letraexiste(chute)) {
            cout << "Voce acertou: a palavra tem a letra " << chute << "\n\n";
            pontos += 100;
        } else {
            cout << "\nVoce errou: a palavra NAO tem a letra " << chute << "\n\n";
            pontos -= 200;
        }

        chutes[chutesdados] = chute;
        chutesdados++;
    } else {
        cout << "Digite apenas letras maiusculas!\n\n";
    }
}

void desenhaforca() {

    int erros = chuteserrados();

    cout << "Tentativas restantes: " << totalchutes - chutesdados << "\n\n";
    cout << "  _______       \n";
    cout << " |/      |      \n";
    cout << " |      " << (erros >= 1 ? '(' : ' ') << (erros >= 1 ? '_' : ' ') << (erros >= 1 ? ')' : ' ') << "  \n";
    cout << " |      " << (erros >= 3 ? '\\' : ' ') << (erros >= 2 ? '|' : ' ') << (erros >= 3 ? '/' : ' ') << "  \n";
    cout << " |       " << (erros >= 2 ? '|' : ' ') << "     \n";
    cout << " |      " << (erros >= 4 ? '/' : ' ') << " " << (erros >= 4 ? '\\' : ' ') << "   \n";
    cout << " |              \n";
    cout << "_|___           \n";
    cout << "\n\n";

    for (int i = 0; i < strlen(palavrasecreta); i++) {

        if (jachutou(palavrasecreta[i])) {
            cout << palavrasecreta[i] << " ";
        } else {
            cout << "_ ";
        }

    }
    cout << "\n";

}

void escolhepalavra() {
    FILE *f;

    f = fopen("palavras.txt", "r");
    if (f == 0) {
        cout << "Banco de dados de palavras nao disponivel\n\n";
        exit(1);
    }

    int qtddepalavras;
    fscanf(f, "%d", &qtddepalavras);

    srand(time(0));
    int randomico = rand() % qtddepalavras;

    for (int i = 0; i <= randomico; i++) {
        fscanf(f, "%s", palavrasecreta);
    }

    fclose(f);
}

void adicionapalavra() {
    char quer;

    cout << "Voce deseja adicionar uma nova palavra no jogo (S/N)? ";
    cin >> quer;

    if (quer == 'S') {
        char novapalavra[TAMANHO_PALAVRA];

        cout << "Digite a nova palavra, em letras maiusculas: ";
        cin >> novapalavra;

        FILE *f;

        f = fopen("palavras.txt", "r+");
        if (f == 0) {
            cout << "Banco de dados de palavras nao disponivel\n\n";
            exit(1);
        }

        bool adiciona = true;
        int qtd;

        fscanf(f, "%d", &qtd);

        for (int i = 0; i < qtd; i++) {
            char palavra[TAMANHO_PALAVRA];

            fscanf(f, "%s", palavra);

            if (strcmp(novapalavra, palavra) == 0) {
                adiciona = false;
            }

        }

        if (adiciona) {
            qtd++;
            fseek(f, 0, SEEK_SET);
            fprintf(f, "%04d", qtd);

            fseek(f, 0, SEEK_END);
            fprintf(f, "\n%s", novapalavra);
        }

        fclose(f);

    }

    cout << endl;
}

void escolhedificuldade() {
    int nivel;

    cout << "Qual o nivel de dificuldade?\n";
    cout << "(1) Facil (2) Medio (3) Dificil\n\n";
    cout << "Escolha: ";

    cin >> nivel;

    switch (nivel) {
        case 1:
            totalchutes = QUANTIDADE_DE_CHUTES_FACIL;
            break;
        case 2:
            totalchutes = QUANTIDADE_DE_CHUTES_MEDIO;
            break;
        default:
            totalchutes = QUANTIDADE_DE_CHUTES_DIFICIL;
            break;
    }

    cout << endl;
}

bool verificatotalchutes() {
    return chutesdados >= totalchutes;
}

void adicionaranking() {
    char nome[TAMANHO_PALAVRA];

    cout << "Digite o seu nome, em letras maiusculas: ";
    cin >> nome;

    FILE *f;

    f = fopen("ranking.txt", "r+");
    if (f == 0) {
        cout << "Banco de dados de palavras nao disponivel\n\n";
        exit(1);
    }

    fseek(f, 0, SEEK_END);
    fprintf(f, "\n%s %.2f", nome, pontos);

    fclose(f);
}

int main() {

    escolhedificuldade();
    abertura();
    escolhepalavra();

    do {

        desenhaforca();
        chuta();

    } while (!ganhou() && !enforcou() && !verificatotalchutes());

    if (ganhou()) {
        cout << "\nParabens, voce ganhou!\n\n";
        cout << "Voce fez " << fixed << setprecision(2) << pontos << " pontos.\n\n";

        cout << "       ___________      \n";
        cout << "      '._==_==_=_.'     \n";
        cout << "      .-\\:      /-.    \n";
        cout << "     | (|:.     |) |    \n";
        cout << "      '-|:.     |-'     \n";
        cout << "        \\::.    /      \n";
        cout << "         '::. .'        \n";
        cout << "           ) (          \n";
        cout << "         _.' '._        \n";
        cout << "        '-------'       \n\n";

        adicionapalavra();

    } else {
        cout << "\nPuxa, voce foi enforcado!\n";
        cout << "A palavra era **" << palavrasecreta << "**\n\n";

        cout << "    _______________         \n";
        cout << "   /               \\       \n";
        cout << "  /                 \\      \n";
        cout << "//                   \\/\\  \n";
        cout << "\\|   XXXX     XXXX   | /   \n";
        cout << " |   XXXX     XXXX   |/     \n";
        cout << " |   XXX       XXX   |      \n";
        cout << " |                   |      \n";
        cout << " \\__      XXX      __/     \n";
        cout << "   |\\     XXX     /|       \n";
        cout << "   | |           | |        \n";
        cout << "   | I I I I I I I |        \n";
        cout << "   |  I I I I I I  |        \n";
        cout << "   \\_             _/       \n";
        cout << "     \\_         _/         \n";
        cout << "       \\_______/           \n";
    }

    adicionaranking();

    return 0;
}