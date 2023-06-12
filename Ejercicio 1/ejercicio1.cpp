#include <string>
#include <iostream>
#include <cstring>
#include <math.h>
using namespace std;

char** split(const char* str, char delimiter, int& numSubstrings) {
    int count = 1;
    int length = strlen(str); // Longitud de cadena de entrada
    for (int i = 0; i < length; i++) {
        if (str[i] == delimiter) {
            count++; // Contabilizo cantidad de delimitadores (veces que aparece el espacio)
        }
    }

    char** substrings = new char*[count];
    int index = 0;
    int start = 0;

    for (int i = 0; i <= length; i++) {
        if (str[i] == delimiter || i == length) {
            int substringLength = i - start;
            substrings[index] = new char[substringLength + 1];
            strncpy(substrings[index], str + start, substringLength);
            substrings[index][substringLength] = '\0';
            index++;
            start = i + 1;
        }
    }

    numSubstrings = count;
    return substrings;
}

class NodoHash{
    public:
        string dato;
        int promedio;
        bool hayDato;
        bool huboDato;
        NodoHash(){}
        NodoHash(string dato, int promedio, bool hayDato, bool huboDato) : dato(dato), promedio(promedio), hayDato(hayDato), huboDato(huboDato) {}
};

class Hash{
    private:
        NodoHash* vec;
        int cantidadAlumnos;
        int largo; // Largo del vector

        bool esPrimo(int num){
            if (num < 2){
                return false;
            } else {
                for (int i = 2; i< num/2; i++){
                    if (num % i == 0){
                        return false;
                    }
                }
                return true;
            }
        }

        int primoSup(int num){
            while(!esPrimo(++num));
            return num;
        }

        int funcionHash(string s){
            int total = 0;
            for (int i = 0; i < s.length(); i++){
                total = (total + int(s[i]) * (int)pow(37, i)) % largo;
            }
            return total;
        }

    public:
        Hash(int esperados){
            this->largo = primoSup(esperados);
            this->vec = new NodoHash[largo];
            this->cantidadAlumnos = 0;
            for (int i =0; i < largo; i++){
                vec[i].dato = "";
                vec[i].promedio = 0;
                vec[i].hayDato = false;
            }
        }

        ~Hash(){
                delete[] this ->vec;
        }

        void insertar(string s, int promedio){
            int posicion = funcionHash(s);
             if (vec[posicion].hayDato == false){
                vec[posicion].dato = s;
                vec[posicion].promedio = promedio;
                vec[posicion].hayDato = true;
                cantidadAlumnos++;
            } else {
                while (posicion < largo && vec[posicion].hayDato == true){
                    if (s == vec[posicion].dato){
                        return;
                    }
                    posicion++;
                }
                if (posicion == largo){
                    posicion = 0;
                    while (posicion < funcionHash(s) && vec[posicion].hayDato == true){
                        if (s == vec[posicion].dato){
                            return;
                        }
                        posicion++;

                    }
                    vec[posicion].dato = s;
                    vec[posicion].promedio = promedio;
                    vec[posicion].hayDato = true;
                    cantidadAlumnos++;
                } else {
                    vec[posicion].dato = s;
                    vec[posicion].promedio = promedio;
                    vec[posicion].hayDato = true;
                    cantidadAlumnos++;
                }
            }
        }

        void imprimirElementos(){
            for (int i = 0; i < largo; i++){
                if(vec[i].hayDato == true){
                    cout << vec[i].dato << " " << vec[i].promedio << endl;
                }
            }
        }
};

int main(){
    int cantidadAlumnos; // Lineas que se esperan
    int promedio; 
    cin >> cantidadAlumnos;

}
