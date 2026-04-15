#include <iostream>      // Para entrada/salida de datos
#include <fstream>       // Para manejo de archivos (lectura y escritura)
#include <cstdio>        // Para funciones como remove() y rename()
#include <limits>        // Para numeric_limits (limpiar buffer)
#include <string>        // Para usar tipo string

using namespace std;

// ESTRUCTURA: Alumno
// Define la estructura de datos para almacenar información de un alumno
// en archivos binarios
struct Alumno {
    int id;               // Identificador único del alumno
    char nombre[30];      // Nombre del alumno (máximo 30 caracteres)
    float nota;           // Calificación del alumno
};

// FUNCIÓN: limpiarBuffer()
// Limpia el búfer de entrada cuando hay errores en cin
// Necesario para evitar bucles infinitos cuando el usuario ingresa
// un tipo de dato incorrecto
void limpiarBuffer() {
    cin.clear();  // Limpia el estado de error de cin
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Descarta datos del búfer
}

// FUNCIÓN: crearArchivoTexto()
// Permite crear un nuevo registro de alumno y guardarlo en un archivo de texto
// El archivo se abre en modo de append para no sobrescribir datos existentes
void crearArchivoTexto() {
    // Abre el archivo en modo append (añadir al final)
    ofstream archivo("alumnos.txt", ios::app);

    // Valida que el archivo se haya abierto correctamente
    if (!archivo.is_open()) {
        cout << "Error al abrir archivo texto\n";
        return;
    }

    // Declaración de variables para almacenar datos del alumno
    int id;
    string nombre;
    float nota;

    // Solicita el ID del alumno con validación
    cout << "ID: ";
    while (!(cin >> id)) {  // Valida que sea un número entero
        cout << "Entrada invalida. Ingrese un numero: ";
        limpiarBuffer();  // Limpia el búfer para reintentar
    }

    // Valida que el ID no sea negativo
    if (id < 0) {
        cout << "ID no puede ser negativo. Operacion cancelada.\n";
        return;
    }
    
    // Solicita el nombre del alumno
    cout << "Nombre: ";
    cin.ignore();  // Ignora el salto de línea después del ID
    getline(cin, nombre);  // Permite nombres con espacios
    
    // Solicita la nota del alumno con validación
    cout << "Nota: ";
    while (!(cin >> nota)) {  // Valida que sea un número decimal
        cout << "Entrada invalida. Ingrese una nota numerica: ";
        limpiarBuffer();  // Limpia el búfer para reintentar
    }

    // Escribe el registro en el archivo separado por espacios
    archivo << id << " " << nombre << " " << nota << endl;

    // Cierra el archivo
    archivo.close();
    
}

// FUNCIÓN: listarArchivoTexto()
// Lee y muestra todos los alumnos almacenados en el archivo de texto
// Incluye manejo de errores para datos corruptos
void listarArchivoTexto() {
    // Abre el archivo en modo lectura
    ifstream archivo("alumnos.txt");

    // Valida que el archivo se haya abierto correctamente
    if (!archivo.is_open()) {
        cout << "Error al abrir archivo\n";
        return;
    }

    // Declaración de variables para almacenar datos del alumno
    int id;
    string nombre;
    float nota;

    cout << "\nLISTA DE ALUMNOS\n";

    // Lee los datos del archivo línea por línea
    while (archivo >> id >> nombre >> nota) {
        // Verifica si hubo un error al leer datos
        if (archivo.fail()) {
            cout << "Error al leer archivo. Posible corrupcion de datos.\n";
            archivo.clear();  // Limpia el estado de error
            archivo.ignore(numeric_limits<streamsize>::max(), '\n');  // Descarta la línea corrupta
            continue;  // Continúa con la siguiente línea
        }
        // Muestra el registro del alumno
        cout << id << " " << nombre << " " << nota << endl;
    }

    // Cierra el archivo
    archivo.close();
}

