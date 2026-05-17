#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

//  Clase Alumno
class Alumno {
public:
    string nombres;
    string apellidos;
    string carnet;
    string email;
    string telefono;
    double notas[5];

    Alumno() {
        for (int i = 0; i < 5; i++) notas[i] = 0.0;
    }

    double promedio() const {
        double suma = 0;
        for (int i = 0; i < 5; i++) suma += notas[i];
        return suma / 5.0;
    }

    void mostrar() const {
        cout << "--------------------------------------\n";
        cout << "Nombres   : " << nombres    << "\n";
        cout << "Apellidos : " << apellidos  << "\n";
        cout << "Carnet    : " << carnet     << "\n";
        cout << "Email     : " << email      << "\n";
        cout << "Telefono  : " << telefono   << "\n";
        cout << "Notas     : ";
        for (int i = 0; i < 5; i++) {
            cout << fixed << setprecision(2) << notas[i];
            if (i < 4) cout << " | ";
        }
        cout << "\n";
        cout << "Promedio  : " << fixed << setprecision(2) << promedio() << "\n";
    }
};

//  Nodo (clase auto-referenciada)
class Nodo {
public:
    Alumno alumno;
    Nodo* siguiente;

    Nodo() : siguiente(nullptr) {}
};

//  Lista enlazada simple
class ListaAlumnos {
private:
    Nodo* cabeza;

public:
    ListaAlumnos() : cabeza(nullptr) {}

    //Este es un destructor
    ~ListaAlumnos() {
        // Liberar toda la memoria dinamica
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            Nodo* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
    }

    void insertar(const Alumno& a) {
        Nodo* nuevo = new Nodo();
        nuevo->alumno = a;

        // Insertar al final
        if (cabeza == nullptr) {
            cabeza = nuevo;
        } else {
            Nodo* actual = cabeza;
            while (actual->siguiente != nullptr) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo;
        }
    }

    void mostrarTodos() const {
        if (cabeza == nullptr) {
            cout << "La lista esta vacia.\n";
            return;
        }

        int contador = 1;
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            cout << "\nAlumno #" << contador++ << "\n";
            actual->alumno.mostrar();
            actual = actual->siguiente;
        }
    }

    bool estaVacia() const {
        return cabeza == nullptr;
    }
};

//  Funciones de entrada validada
double leerNota(int numero) {
    double nota;
    while (true) {
        cout << "Nota " << numero << " (0-10): ";
        cin >> nota;
        if (cin.fail() || nota < 0 || nota > 10) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "x Valor invalido. Ingresa un nmero entre 0 y 10.\n";
        } else {
            cin.ignore(1000, '\n');
            return nota;
        }
    }
}

Alumno leerAlumno() {
    Alumno a;
    cout << "\n-> Nombres    : "; getline(cin, a.nombres);
    cout << "-> Apellidos  : "; getline(cin, a.apellidos);
    cout << "-> Carnet     : "; getline(cin, a.carnet);
    cout << "-> Email      : "; getline(cin, a.email);
    cout << "-> Telefono   : "; getline(cin, a.telefono);

    cout << "-> Notas:\n";
    for (int i = 0; i < 5; i++) {
        a.notas[i] = leerNota(i + 1);
    }
    return a;
}

//  Main
int main() {
    ListaAlumnos lista;
    char respuesta;

    cout << "=======================================\n";
    cout << "     SISTEMA DE REGISTRO DE ALUMNOS     \n";
    cout << "=======================================\n";

    do {
        cout << "\n[ Ingreso de alumno ]\n";
        Alumno a = leerAlumno();
        lista.insertar(a);
        cout << "\nAlumno agregado correctamente.\n";

        cout << "\nDesea agregar otro alumno? (s/n): ";
        cin >> respuesta;
        cin.ignore(1000, '\n');

    } while (respuesta == 's' || respuesta == 'S');

    cout << "\n=======================================\n";
    cout << "        LISTADO FINAL DE ALUMNOS        \n";
    cout << "=======================================\n";
    lista.mostrarTodos();

    cout << "\n=========================================\n";
    cout << "  Memoria liberada. Programa finalizado.\n";
    cout << "=========================================\n";

    return 0;
}
