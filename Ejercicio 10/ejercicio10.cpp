#include <iostream>
#include <cstring>

using namespace std;

// Estructura para representar las coordenadas x, y en una matriz.
struct Posicion {
    int x;
    int y;
};

// Verifico si la posicion es valida dentro de los limites de la matriz.
bool esPosicionValida(int x, int y, int M, int N) {
    return x >= 0 && x < M && y >= 0 && y < N;
}

// Busca el camino mas corto desde un origen a un destino. Exploro todas las posibles vias.
int caminoMasCorto(char** matriz, int M, int N, Posicion origen, Posicion destino, bool** visitados, int distancia, bool pasoXBedelia) {
    if (origen.x == destino.x && origen.y == destino.y && pasoXBedelia) {
        return distancia;
    }

    visitados[origen.x][origen.y] = true;
    
    // Direcciones posibles
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    int masCorto = 0;

    for (int i = 0; i < 4; i++) {
        int nuevoX = origen.x + dx[i];
        int nuevoY = origen.y + dy[i];

        if (esPosicionValida(nuevoX, nuevoY, M, N) && !visitados[nuevoX][nuevoY] && matriz[nuevoX][nuevoY] != 'P') {
            Posicion siguiente = {nuevoX, nuevoY};
            bool proxPasoXBedelia = pasoXBedelia || (matriz[nuevoX][nuevoY] == 'B');
            int longitud = caminoMasCorto(matriz, M, N, siguiente, destino, visitados, distancia + 1, proxPasoXBedelia);

            if (longitud != 0 && (masCorto == 0 || longitud < masCorto)) {
                masCorto = longitud;
            }
        }
    }

    visitados[origen.x][origen.y] = false;

    return masCorto;
}

int main() {
    int M, N;
    cin >> M >> N;
    
    // Configuracion de la facultad
    char** matriz = new char*[M];
    for (int i = 0; i < M; i++) {
        matriz[i] = new char[N];
        for (int j = 0; j < N; j++) {
            cin >> matriz[i][j];
        }
    }

    int P;
    cin >> P;

    // Casos de prueba
    for (int i = 0; i < P; i++) {
        int xi, yi, xf, yf;
        cin >> xi >> yi >> xf >> yf;

        xi--;
        yi--;
        xf--;
        yf--;

        Posicion comienzo = {xi, yi};
        Posicion destino = {xf, yf};

        bool** visitados = new bool*[M];
        for (int j = 0; j < M; j++) {
            visitados[j] = new bool[N];
            for (int k = 0; k < N; k++) {
                visitados[j][k] = false;
            }
        }

        int longitud = caminoMasCorto(matriz, M, N, comienzo, destino, visitados, 0, false);

        if (longitud == 0) {
            cout << 0 << endl;
        } else {
            cout << longitud + 1 << endl;
        }

        for (int j = 0; j < M; j++) {
            delete[] visitados[j];
        }
        delete[] visitados;
    }

    for (int i = 0; i < M; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;

    return 0;
}
