#ifndef VECTOR_H
#define VECTOR_H

template <typename T>

class Vector {
    private:
        T* datos;
        int capacidad;
        int tamanio;

        void redimensionar() {
            capacidad *= 2;
            T* nuevoArreglo = new T[capacidad];
            for (int i = 0; i < tamanio; i++) {
                nuevoArreglo[i] = datos[i];
            }
            delete[] datos;
            datos = nuevoArreglo;
        }

    public:
        Vector() {
            capacidad = 10;
            tamanio = 0;
            datos = new T[capacidad];
        }

        ~Vector() {
            delete[] datos;
        }

        void agregar(T elemento) {
            if (tamanio == capacidad) {
                redimensionar();
            }
            datos[tamanio] = elemento;
            tamanio++;
        }
        
        void eliminar(int indice) {
            if (indice >= 0 && indice < tamanio) {
                for (int i = indice; i < tamanio - 1; i++) {
                    datos[i] = datos[i + 1];
                }
                tamanio--;
            }
        }

        int getTamanio() {
            return tamanio;
        }

        // Operador corchetes para poder acceder a los elementos como un arreglo común (v[i])
        T& operator[](int indice) {
            return datos[indice];
        }

};

#endif

