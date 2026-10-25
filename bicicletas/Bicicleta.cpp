#include "Bicicleta.h"

Bicicleta::Bicicleta() {
    biciId = 0;
    codigoEstacion = "";
    tipo = "";
    estado = "Averiada";
    kilometros = 0;
    prioridad = 3;
    prestada = false;
}

Bicicleta::Bicicleta(int biciId, string codigoEstacion, string tipo, string estado, int kilometros) {
    this->biciId = biciId;
    this->codigoEstacion = codigoEstacion;
    this->tipo = tipo;
    this->estado = estado;
    this->kilometros = kilometros;
    this->prestada = false;
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

int Bicicleta::getPrioridad(){
    return prioridad;
}

void Bicicleta::setEstado(string nuevoEstado) {
    estado = nuevoEstado;
}

void Bicicleta::setCodigoEstacion(string nuevoCodigo) {
    codigoEstacion = nuevoCodigo;
}

void Bicicleta::setPrioridad(int nuevaPrioridad){
    prioridad = nuevaPrioridad;
}

bool Bicicleta::getPrestada() {
    return prestada;
}

void Bicicleta::setPrestada(bool prestada) {
    this->prestada = prestada;
}
