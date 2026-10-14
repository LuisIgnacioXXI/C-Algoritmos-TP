#include "Estacion.h"
#include <iostream>

Estacion::Estacion(string codigo, string nombre, string barrio, int capacidadAnclajes, int cantidadBicisDisponibles) {
    this->codigo = codigo;
    this->nombre = nombre;
    this->barrio = barrio;
    this->capacidadAnclajes = capacidadAnclajes;
    this->cantidadBicisDisponibles = cantidadBicisDisponibles;
}

string Estacion:: getCodigo() {
    return codigo;
}

string Estacion::getNombre() {
    return nombre;
}

string Estacion::getBarrio() {
    return barrio;
}

int Estacion::getCapacidadAnclajes(){
    return capacidadAnclajes;
}

int Estacion::getCantidadBicisDisponibles(){
    return cantidadBicisDisponibles;
}

void Estacion::mostrarInformacion() {
    cout << "ESTACION: " << endl;
    cout << "Codigo: " << codigo << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Barrio: " << barrio << endl;
    cout << "Capacidad de anclajes: " << capacidadAnclajes << endl;
    cout << "Bicicletas disponibles: " << cantidadBicisDisponibles << endl;
}

