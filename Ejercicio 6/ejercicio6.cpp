#include <string>
#include <iostream>
using namespace std;

bool esImpar (int n){
    if (n % 2 == 0){
        return false;
    } else{
        return true;
    }
}

int elementoNoRepetido(int * arr, int i, int f){
        if (i == f){
        return arr[i];
    }

    int mitad = (f + i) / 2;

    bool impar;

    if (arr[mitad] == arr[mitad + 1]){
        impar = esImpar(mitad);
        if (impar){
            elementoNoRepetido(arr, i, mitad -1);
        } else{
            elementoNoRepetido(arr, mitad, f);
        }
    } else {
        impar = esImpar(mitad + 1);
        if (impar){
            elementoNoRepetido(arr, i, mitad);
        } else{
            elementoNoRepetido(arr, mitad + 1, f);
        }
    }
}

int main(){
    int cantidadElementos;
    cin >> cantidadElementos;
    int* arr = new int[cantidadElementos];
    int elemento;
    for (int i = 0; i < cantidadElementos; i++){
        cin >> elemento;
        arr[i] = elemento;
    }
    int noRepetido = elementoNoRepetido(arr, 0, cantidadElementos - 1);
    cout << noRepetido << endl;
    delete [] arr;
    return 0;
}