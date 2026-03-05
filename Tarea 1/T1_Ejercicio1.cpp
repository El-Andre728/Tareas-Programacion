#include <iostream>
#include <string>
using namespace std;

int main() {
    string binario;
    long long decimal = 0;

    cout << "Ingrese un numero binario: ";
    cin >> binario;

    int potencia = 1; // 2^0
    for (int i = binario.length() - 1; i >= 0; i--) { 
        if (binario[i] == '1') {
            decimal += potencia;
        }
        potencia *= 2;
    }

    cout << "Decimal: " << decimal << endl;
    return 0;
}