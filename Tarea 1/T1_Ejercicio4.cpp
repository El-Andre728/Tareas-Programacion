#include <iostream>
#include <string>
using namespace std;

int main() {
    string texto;
    int a, b;

    cout << "Ingrese una cadena: ";
    getline(cin, texto);

    cout << "Ingrese indice a: ";
    cin >> a;
    cout << "Ingrese indice b: ";
    cin >> b;

    if (a < 0) a = 0;
    if (b >= (int)texto.length()) b = texto.length() - 1;

    while (a < b) {
        char temp = texto[a];
        texto[a] = texto[b];
        texto[b] = temp;
        a++;
        b--;
    }

    cout << "Resultado: " << texto << endl;

    return 0;
}