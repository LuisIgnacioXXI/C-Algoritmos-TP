#include "NodoHash.h"

NodoHash::NodoHash(Estacion* estacion) {
    this->estacion = estacion;
    this->siguiente = nullptr;
}

Estacion* NodoHash::getEstacion() {
    return estacion;
}

NodoHash* NodoHash::getSiguiente() {
    return siguiente;
}

void NodoHash::setSiguiente(NodoHash* siguiente) {
    this->siguiente = siguiente;
}
