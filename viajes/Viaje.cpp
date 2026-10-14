#include "Viaje.h"

Viaje::Viaje(int viajeId, int biciId, int dniUsuario, string estacionOrigen, string estacionDestino, int fecha, int duracionMin) {
    this->viajeId = viajeId;
    this->biciId = biciId;
    this->dniUsuario = dniUsuario;
    this->estacionOrigen = estacionOrigen;
    this->estacionDestino = estacionDestino;
    this->fecha = fecha;
    this->duracionMin = duracionMin;
}

int Viaje::getViajeId() {
    return viajeId;
}

int Viaje::getBiciId() {
    return biciId;
}

int Viaje::getDniUsuario() {
    return dniUsuario;
}

string Viaje::getEstacionOrigen() {
    return estacionOrigen;
}

string Viaje::getEstacionDestino() {
    return estacionDestino;
}

int Viaje::getFecha() {
    return fecha;
}

int Viaje::getDuracionMin() {
    return duracionMin;
}