// FUNCIÓN: buscarAlumno()
// Busca un alumno específico por su ID en el archivo de texto
// Muestra los datos del alumno si es encontrado
void buscarAlumno() {
    // Abre el archivo en modo lectura
    ifstream archivo("alumnos.txt");

    // Solicita el ID a buscar con validación
    int buscar;
    cout << "Ingrese ID a buscar: ";
    while (!(cin >> buscar)) {  // Valida que sea un número entero
        cout << "Entrada invalida. Ingrese un numero: ";
        limpiarBuffer();
    }

    // Declaración de variables para almacenar datos del alumno
    int id;
    string nombre;
    float nota;
    bool encontrado = false;  // Bandera para controlar si se encontró el alumno

    // Lee los datos del archivo línea por línea
    while (archivo >> id >> nombre >> nota) {
        // Verifica si hubo un error al leer datos
        if (archivo.fail()) {
            cout << "Error al leer archivo. Posible corrupcion de datos.\n";
            archivo.clear();  // Limpia el estado de error
            archivo.ignore(numeric_limits<streamsize>::max(), '\n');  // Descarta la línea corrupta
            continue;
        }
        // Compara el ID leído con el ID buscado
        if (id == buscar) {
            cout << "Encontrado: " << nombre << " Nota: " << nota << endl;
            encontrado = true;  // Marca como encontrado
        }
    }

    // Si no se encontró el alumno, muestra un mensaje
    if (!encontrado)
        cout << "Alumno no encontrado\n";

    // Cierra el archivo
    archivo.close();
}

// FUNCIÓN: actualizarNota()
// Actualiza la nota de un alumno específico identificado por su ID
// Realiza la actualización mediante un archivo temporal
void actualizarNota() {
    // Abre el archivo existente para lectura
    ifstream archivo("alumnos.txt");
    // Abre un archivo temporal para escritura
    ofstream temp("temp.txt");

    // Solicita el ID del alumno a actualizar con validación
    int buscar;
    cout << "ID a actualizar: ";
    while (!(cin >> buscar)) {  // Valida que sea un número entero
        cout << "Entrada invalida. Ingrese un numero: ";
        limpiarBuffer();
    }

    // Solicita la nueva nota con validación
    float nuevaNota;
    cout << "Nueva nota: ";
    while (!(cin >> nuevaNota)) {  // Valida que sea un número decimal
        cout << "Entrada invalida. Ingrese una nota numerica: ";
        limpiarBuffer();
    }

    // Declaración de variables para almacenar datos del alumno
    int id;
    string nombre;
    float nota;

    // Lee el archivo original y escribe en el archivo temporal
    while (archivo >> id >> nombre >> nota) {
        // Verifica si hubo un error al leer datos
        if (archivo.fail()) {
            cout << "Error al leer archivo. Posible corrupcion de datos.\n";
            archivo.clear();  // Limpia el estado de error
            archivo.ignore(numeric_limits<streamsize>::max(), '\n');  // Descarta la línea corrupta
            continue;
        }
        // Si el ID coincide, escribe la nueva nota; si no, mantiene la nota original
        if (id == buscar) {
            temp << id << " " << nombre << " " << nuevaNota << endl;
        } else {
            temp << id << " " << nombre << " " << nota << endl;
        }
    }

    // Cierra ambos archivos
    archivo.close();
    temp.close();

    // Elimina el archivo original y renombra el temporal como el original
    remove("alumnos.txt");
    rename("temp.txt", "alumnos.txt");

    cout << "Actualizacion realizada\n";
}

