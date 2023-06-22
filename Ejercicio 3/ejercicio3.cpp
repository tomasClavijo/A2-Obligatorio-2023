#include <iostream>
#include <string>
#include <cstring>
/* Librería incluída para usar printf() */
#include <cstdio> 

using namespace std;

struct Persona {
    string pasaporte;
    int vuelos;
};

struct Reserva {
    Persona* personas;
    int numPersonas;
    float promedio;
};

class MaxHeap {
private:
    Reserva* arr;
    int proximoLibre;
    int capacidad;

    void flotar(int pos) {
        if (pos == 1) {
            return;
        }

        int padre = pos / 2;
        if (arr[pos].promedio > arr[padre].promedio) {
            swap(arr[pos], arr[padre]);
            flotar(padre);
        }
    }

public:
    MaxHeap(int cap) {
        capacidad = cap;
        proximoLibre = 1;
        arr = new Reserva[capacidad + 1];
    }

    void insertar(Reserva reserva) {
        if (proximoLibre > capacidad) {
            return;
        }

        arr[proximoLibre] = reserva;
        flotar(proximoLibre);
        proximoLibre++;
    }

    Reserva eliminarMax() {
        Reserva maxReserva = arr[1];
        arr[1] = arr[proximoLibre - 1];
        proximoLibre--;

        int pos = 1;
        while (true) {
            int izq = pos * 2;
            int der = pos * 2 + 1;
            int maxPos = pos;

            if (izq < proximoLibre && arr[izq].promedio > arr[maxPos].promedio) {
                maxPos = izq;
            }

            if (der < proximoLibre && arr[der].promedio > arr[maxPos].promedio) {
                maxPos = der;
            }

            if (maxPos == pos) {
                break;
            }

            swap(arr[pos], arr[maxPos]);
            pos = maxPos;
        }

        return maxReserva;
    }

    bool esVacio() {
        return proximoLibre == 1;
    }
};

int main() {
    int numReservas;
    cin >> numReservas;

    MaxHeap heap(numReservas);

    for (int i = 0; i < numReservas; i++) {
        int numPersonas;
        cin >> numPersonas;

        Reserva reserva;
        reserva.numPersonas = numPersonas;
        reserva.personas = new Persona[numPersonas];

        float sumaVuelos = 0;
        for (int j = 0; j < numPersonas; j++) {
            string pasaporte;
            float vuelos;
            cin >> pasaporte >> vuelos;
            sumaVuelos += vuelos;

            reserva.personas[j].pasaporte = pasaporte;
            reserva.personas[j].vuelos = vuelos;
        }

        reserva.promedio = sumaVuelos / static_cast<float>(numPersonas);
        heap.insertar(reserva);
    }

    // Imprimir las reservas ordenadas en forma descendente
    while (!heap.esVacio()) {
        Reserva reserva = heap.eliminarMax();
        if (reserva.promedio == static_cast<int>(reserva.promedio)) {
            printf("%.0f", reserva.promedio);
        } else {
            printf("%.2f", reserva.promedio);
        }
        cout << " "; 
        for (int i = 0; i < reserva.numPersonas; i++) {
            cout << reserva.personas[i].pasaporte << " ";
        }
        cout << endl;

        delete[] reserva.personas;
    }

    return 0;
}