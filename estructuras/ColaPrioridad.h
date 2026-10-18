#ifndef COLA_PRIORIDAD_H
#define COLA_PRIORIDAD_H

#include "Vector.h"
#include <stdexcept>

using namespace std;

template <typename T>


class ColaPrioridad {
    private:
        Vector<T> datos;

        void subir(int indice) {
            while (indice > 0) {
                int padre = (indice - 1) / 2;

                if (datos[indice].getPrioridad() < datos[padre].getPrioridad()) {

                    T aux = datos[indice];
                    datos[indice] = datos[padre];
                    datos[padre] = aux;

                    indice = padre;
                } 
                else {
                    return;
                }
            }
        }

        void bajar(int indice) {
            int tamanio = datos.getTamanio();
            bool continuar = true;

            while (continuar) {
                int izquierdo = 2 * indice + 1;
                int derecho = 2 * indice + 2;
                int menor = indice;

                if (izquierdo < tamanio && datos[izquierdo].getPrioridad() < datos[menor].getPrioridad()) {
                    menor = izquierdo;
                }

                if (derecho < tamanio && datos[derecho].getPrioridad() < datos[menor].getPrioridad()) {
                    menor = derecho;
                }

                if (menor != indice) {
                    T aux = datos[indice];
                    datos[indice] = datos[menor];
                    datos[menor] = aux;
                    indice = menor;
                } 
                else {
                    continuar = false;
                }
            }
        }

    public:
        ColaPrioridad() {}

        void encolar(T elemento) {
            datos.agregar(elemento);
            subir(datos.getTamanio() - 1);
        }

        T extraerPrimero() {
            if (vacia()) {
                throw runtime_error("No hay bicicletas en la cola de prioridad");
            }
            T elemento = datos[0];
            datos[0] = datos[datos.getTamanio() - 1];
            datos.eliminar(datos.getTamanio() - 1);

            if (datos.getTamanio() > 0) {
                bajar(0);
            }

            return elemento;
        }

        bool vacia() {
            return datos.getTamanio() == 0;
        }
};

#endif

