#include <string>
#include <iostream>
#include <cstring>
/* Librería incluída para la potencia en la función de Hash */
#include <math.h>
using namespace std;

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
        //NodoHash* vecOrdenado;
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

        /* El "if" en la funcion de Hash se realizó para evitar el desborde. 
        Esta idea fue recomendación de un docente*/

        int funcionHash(string s){
            int total = 0;
            for (int i = 0; i < s.length(); i++){
                if(i < 5){ 
                    total = (total + s.at(i)*(int)(pow(31,i)))%largo;
                    
                }else{
                    total = (total + s.at(i))%largo;
                }
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

        NodoHash buscar (string nombre){
            int posicion = funcionHash(nombre);
            if (vec[posicion].hayDato == true && vec[posicion].dato == nombre){
                return vec[posicion];
            } else {
                while (posicion < largo && vec[posicion].hayDato == true){
                    if (nombre == vec[posicion].dato){
                        return vec[posicion];
                    }
                    posicion++;
                }
                if (posicion == largo){
                    posicion = 0;
                    while (posicion < funcionHash(nombre) && vec[posicion].hayDato == true){
                        if (nombre == vec[posicion].dato){
                            return vec[posicion];
                        }
                        posicion++;

                    }
                }
            }
        }

        void imprimirElementos(string* vec){
            for (int i = 0; i < cantidadAlumnos; i++){
                NodoHash x = buscar(vec[i]);
                cout << x.dato << " " << x.promedio << endl;
            }
        }
};

int main(){
    int cantidadAlumnos = 0; // A
    int promedio = 0; 
    cin >> cantidadAlumnos;
    Hash* h = new Hash(cantidadAlumnos);
    for(int i = 0; i < cantidadAlumnos; i++){
        string nombre;
        int cantidadNotas = 0;
        int sumaTotal= 0;
        cin >> nombre >> cantidadNotas;
        for (int j = 0; j < cantidadNotas; j++){
            int x;
            cin >> x;
            sumaTotal += x;
        }
        promedio = sumaTotal / cantidadNotas;
        h->insertar(nombre, promedio);
        NodoHash x = h->buscar(nombre);
        cout << x.dato << " " << x.promedio << endl;
    }
    delete h;
}
