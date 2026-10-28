#ifndef NODO_HASH_H
#define NODO_HASH_H

#include "../estaciones/Estacion.h"

class NodoHash {
    private:
        Estacion* estacion;
        NodoHash* siguiente;

    public:
        NodoHash(Estacion* estacion);

        Estacion* getEstacion();
        NodoHash* getSiguiente();

        void setSiguiente(NodoHash* siguiente);
};

#endif
