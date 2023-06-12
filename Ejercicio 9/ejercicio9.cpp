#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int ** initMatriz(int filas, int columnas){
	int ** m = new int*[filas]();
	for(int i=0; i < filas; i++)
	{
		m[i] = new int[columnas]();
	}
	return m;
}

int calcularCombinacion(int N, int K) {
    if (K > N) {
        return 0;
    } else if (N == K || K == 0){
        return 1;
    }

    int** combinaciones = initMatriz(N+1, K+1);

    for (int i = 0; i <= N; i++) {
        combinaciones[i][0] = 1;
    }

    // Calcular las combinaciones utilizando la fórmula C(n, k) = C(n-1, k-1) + C(n-1, k)
    for (int n = 1; n <= N; n++) {
        for (int k = 1; k <= min(n, K); k++) {
            combinaciones[n][k] = combinaciones[n-1][k-1] + combinaciones[n-1][k];
        }
    }

    return combinaciones[N][K];
}

int main() {
    int N, P;
    cin >> N >> P;

    int** casos = initMatriz(P,2);
    for (int i = 0; i < P; i++) {
        cin >> casos[i][0] >> casos[i][1];
    }

    for (int i = 0; i < P; i++) {
        int result = calcularCombinacion(casos[i][0], casos[i][1]);
        cout << result << endl;
    }

    return 0;
}