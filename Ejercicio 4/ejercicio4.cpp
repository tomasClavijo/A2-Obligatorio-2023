#include <iostream>
#include <cstring>
#include <string>

using namespace std;

struct NodoLista {
    int origen;
    int destino;
    int habilitado;
    int distancia;
    NodoLista* sig;

    NodoLista(int _origen, int _destino, int _habilitado, int _distancia)
        : origen(_origen), destino(_destino), habilitado(_habilitado), distancia(_distancia), sig(nullptr) {}
};

class Grafo {
private:
    NodoLista** listaAdy;
    int V;
    bool* ciudadesDeshabilitadas;

public:
    Grafo(int _V) : V(_V) {
        listaAdy = new NodoLista*[V + 1];
        ciudadesDeshabilitadas = new bool[V + 1];
        for (int i = 0; i <= V; i++) {
            listaAdy[i] = nullptr;
            ciudadesDeshabilitadas[i] = false;
        }
    }

    ~Grafo() {
        for (int i = 0; i <= V; i++) {
            NodoLista* actual = listaAdy[i];
            while (actual != nullptr) {
                NodoLista* siguiente = actual->sig;
                delete actual;
                actual = siguiente;
            }
        }
        delete[] listaAdy;
        delete[] ciudadesDeshabilitadas;
    }

    void aniadirArista(int origen, int destino, int distancia, int dobleSimple, int habilitado) {
        NodoLista* nuevoNodo = new NodoLista(origen, destino, habilitado, distancia);
        nuevoNodo->sig = listaAdy[origen];
        listaAdy[origen] = nuevoNodo;

        if (dobleSimple == 2) {
            nuevoNodo = new NodoLista(destino, origen, habilitado, distancia);
            nuevoNodo->sig = listaAdy[destino];
            listaAdy[destino] = nuevoNodo;
        }
    }

    void agregarCiudadDeshabilitada(int ciudad) {
        ciudadesDeshabilitadas[ciudad] = true;
    }

    void deshabilitarCarretera(int ciudad1, int ciudad2) {
        NodoLista* actual = listaAdy[ciudad1];
        while (actual != nullptr) {
            if (actual->destino == ciudad2) {
                actual->habilitado = 0;
                break;
            }
            actual = actual->sig;
        }
        // Si la carretera es de doble sentido, también la deshabilitamos en el otro sentido
        actual = listaAdy[ciudad2];
        while (actual != nullptr) {
            if (actual->destino == ciudad1) {
                actual->habilitado = 0;
                break;
            }
            actual = actual->sig;
        }
    }

    int getV() const {
        return V;
    }

    NodoLista* getAdyacentes(int origen) const {
        return listaAdy[origen];
    }

    bool esCiudadDeshabilitada(int ciudad) const {
        return ciudadesDeshabilitadas[ciudad];
    }
};

const int INF = 1e9;

int posMinNoVis(int* dist, bool* vis, int tope) {
    int posMin = -1;
    int minDist = INF;
    for (int i = 0; i < tope; i++) {
        if (dist[i] < minDist && !vis[i]) {
            minDist = dist[i];
            posMin = i;
        }
    }
    return posMin;
}

pair<int, string> dijkstra(const Grafo& grafo, int origen, int destino) {
    const int V = grafo.getV();
    int* dist = new int[V + 1];
    bool* visitado = new bool[V + 1];
    int* previo = new int[V + 1];

    for (int i = 1; i <= V; i++) {
        dist[i] = INF;
        visitado[i] = false;
        previo[i] = -1;
    }

    dist[origen] = 0;

    for (int i = 1; i <= V; i++) {
        int u = posMinNoVis(dist, visitado, V + 1);
        if (u == -1) {
            break;
        }
        visitado[u] = true;

        NodoLista* adyacentes = grafo.getAdyacentes(u);
        while (adyacentes != nullptr) {
            int v = adyacentes->destino;
            int peso = adyacentes->distancia;
            int habilitado = adyacentes->habilitado;

            if (!visitado[v] && habilitado && dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                previo[v] = u;
            }

            adyacentes = adyacentes->sig;
        }
    }

    string camino;
    int v = destino;
    while (v != -1) {
        camino = to_string(v) + (camino.empty() ? "" : ", ") + camino;
        v = previo[v];
    }

    delete[] dist;
    delete[] visitado;
    delete[] previo;

    return make_pair(dist[destino], "[" + camino + "]");
}

int main() {
    int N, M;
    cin >> N >> M;

    Grafo grafo(N);

    for (int i = 0; i < M; i++) {
        int origen, destino, distancia, dobleSimple, habilitado;
        cin >> origen >> destino >> distancia >> dobleSimple >> habilitado;
        grafo.aniadirArista(origen, destino, distancia, dobleSimple, habilitado);
    }

    int K;
    cin >> K;

    for (int i = 0; i < K; i++) {
        int ciudadDeshabilitada;
        cin >> ciudadDeshabilitada;
        grafo.agregarCiudadDeshabilitada(ciudadDeshabilitada);
    }

    int L;
    cin >> L;

    for (int i = 0; i < L; i++) {
        int ciudad1, ciudad2;
        cin >> ciudad1 >> ciudad2;
        grafo.deshabilitarCarretera(ciudad1, ciudad2);
    }

    int C1, C2;
    cin >> C1 >> C2;

    pair<int, string> resultado = dijkstra(grafo, C1, C2);
    cout << resultado.first << endl;
    cout << resultado.second << endl;

    return 0;
}


