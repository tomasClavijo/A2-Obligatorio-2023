#include <iostream>
#include <cstring>

using namespace std;

const int MAX = 100;

struct Posicion {
    int x;
    int y;
};

// Verifico si la posicion es valida al realizar un movimiento
bool esPosicionValida(int x, int y, int M, int N) {
    return x >= 0 && x < M && y >= 0 && y < N;
}

// Busca el camino mas corto desde un origen hasta un destino
int caminoMasCorto(char matriz[][MAX], int M, int N, Posicion origen, Posicion destino, bool visitados[][MAX], int distancia, bool pasoXBedelia) {
    if (origen.x == destino.x && origen.y == destino.y && pasoXBedelia) {
        return distancia;
    }

    visitados[origen.x][origen.y] = true;

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    int masCorto = 0;

    for (int i = 0; i < 4; i++) {
        int nuevoX = origen.x + dx[i];
        int nuevoY = origen.y + dy[i];

        if (esPosicionValida(nuevoX, nuevoY, M, N) && !visitados[nuevoX][nuevoY] && matriz[nuevoX][nuevoY] != 'P') {
            Posicion next = {nuevoX, nuevoY};
            bool nextpasoXBedelia = pasoXBedelia || (matriz[nuevoX][nuevoY] == 'B');
            int longitud = caminoMasCorto(matriz, M, N, next, destino, visitados, distancia + 1, nextpasoXBedelia);

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

    char matriz[MAX][MAX]; // INTENTAR DEFINIR LA MATRIZ EN OTRA FUNCION Y SACAR DEL CAMINO AL MAX. 

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cin >> matriz[i][j];
        }
    }

    int P;
    cin >> P;

    for (int i = 0; i < P; i++) {
        int xi, yi, xf, yf;
        cin >> xi >> yi >> xf >> yf;

        xi--;
        yi--;
        xf--;
        yf--;

        Posicion comienzo = {xi, yi};
        Posicion destino = {xf, yf};

        bool visitados[MAX][MAX];
        memset(visitados, false, sizeof(visitados));

        int longitud = caminoMasCorto(matriz, M, N, comienzo, destino, visitados, 0, false);

        if (longitud == 0) {
            cout << 0 << endl;
        } else {
            cout << longitud + 1 << endl;
        }
    }

    return 0;
}