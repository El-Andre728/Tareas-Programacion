#include <iostream>
#include <vector>

using namespace std;

int main() {

    int n = 0;
    cout << "Ingrese un numero positivo: ";
    cin >> n;
    //Se usa un vector en vez de un arreglo porque da error al usar un arreglo con tamaño variable.
    vector<int> arreglo(n);

    for (int i = 0; i < n; i++) {
        arreglo[i] = n - i;
    }

    cout << "Arreglo descendente: ";
    for (int i = 0; i < n; i++) {
        cout << arreglo[i] << " ";
    }

    return 0;
}