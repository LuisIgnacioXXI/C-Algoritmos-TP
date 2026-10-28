#include "TablaHashEstaciones.h"

TablaHashEstaciones::TablaHashEstaciones() {
    cantidad = 0;
    colisiones = 0;

    for (int i = 0; i < TAMANIO; i++) {
        tabla[i] = nullptr;
    }
}

TablaHashEstaciones::~TablaHashEstaciones() {
    for (int i = 0; i < TAMANIO; i++) {
        NodoHash* actual = tabla[i];

        while (actual != nullptr) {
            NodoHash* siguiente = actual->getSiguiente();
            delete actual;
            actual = siguiente;
        }
    }
}

int TablaHashEstaciones::funcionHash(string codigo) {
    int suma = 0;

    for (int i = 0; i < codigo.length(); i++) {
        suma += codigo[i];
    }

    return suma % TAMANIO;
}

void TablaHashEstaciones::insertar(Estacion* estacion) {
    if (estacion == nullptr) {
        return;
    }

    string codigo = estacion->getCodigo();

    if (buscar(codigo) != nullptr) {
        return;
    }

    int indice = funcionHash(codigo);

    NodoHash* nuevo = new NodoHash(estacion);

    if (tabla[indice] != nullptr) {
        colisiones++;
    }

    nuevo->setSiguiente(tabla[indice]);
    tabla[indice] = nuevo;

    cantidad++;
}

Estacion* TablaHashEstaciones::buscar(string codigo) {
    int indice = funcionHash(codigo);
    NodoHash* actual = tabla[indice];

    while (actual != nullptr) {
        if (actual->getEstacion()->getCodigo() == codigo) {
            return actual->getEstacion();
        }

        actual = actual->getSiguiente();
    }

    return nullptr;
}

int TablaHashEstaciones::getCantidad() {
    return cantidad;
}

int TablaHashEstaciones::getColisiones() {
    return colisiones;
}

float TablaHashEstaciones::getFactorCarga() {
    return static_cast<float>(cantidad) / TAMANIO;
}

