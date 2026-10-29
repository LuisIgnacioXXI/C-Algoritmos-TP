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

int TablaHashEstaciones::getCantidad() {
    return cantidad;
}

int TablaHashEstaciones::getColisiones() {
    return colisiones;
}

float TablaHashEstaciones::getFactorCarga() {
    return static_cast<float>(cantidad) / TAMANIO;
}


int TablaHashEstaciones::funcionHash(string codigo) {
    int suma = 0;
    for (int i = 0; i < codigo.length(); i++) {
        suma += codigo[i];
    }
    return suma % TAMANIO;
}

void TablaHashEstaciones::insertar(Estacion* estacion) {
    if (estacion == nullptr || buscar(estacion->getCodigo()) != nullptr) {
        return;
    }

    int indice = funcionHash(estacion->getCodigo());

    NodoHash* nuevo = new NodoHash(estacion);

    if (tabla[indice] != nullptr) {
        colisiones++;
    }

    nuevo->setSiguiente(tabla[indice]);
    tabla[indice] = nuevo;

    cantidad++;
}

Estacion* TablaHashEstaciones::buscar(string codigo) {
    Estacion* estacionEncontrada = nullptr;
    int indice = funcionHash(codigo);
    NodoHash* actual = tabla[indice];

    while (actual != nullptr && estacionEncontrada == nullptr) {
        if (actual->getEstacion()->getCodigo() == codigo) {
            estacionEncontrada = actual->getEstacion();
        }
        actual = actual->getSiguiente();
    }

    return estacionEncontrada;
}


void TablaHashEstaciones::eliminar(string codigo) {
    int indice = funcionHash(codigo);
    NodoHash* actual = tabla[indice];
    NodoHash* anterior = nullptr;

    while (actual != nullptr && actual->getEstacion()->getCodigo() != codigo) {
        anterior = actual;
        actual = actual->getSiguiente();
    }

    if (actual != nullptr) {
        if (anterior == nullptr) {
            tabla[indice] = actual->getSiguiente();
        } 
        else {
            anterior->setSiguiente(actual->getSiguiente());
        }

        delete actual;
        cantidad--;
    }
}


