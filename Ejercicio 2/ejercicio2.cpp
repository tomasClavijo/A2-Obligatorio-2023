#include <iostream>
#include <string>

// AVL cumple con O(P * Log2 (P)) en búsqueda e inserción.

using namespace std;

struct Nodo {
    string palabra;
    int ocurrencias;
    int altura;
    Nodo* izquierdo;
    Nodo* derecho;
};

int max(int a, int b) {
    return (a > b) ? a : b;
}

int obtenerAltura(Nodo* nodo) {
    if (nodo == nullptr) {
        return 0;
    } else {
        return nodo->altura;
    }
}

int obtenerBalance(Nodo* nodo) {
    if (nodo == nullptr) {
        return 0;
    } else {
        return obtenerAltura(nodo->izquierdo) - obtenerAltura(nodo->derecho);
    }
}

Nodo* rotacionDerecha(Nodo* y) {
    Nodo* x = y->izquierdo;
    Nodo* T2 = x->derecho;

    x->derecho = y;
    y->izquierdo = T2;

    y->altura = max(obtenerAltura(y->izquierdo), obtenerAltura(y->derecho)) + 1;
    x->altura = max(obtenerAltura(x->izquierdo), obtenerAltura(x->derecho)) + 1;

    return x;
}

Nodo* rotacionIzquierda(Nodo* x) {
    Nodo* y = x->derecho;
    Nodo* T2 = y->izquierdo;

    y->izquierdo = x;
    x->derecho = T2;

    x->altura = max(obtenerAltura(x->izquierdo), obtenerAltura(x->derecho)) + 1;
    y->altura = max(obtenerAltura(y->izquierdo), obtenerAltura(y->derecho)) + 1;

    return y;
}

Nodo* insertarNodo(Nodo* nodo, string palabra) {
    if (nodo == nullptr) {
        Nodo* nuevoNodo = new Nodo();
        nuevoNodo->palabra = palabra;
        nuevoNodo->ocurrencias = 1;
        nuevoNodo->altura = 1;
        nuevoNodo->izquierdo = nullptr;
        nuevoNodo->derecho = nullptr;
        return nuevoNodo;
    }

    if (palabra > nodo->palabra) {
        nodo->derecho = insertarNodo(nodo->derecho, palabra);
    } else if (palabra < nodo->palabra) {
        nodo->izquierdo = insertarNodo(nodo->izquierdo, palabra);
    } else {
        nodo->ocurrencias++;
        nodo->altura = 1 + max(obtenerAltura(nodo->izquierdo), obtenerAltura(nodo->derecho));
        return nodo;
    }

    nodo->altura = 1 + max(obtenerAltura(nodo->izquierdo), obtenerAltura(nodo->derecho));

    int balance = obtenerBalance(nodo);

    if (balance > 1 && palabra < nodo->izquierdo->palabra) {
        return rotacionDerecha(nodo);
    }
    if (balance < -1 && palabra > nodo->derecho->palabra) {
        return rotacionIzquierda(nodo);
    }
    if (balance > 1 && palabra > nodo->izquierdo->palabra) {
        nodo->izquierdo = rotacionIzquierda(nodo->izquierdo);
        return rotacionDerecha(nodo);
    }
    if (balance < -1 && palabra < nodo->derecho->palabra) {
        nodo->derecho = rotacionDerecha(nodo->derecho);
        return rotacionIzquierda(nodo);
    }

    return nodo;
}

Nodo* buscarNodo(Nodo* nodo, string palabra) {
    if (nodo == nullptr || nodo->palabra == palabra) {
        return nodo;
    } else if (palabra < nodo->palabra) {
        return buscarNodo(nodo->izquierdo, palabra);
    } else {
        return buscarNodo(nodo->derecho, palabra);
    }
}

void mostrarPalabras(Nodo* nodo) {
    if (nodo != nullptr) {
        mostrarPalabras(nodo->derecho);
        cout << nodo->palabra << " " << nodo->ocurrencias << endl;
        mostrarPalabras(nodo->izquierdo);
    }
}

int main() {
    int P;
    cin >> P;

    Nodo* raiz = nullptr;

    for (int i = 0; i < P; i++) {
        string palabra;
        cin >> palabra;

        Nodo* nodoExistente = buscarNodo(raiz, palabra);
        if (nodoExistente != nullptr) {
            nodoExistente->ocurrencias++;
        } else {
            raiz = insertarNodo(raiz, palabra);
        }
    }

    mostrarPalabras(raiz);

    return 0;
}