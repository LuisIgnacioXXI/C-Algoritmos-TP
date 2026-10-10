#include "Estacion.h"

Estacion::Estacion(string codigo, string nombre, string barrio, int capacidadAnclajes, int cantidadBicisDisponibles) {
    this->codigo = codigo;
    this->nombre = nombre;
    this->barrio = barrio;
    this->capacidadAnclajes = capacidadAnclajes;
    this->cantidadBicisDisponibles = cantidadBicisDisponibles;
}

string Estacion:: getCodigo() {
    return this->codigo;
}

string Estacion::getNombre() {
    return this->nombre;
}

string Estacion::getBarrio() {
    return this->barrio;
}

int Estacion::getCapacidadAnclajes(){
    return this->capacidadAnclajes;
}

int Estacion::getCantidadBicisDisponibles(){
    return this->cantidadBicisDisponibles;
}



