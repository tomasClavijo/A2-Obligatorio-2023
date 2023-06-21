#include <iostream>
using namespace std;

void combinacion(long long n, long long ni, long long k, long long*& actual, long long*& aux, long long*& anterior, bool*& nivelesCalculados) {
    if (nivelesCalculados[ni]) {
        for (long long i = 0; i <= n; i++) {
            anterior[i] = actual[i];
            actual[i] = aux[i];
        }
        return;
    }

    aux[0] = 1;
    for (long long i = 1; i <= n; i++)
        aux[i] = anterior[i - 1] + anterior[i];

    for (long long i = 0; i <= n; i++) {
        anterior[i] = actual[i];
        actual[i] = aux[i];
    }

    nivelesCalculados[ni] = true;
}

int main() {
    long long n, p;
    cin >> n;
    cin >> p;

    long long* actual = new long long[n + 1]();
    long long* aux = new long long[n + 1]();
    long long* anterior = new long long[n + 1]();
    bool* nivelesCalculados = new bool[n + 1]();
    actual[0] = 1;
    aux[0] = 1;
    anterior[0] = 1;

    bool nivelNuevo = true;
    long long nAnterior = -1;
    long long construidoHasta = 0;

    for (long long i = 0; i < p; i++) {
        long long ni, ki;
        cin >> ni;
        cin >> ki;

        if (ni != 0)
            combinacion(n, ni, ki, actual, aux, anterior, nivelesCalculados);
        cout << actual[ki] << endl;
    }

    delete[] actual;
    delete[] nivelesCalculados;
    delete[] anterior;
    delete[] aux;
    return 0;
}
