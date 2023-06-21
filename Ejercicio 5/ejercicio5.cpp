#include <iostream>
#include <cstring>
#include <string>
#include <cassert>

using namespace std;

struct NodoLista {
    int destino;
    int val;
    NodoLista* sig;
    NodoLista(int _origen, int _destino)
        : val(_origen), destino(_destino), sig(nullptr) {}
};

struct Nodo{
    int val;
    int nivel;
    Nodo(int _val, int _nivel) 
        : val(_val), nivel(_nivel){}
};


class Grafo {
private:
    NodoLista** listaAdy;
    int V;
    int A;
    int* gradoDeEntrada;

public:
    Grafo(int _V){
        V = _V;
        listaAdy = new NodoLista*[V + 1];
        A = 0;
        gradoDeEntrada = new int[V + 1];
        for (int i = 0; i <= V; i++) {
            listaAdy[i] = nullptr;
            gradoDeEntrada[i] = 0;
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
        delete[] gradoDeEntrada;
    }

    void aniadirArista(int origen, int destino) {
        NodoLista* nuevoNodo = new NodoLista(origen, destino);
        nuevoNodo->sig = listaAdy[origen];
        listaAdy[origen] = nuevoNodo;
        A++;
        gradoDeEntrada[destino]++;
    }

    int getV() {
        return V;
    }

    int getA(){
        return A;
    }

    NodoLista* getAdyacentes(int origen) const {
        return listaAdy[origen];
    }

};

class MinHeap{
    private:
        Nodo** arr;
        int proximoLibre;
        int largo;

        int posPadre(int pos){
            return pos / 2;
        }

        int posHijoIzq(int pos){
            return pos * 2;
        }

        int posHijoDer(int pos){
            return pos * 2 + 1;
        }

        bool tengoHijoIzq(int pos){
            return proximoLibre > posHijoIzq(pos);
        }

        bool tengoHijoDer(int pos){
            return proximoLibre > posHijoDer(pos);
        }

        void intercambiar(int pos1, int pos2){
            Nodo* aux = arr[pos1];
            arr[pos1] = arr[pos2];
            arr[pos2] = aux;
        }

        void flotar(int pos){
            if (pos == 1){
                return;
            } else {
                int posPadre = this->posPadre(pos);
                int nivelPadre = arr[posPadre]->nivel;
                int nivelActual = arr[pos]->nivel;
                    if (nivelPadre > nivelActual){
                        intercambiar(posPadre,pos);
                        flotar(posPadre);
                    } else if (nivelPadre == nivelActual){
                        int valorPadre = arr[posPadre]->val;
                        int valorActual = arr[pos]->val;
                        if(valorPadre > valorActual){
                            intercambiar(posPadre, pos);
                            flotar(posPadre);
                        }
                    }
                }
            }

        void hundir(int pos){
           if (tengoHijoIzq(pos)){
            int posHijoMenor = posHijoIzq(pos);
            if (tengoHijoDer(pos) && (arr[posHijoDer(pos)]->nivel < arr [posHijoIzq(pos)]->nivel)){
                posHijoMenor = posHijoDer(pos);
            } else if (tengoHijoDer(pos) && (arr[posHijoDer(pos)]->nivel == arr [posHijoIzq(pos)]->nivel)){
                if (arr[posHijoDer(pos)]->val < arr[posHijoIzq(pos)]->val){
                    posHijoMenor = posHijoDer(pos);
                } else {
                    posHijoMenor = posHijoIzq(pos);
                }
            }
            if(arr[pos]->nivel > arr[posHijoMenor]->nivel){
                intercambiar (pos, posHijoMenor);
                hundir (posHijoMenor);
            } else if (arr[pos]->nivel == arr[posHijoMenor]->nivel){
                if(arr[pos]->val > arr[posHijoMenor]->val){
                    intercambiar(pos, posHijoMenor);
                    hundir(posHijoMenor);
                }
            }
           }
        }
    
    public:
        MinHeap(int capacidad){
            largo = capacidad + 1;
            proximoLibre = 1;
            arr = new Nodo*[largo];
        }
        ~MinHeap(){
            delete [] arr;
        }
        void insertar (Nodo* elemento){
            assert(!estaLleno());
            arr[proximoLibre] = elemento;
            proximoLibre++;
            flotar(proximoLibre - 1);
        }
        void eliminarMin(){
            assert(!esVacio());
            arr[1] = arr[proximoLibre - 1];
            proximoLibre--;
            hundir(1);
        }
        Nodo* getMin(){
            assert(!esVacio());
            return arr[1];
        }
        bool esVacio(){
            return proximoLibre == 1;
        }
        bool estaLleno(){
            return proximoLibre >= largo; 
        }
        int cantidadDeElementos(){
            return proximoLibre - 1;
        }

};

void ordenTopologico (Grafo* g, int* gradoDeIncidencia, int* niveles){
    int ultimoNivel = 0;
    MinHeap* h = new MinHeap(g->getV());
    for(int i = 1; i < g->getV() + 1; i++){
        if(gradoDeIncidencia[i] == 0){
            niveles[i] = ultimoNivel;
            Nodo* n = new Nodo(i, niveles[i]);
            h->insertar(n);
        }
    }
    int verticesProcesados = 0;
    while(!h->esVacio()){
        Nodo* vertice = h->getMin();
        h->eliminarMin();
        cout << vertice->val << endl;
        NodoLista* ady = g->getAdyacentes(vertice->val);
        ultimoNivel = vertice->nivel + 1;
        while(ady != NULL){
            int destino = ady->destino;
            gradoDeIncidencia[destino]--;
            niveles[destino] = ultimoNivel;
            if (gradoDeIncidencia[destino] == 0){
                Nodo* m = new Nodo(destino, niveles[destino]);
                h->insertar(m);
            }
            ady = ady->sig;
        }
    }
}

int main(){
    int cantVertices;
    cin >> cantVertices;

    Grafo *g = new Grafo(cantVertices);
    int cantidadAristas;
    cin >> cantidadAristas;
    int* gradoDeIncidencia = new int[cantVertices+1];
    for(int i = 1; i <= cantVertices; i++){
        gradoDeIncidencia[i] = 0;
    }

    for(int i = 0; i < cantidadAristas; i++){
        int origen, destino;
        cin >> origen >> destino;

        g->aniadirArista(origen, destino);
        gradoDeIncidencia[destino]++;
    }

    int* niveles = new int[cantVertices + 1];
    for (int i = 0; i <= cantVertices; i++){
        niveles[i] = -1;
    }

    ordenTopologico(g, gradoDeIncidencia, niveles);

    delete g;
    delete[] gradoDeIncidencia;
    delete[] niveles;

    return 0;
}