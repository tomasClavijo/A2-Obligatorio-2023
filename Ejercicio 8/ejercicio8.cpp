#include <iostream>
#include <cstring>
#include <string>
using namespace std;


// Decido utilizar un mergeSort, otra opción es utilizar un minHeap
void merge(int* arr, int izq, int medio, int der) {
    int i, j, k;
    int n1 = medio - izq + 1;
    int n2 = der - medio;

    int* L = new int[n1];
    int* R = new int[n2];

    // Copiar datos a los arreglos temporales L[] y R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[izq + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[medio + 1 + j];

    // Combinar los arreglos temporales de nuevo en arr[izq..der]
    i = 0;
    j = 0;
    k = izq;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    // Copiar los elementos restantes de L[], si hay alguno
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    // Copiar los elementos restantes de R[], si hay alguno
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(int* arr, int izq, int der) {
    if (izq < der) {
        int medio = izq + (der - izq) / 2;

        // Ordenar la primera y segunda mitad
        mergeSort(arr, izq, medio);
        mergeSort(arr, medio + 1, der);

        // Combinar las mitades ordenadas
        merge(arr, izq, medio, der);
    }
}

struct Vuelo {
    int arribo;
    int salida;
};

int MinimoPlataformas(Vuelo* vuelos, int N) {
    int minPlataformas = 1;
    int actPlataformas = 1;

    int* arribos = new int[N];
    int* salidas = new int[N];

    for (int i = 0; i < N; i++) {
        arribos[i] = vuelos[i].arribo;
        salidas[i] = vuelos[i].salida;
    }

    mergeSort(arribos, 0, N-1);
    mergeSort(salidas, 0, N-1);

    int arriboActual = 1;
    int salidaActual = 0;

    while (arriboActual < N && salidaActual < N) {
        if (arribos[arriboActual] < salidas[salidaActual]) {
            actPlataformas++;
            arriboActual++;
        } else {
            actPlataformas--;
            salidaActual++;
        }

        if (actPlataformas > minPlataformas) {
            minPlataformas = actPlataformas;
        }
    }

    delete[] arribos;
    delete[] salidas;

    return minPlataformas;
}

int main() {
    int N;
    cin >> N;
    Vuelo* vuelos = new Vuelo[N];

    for (int i = 0; i < N; i++) {
        cin >> vuelos[i].arribo >> vuelos[i].salida;
    }

    int minPlataformas = MinimoPlataformas(vuelos, N);

    cout << minPlataformas << endl;

    delete[] vuelos;

    return 0;
}