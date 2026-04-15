//Quick sort
#include <iostream>
using namespace std;
int particion(int arr[], int inicio, int fin) {
    int pivote = arr[fin];
    int i = inicio - 1;

    for (int j = inicio; j < fin; j++) {
        if (arr[j] < pivote) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[fin];
    arr[fin] = temp;

    return i + 1;
}

void quickSort(int arr[], int inicio, int fin) {
    if (inicio < fin) {
        int pi = particion(arr, inicio, fin);

        quickSort(arr, inicio, pi - 1);
        quickSort(arr, pi + 1, fin);
    }
}
int main() {
    int arr[] = {8, 3, 5, 2, 9, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    quickSort(arr, 0, n - 1);

    cout << "Arreglo ordenado: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    return 0;
}
//Insertion sort
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {//i=1
        int clave = arr[i];// clave = arr[1]
        int j = i - 1; // j = 1-1 = 0

        while (j >= 0 && arr[j] > clave) {
            arr[j + 1] = arr[j]; //arr [j+1=1]
            j--; //j-1   
             
        }

        arr[j + 1] = clave;
    }
}
int main() {
    int arr[] = {8, 3, 5, 2, 9, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    insertionSort(arr, n);

    cout << "Arreglo ordenado: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    return 0;
}
//Selection sort
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }

        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}
int main() {
    int arr[] = {8, 3, 5, 2, 9, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    selectionSort(arr, n);

    cout << "Arreglo ordenado: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    return 0;
}