#ifndef TABLA_HASH_ESTACIONES_H
#define TABLA_HASH_ESTACIONES_H

#include "Estacion.h"

class TablaHashEstaciones {
private:
    struct Nodo {
        Estacion* estacion;
        Nodo* siguiente;

        Nodo(Estacion* e) {
            estacion = e;
            siguiente = nullptr;
        }
    };

    Nodo** tabla;
    int capacidad;
    int cantidad;
    int colisiones;

    int funcionHash(string codigo);

public:
    explicit TablaHashEstaciones(int capacidad = 11);
    ~TablaHashEstaciones();

    bool agregar(Estacion* estacion);
    Estacion* buscar(string codigo);
    bool eliminar(string codigo);

    void mostrarTodas();
    void listarPorCapacidad();
    void listarPorBicisDisponibles();
    void listarBajaOcupacion();

    int getCantidad();
    int getColisiones();
    double factorCarga();
    Estacion* obtenerEstacionPorIndice(int indice);
};

#endif