// FUNCIÓN: crearBinario()
// Permite crear un nuevo registro de alumno y guardarlo en un archivo binario
// Los datos se almacenan en formato binario para mayor eficiencia
void crearBinario() {
    // Abre el archivo en modo binario append (añadir al final)
    ofstream archivo("alumnos.dat", ios::binary | ios::app);

    // Declara una estructura alumno
    Alumno a;

    // Solicita el ID del alumno con validación
    cout << "ID: ";
    while (!(cin >> a.id)) {  // Valida que sea un número entero
        cout << "Entrada invalida. Ingrese un numero: ";
        limpiarBuffer();  // Limpia el búfer para reintentar
    }
    
    // Solicita el nombre del alumno
    cout << "Nombre: ";
    cin.ignore();  // Ignora el salto de línea después del ID
    cin.getline(a.nombre, 30);  // Lee hasta 30 caracteres del nombre
    
    // Solicita la nota del alumno con validación
    cout << "Nota: ";
    while (!(cin >> a.nota)) {  // Valida que sea un número decimal
        cout << "Entrada invalida. Ingrese una nota numerica: ";
        limpiarBuffer();  // Limpia el búfer para reintentar
    }

    // Escribe la estructura en el archivo en formato binario
    archivo.write((char*)&a, sizeof(a));

    // Cierra el archivo
    archivo.close();
}

// FUNCIÓN: leerRegistroEspecifico()
// Lee un registro específico del archivo binario basado en su posición
// Utiliza seekg para acceder directamente al registro deseado
void leerRegistroEspecifico() {
    // Abre el archivo en modo lectura binaria
    fstream archivo("alumnos.dat", ios::binary | ios::in);

    // Solicita la posición del registro a leer con validación
    int pos;
    cout << "Numero de registro: ";
    while (!(cin >> pos)) {  // Valida que sea un número entero
        cout << "Entrada invalida. Ingrese un numero: ";
        limpiarBuffer();
    }

    // Declara una estructura alumno para almacenar el registro leído
    Alumno a;

    // Posiciona el cursor del archivo en la posición del registro
    // Cada registro ocupa sizeof(a) bytes
    archivo.seekg(pos * sizeof(a), ios::beg);
    // Lee el registro desde el archivo binario
    archivo.read((char*)&a, sizeof(a));

    // Muestra los datos del registro leído
    cout << a.id << " " << a.nombre << " " << a.nota << endl;

    // Cierra el archivo
    archivo.close();
}

// FUNCIÓN: recorrerBinario()
// Lee y muestra todos los registros almacenados en el archivo binario
void recorrerBinario() {
    // Abre el archivo en modo lectura binaria
    ifstream archivo("alumnos.dat", ios::binary);

    // Declara una estructura alumno para almacenar cada registro
    Alumno a;

    cout << "\nREGISTROS BINARIOS\n";

    // Lee todos los registros del archivo uno por uno
    while (archivo.read((char*)&a, sizeof(a))) {
        // Muestra los datos de cada registro leído
        cout << a.id << " " << a.nombre << " " << a.nota << endl;
    }

    // Cierra el archivo
    archivo.close();
}

int main() {

    int op;  // Variable para almacenar la opción seleccionada

    // Bucle principal del programa
    do {
        // Menú de opciones disponibles
        cout << "\n1 Crear alumno";
        cout << "\n2 Listar alumnos";
        cout << "\n3 Buscar alumno";
        cout << "\n4 Actualizar nota";
        cout << "\n5 Crear alumno binario";
        cout << "\n6 Leer registro binario especifico";
        cout << "\n7 Recorrer archivo binario";
        cout << "\n0 Salir\n";

        // Solicita la opción con validación
        while (!(cin >> op)) {  // Valida que sea un número entero
            cout << "Opcion invalida. Ingrese un numero: ";
            limpiarBuffer();  // Limpia el búfer para reintentar
        }

        // Ejecuta la función correspondiente según la opción seleccionada
        switch (op) {
            case 1: crearArchivoTexto(); break;           // Opción 1: Crear alumno en texto
            case 2: listarArchivoTexto(); break;          // Opción 2: Listar alumnos de texto
            case 3: buscarAlumno(); break;                // Opción 3: Buscar alumno por ID
            case 4: actualizarNota(); break;              // Opción 4: Actualizar nota de alumno
            case 5: crearBinario(); break;                // Opción 5: Crear alumno en binario
            case 6: leerRegistroEspecifico(); break;      // Opción 6: Leer un registro específico
            case 7: recorrerBinario(); break;             // Opción 7: Recorrer archivo binario
            // La opción 0 termina el bucle y finaliza el programa
        }

    } while (op != 0);
    
    return 0;
}