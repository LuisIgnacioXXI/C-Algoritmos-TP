#ifndef TABLA_HASH_ESTACIONES_H
#define TABLA_HASH_ESTACIONES_H

#include "NodoHash.h"
#include <string>

using namespace std;

class TablaHashEstaciones {
private:
    static const int TAMANIO = 11;

    NodoHash* tabla[TAMANIO];
    int cantidad;
    int colisiones;

    int funcionHash(string codigo);

public:
    TablaHashEstaciones();
    ~TablaHashEstaciones();

    void insertar(Estacion* estacion);
    Estacion* buscar(string codigo);

    int getCantidad();
    int getColisiones();
    float getFactorCarga();
};

#endif
