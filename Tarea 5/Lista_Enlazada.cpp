#include <iostream>
using namespace std;

//Estructura del nodo
struct Nodo {
    int dato;
    Nodo* siguiente;
};

//Agregar nodo al final de la lista
void agregarNodo(Nodo*& cabeza, Nodo*& cola, int valor) {
    Nodo* nuevo = new Nodo();   //reservar memoria dinamica
    nuevo->dato = valor;
    nuevo->siguiente = nullptr;

    if (cabeza == nullptr) {    //lista vacia: el nuevo es cabeza y cola
        cabeza = nuevo;
        cola   = nuevo;
    } else {                    //enlazar con el ultimo nodo
        cola->siguiente = nuevo;
        cola = nuevo;
    }
}

//Imprimir la lista
void imprimirLista(Nodo* cabeza) {
    if (cabeza == nullptr) {
        cout << "La lista esta vacia.\n";
        return;
    }

    cout << "\nContenido de la lista:\n";
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        cout << "[" << actual->dato << " | ";
        if (actual->siguiente != nullptr)
            cout << "*] -> ";
        else
            cout << "NULL]";
        actual = actual->siguiente;
    }
    cout << "\n";
}

//Liberar memoria dinamica 
void liberarLista(Nodo*& cabeza) {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        Nodo* temp = actual->siguiente;
        delete actual;          //liberar nodo actual
        actual = temp;
    }
    cabeza = nullptr;           //dejar el puntero limpio
}

//Main 
int main() {
    Nodo* cabeza = nullptr;
    Nodo* cola   = nullptr;
    char opcion;
    int valor;

    cout << "=== Lista Enlazada Dinamica ===\n";

    //Menu interactivo 
    do {
        cout << "\nDesea ingresar un nuevo valor? (S/N): ";
        cin >> opcion;
        opcion = toupper(opcion);   //aceptar 's' y 'S'

        if (opcion == 'S') {
            cout << "Ingrese el valor: ";
            cin >> valor;
            agregarNodo(cabeza, cola, valor);
            cout << "Nodo agregado correctamente.\n";
        } else if (opcion != 'N') {
            cout << "Opcion invalida. Ingrese S o N.\n";
        }

    } while (opcion != 'N');

    //Mostrar e imprimir
    imprimirLista(cabeza);

    //Liberar memoria
    liberarLista(cabeza);
    cout << "\nMemoria liberada. Programa finalizado.\n";

    return 0;
}