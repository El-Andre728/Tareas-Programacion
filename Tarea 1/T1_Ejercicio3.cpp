#include <iostream>
#include <vector>
using namespace std;

int main() {
    int cantidad;

    cout << "Cuantos numeros desea ingresar? ";
    cin >> cantidad;
    
    //Un arreglo no puede tener un tamaño varible.
    vector<int> numeros(cantidad);
    vector<int> inversos(cantidad);

    for (int i = 0; i < cantidad; i++) {
        cout << "Numero " << i + 1 << ": ";
        cin >> numeros[i];
        inversos[i] = -numeros[i];
    }

    cout << "Inversos aditivos: ";
    for (int i = 0; i < cantidad; i++) {
        cout << inversos[i] << " ";
    }

    return 0;
}