#include "TablaHashEstaciones.h"
#include <iostream>

using namespace std;

TablaHashEstaciones::TablaHashEstaciones(int capacidad)
    : capacidad(capacidad > 0 ? capacidad : 11),
      cantidad(0),
      colisiones(0) {

    tabla = new Nodo*[this->capacidad];

    for (int i = 0; i < this->capacidad; i++) {
        tabla[i] = nullptr;
    }
}

TablaHashEstaciones::~TablaHashEstaciones() {
    for (int i = 0; i < capacidad; i++) {
        Nodo* actual = tabla[i];

        while (actual != nullptr) {
            Nodo* siguiente = actual->siguiente;

            delete actual->estacion;
            delete actual;

            actual = siguiente;
        }
    }

    delete[] tabla;
}

int TablaHashEstaciones::funcionHash(string codigo) {
    unsigned long suma = 0;

    for (char caracter : codigo) {
        suma += static_cast<unsigned char>(caracter);
    }

    return suma % capacidad;
}

bool TablaHashEstaciones::agregar(Estacion* estacion) {
    if (estacion == nullptr) {
        return false;
    }

    string codigo = estacion->getCodigo();
    int posicion = funcionHash(codigo);

    if (buscar(codigo) != nullptr) {
        return false;
    }

    if (tabla[posicion] != nullptr) {
        colisiones++;
    }

    Nodo* nuevo = new Nodo(estacion);
    nuevo->siguiente = tabla[posicion];
    tabla[posicion] = nuevo;

    cantidad++;

    return true;
}


Estacion* TablaHashEstaciones::buscar(string codigo) {
    int posicion = funcionHash(codigo);
    Nodo* actual = tabla[posicion];

    while (actual != nullptr) {
        if (actual->estacion->getCodigo() == codigo) {
            return actual->estacion;
        }

        actual = actual->siguiente;
    }

    return nullptr;
}



bool TablaHashEstaciones::eliminar(string codigo) {
    int posicion = funcionHash(codigo);

    Nodo* actual = tabla[posicion];
    Nodo* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->estacion->getCodigo() == codigo) {

            if (anterior == nullptr) {
                tabla[posicion] = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }

            delete actual->estacion;
            delete actual;
            cantidad--;

            return true;
        }

        anterior = actual;
        actual = actual->siguiente;
    }

    return false;
}


int TablaHashEstaciones::getCantidad() {
    return cantidad;
}

int TablaHashEstaciones::getColisiones() {
    return colisiones;
}

double TablaHashEstaciones::factorCarga() {
    return static_cast<double>(cantidad) / capacidad;
}

void TablaHashEstaciones::mostrarTodas() {
    for (int i = 0; i < capacidad; i++) {
        Nodo* actual = tabla[i];

        while (actual != nullptr) {
            actual->estacion->mostrarInformacion();
            cout << endl;

            actual = actual->siguiente;
        }
    }
}


void TablaHashEstaciones::listarPorCapacidad() {
    if (cantidad == 0) {
        cout << "No hay estaciones cargadas" << endl;
        return;
    }

    Estacion** estaciones = new Estacion*[cantidad];
    int indice = 0;

    for (int i = 0; i < capacidad; i++) {
        Nodo* actual = tabla[i];

        while (actual != nullptr) {
            estaciones[indice] = actual->estacion;
            indice++;
            actual = actual->siguiente;
        }
    }

    for (int i = 0; i < cantidad - 1; i++) {
        for (int j = 0; j < cantidad - 1 - i; j++) {
            if (estaciones[j]->getCapacidadAnclajes() >
                estaciones[j + 1]->getCapacidadAnclajes()) {

                Estacion* auxiliar = estaciones[j];
                estaciones[j] = estaciones[j + 1];
                estaciones[j + 1] = auxiliar;
            }
        }
    }

    cout << "Estaciones ordenadas por capacidad:" << endl;

    for (int i = 0; i < cantidad; i++) {
        estaciones[i]->mostrarInformacion();
        cout << endl;
    }

    delete[] estaciones;
}

void TablaHashEstaciones::listarPorBicisDisponibles() {
    if (cantidad == 0) {
        cout << "No hay estaciones cargadas" << endl;
        return;
    }

    Estacion** estaciones = new Estacion*[cantidad];
    int indice = 0;

    for (int i = 0; i < capacidad; i++) {
        Nodo* actual = tabla[i];

        while (actual != nullptr) {
            estaciones[indice] = actual->estacion;
            indice++;
            actual = actual->siguiente;
        }
    }

    for (int i = 0; i < cantidad - 1; i++) {
        for (int j = 0; j < cantidad - 1 - i; j++) {
            if (estaciones[j]->getCantidadBicisDisponibles() >
                estaciones[j + 1]->getCantidadBicisDisponibles()) {

                Estacion* auxiliar = estaciones[j];
                estaciones[j] = estaciones[j + 1];
                estaciones[j + 1] = auxiliar;
            }
        }
    }

    cout << "Estaciones ordenadas por bicicletas disponibles:" << endl;

    for (int i = 0; i < cantidad; i++) {
        estaciones[i]->mostrarInformacion();
        cout << endl;
    }

    delete[] estaciones;
}


void TablaHashEstaciones::listarBajaOcupacion() {
    bool encontrada = false;

    cout << "Estaciones con menos del 20% de ocupacion:" << endl;

    for (int i = 0; i < capacidad; i++) {
        Nodo* actual = tabla[i];

        while (actual != nullptr) {
            Estacion* estacion = actual->estacion;
            double ocupacion = static_cast<double>(estacion->getCantidadBicisDisponibles()) / estacion->getCapacidadAnclajes();

            if (ocupacion < 0.20) {
                estacion->mostrarInformacion();
                cout << "Ocupacion: " << ocupacion * 100 << "%" << endl;
                cout << endl;
                encontrada = true;
            }
            actual = actual->siguiente;
        }
    }

    if (!encontrada) {
        cout << "No hay estaciones con baja ocupacion" << endl;
    }
}


Estacion* TablaHashEstaciones::obtenerEstacionPorIndice(int indice) {
    if (indice < 0 || indice >= cantidad) {
        return nullptr;
    }

    int contador = 0;

    for (int i = 0; i < capacidad; i++) {
        Nodo* actual = tabla[i];

        while (actual != nullptr) {
            if (contador == indice) {
                return actual->estacion;
            }

            contador++;
            actual = actual->siguiente;
        }
    }

    return nullptr;
}



