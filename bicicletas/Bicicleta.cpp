#include "Bicicleta.h"

Bicicleta::Bicicleta(int biciId, string codigoEstacion, string tipo, string estado, int kilometros) {
    this->biciId = biciId;
    this->codigoEstacion = codigoEstacion;
    this->tipo = tipo;
    this->estado = estado;
    this->kilometros = kilometros;
}

int Bicicleta::getBiciId() {
    return biciId;
}

string Bicicleta::getCodigoEstacion() {
    return codigoEstacion;
}

string Bicicleta::getTipo() {
    return tipo;
}

string Bicicleta::getEstado() {
    return estado;
}

int Bicicleta::getKilometros() {
    return kilometros;
}

