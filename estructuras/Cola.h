#ifndef COLA_H
#define COLA_H

#include "Vector.h"

template <typename T>

class Cola {
    private:
        Vector<T> elementos;

    public:
        Cola() {}

        void encolar(T& elemento) {
            elementos.agregar(elemento);
        }

        void desencolar() {
            if (!vacia()) {
                elementos.eliminar(0);
            }
        }

        T frente() {
            return elementos[0];
        }

        bool vacia() {
            return elementos.getTamanio() == 0;
        }

        int getTamanio() {
            return elementos.getTamanio();
        }
};

#endif
