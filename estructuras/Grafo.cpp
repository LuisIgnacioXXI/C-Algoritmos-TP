#include "Grafo.h"
#include <iostream>
#include "Vector.h"
#include "Cola.h"

Grafo::Grafo() : estaciones(nullptr) {}

Grafo::~Grafo() {
    while (estaciones != nullptr) {
        NodoEstacion* siguiente = estaciones->siguiente;
        liberarAdyacentes(estaciones->adyacentes);
        delete estaciones;
        estaciones = siguiente;
    }
}

void Grafo::liberarAdyacentes(NodoAdyacente* nodo) {
    while (nodo != nullptr) {
        NodoAdyacente* siguiente = nodo->siguiente;
        delete nodo;
        nodo = siguiente;
    }
}

Grafo::NodoEstacion* Grafo::buscarNodo(string codigo) {
    NodoEstacion* actual = estaciones;

    while (actual != nullptr) {
        if (actual->codigo == codigo) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

bool Grafo::agregarEstacion(string codigo) {
    if (buscarNodo(codigo) != nullptr) {
        cout << "No se puede agregar: la estacion " << codigo << " ya existe" << endl;
        return false;
    }
    NodoEstacion* nueva = new NodoEstacion(codigo);
    nueva->siguiente = estaciones;
    estaciones = nueva;

    cout << "Estacion " << codigo << " agregada correctamente" << endl;

    return true;
}

bool Grafo::agregarConexion(string origen, string destino) {
    if (origen == destino) {
        cout << "No se puede conectar una estacion consigo misma" << endl;
        return false;
    }

    NodoEstacion* nodoOrigen = buscarNodo(origen);
    NodoEstacion* nodoDestino = buscarNodo(destino);

    if (nodoOrigen == nullptr || nodoDestino == nullptr) {
        cout << "No se puede agregar la conexion: alguna estacion no existe" << endl;
        return false;
    }

    NodoAdyacente* actual = nodoOrigen->adyacentes;
    while (actual != nullptr) {
        if (actual->codigoEstacion == destino) {
            cout << "La conexion entre las estaciones ya existe" << endl;
            return false;
        }
        actual = actual->siguiente;
    }

    NodoAdyacente* nuevaOrigen = new NodoAdyacente(destino);
    nuevaOrigen->siguiente = nodoOrigen->adyacentes;
    nodoOrigen->adyacentes = nuevaOrigen;

    NodoAdyacente* nuevaDestino = new NodoAdyacente(origen);
    nuevaDestino->siguiente = nodoDestino->adyacentes;
    nodoDestino->adyacentes = nuevaDestino;

    cout << "Conexion agregada correctamente" << endl;

    return true;
}

void Grafo::mostrarConexiones() {
    NodoEstacion* actual = estaciones;

    while (actual != nullptr) {
        cout << actual->codigo << " -> ";

        NodoAdyacente* adyacente = actual->adyacentes;

        while (adyacente != nullptr) {
            cout << adyacente->codigoEstacion;

            if (adyacente->siguiente != nullptr) {
                cout << ", ";
            }
            adyacente = adyacente->siguiente;
        }

        cout << endl;
        actual = actual->siguiente;
    }
}

void Grafo::caminoMasCorto(string origen, string destino) {

    // 1. Verificar que existan las estaciones
    if (buscarNodo(origen) == nullptr || buscarNodo(destino) == nullptr) {
        cout << "Error: alguna estacion no existe en el grafo" << endl;
        return;
    }

    if (origen == destino) {
        cout << "Camino mas corto: " << origen << endl;
        cout << "Cantidad de tramos: 0" << endl;
        return;
    }

    // 2. Crear las estructuras necesarias para el BFS
    Cola<string> cola;
    Vector<string> visitadas;
    Vector<string> predecesoras;

    // 3. Comenzar desde la estacion de origen
    cola.encolar(origen);
    visitadas.agregar(origen);
    predecesoras.agregar("");

    bool encontrado = false;

    // 4. Recorrer las estaciones utilizando BFS
    while (!cola.vacia() && !encontrado) {

        string codigoActual = cola.frente();
        cola.desencolar();

        NodoEstacion* actual = buscarNodo(codigoActual);
        NodoAdyacente* vecino = actual->adyacentes;

        while (vecino != nullptr && !encontrado) {

            // Comprobar si el vecino ya fue visitado
            if (visitadas.buscarPosicion(vecino->codigoEstacion) == -1) {

                // Registrar el vecino y desde donde llegamos
                visitadas.agregar(vecino->codigoEstacion);
                predecesoras.agregar(codigoActual);

                // Agregarlo a la cola para visitarlo despues
                cola.encolar(vecino->codigoEstacion);

                if (vecino->codigoEstacion == destino) {
                    encontrado = true;
                }
            }

            vecino = vecino->siguiente;
        }
    }

    // 5. Reconstruir y mostrar el camino
    if (encontrado) {

        Vector<string> camino;
        string codigoActual = destino;

        while (codigoActual != "") {

            camino.agregar(codigoActual);

            if (codigoActual == origen) {
                break;
            }

            // Buscar la predecesora de la estacion actual
            int posicion = visitadas.buscarPosicion(codigoActual);

            if (posicion != -1) {
                codigoActual = predecesoras[posicion];
            }
        }

        cout << "Camino mas corto: ";

        for (int i = camino.getTamanio() - 1; i >= 0; i--) {
            cout << camino[i];

            if (i > 0) {
                cout << " -> ";
            }
        }

        cout << endl;
        cout << "Cantidad de tramos: " << camino.getTamanio() - 1 << endl;
    }
    else {
        cout << "No existe un camino entre " << origen << " y " << destino << endl;
    }
}




bool Grafo::eliminarEstacion(string codigo) {
    NodoEstacion* actual = estaciones;
    NodoEstacion* anterior = nullptr;

    // 1. Buscar la estacion que queremos eliminar
    while (actual != nullptr && actual->codigo != codigo) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == nullptr) {
        cout << "No se puede eliminar: la estacion " << codigo << " no existe" << endl;
        return false;
    }

    // 2. Eliminar las conexiones que apuntan a esa estacion
    NodoEstacion* otra = estaciones;

    while (otra != nullptr) {
        eliminarAdyacencia(otra, codigo);
        otra = otra->siguiente;
    }

    // 3. Quitar la estacion de la lista principal
    if (anterior == nullptr) {
        estaciones = actual->siguiente;
    }
    else {
        anterior->siguiente = actual->siguiente;
    }

    // 4. Liberar su memoria
    liberarAdyacentes(actual->adyacentes);
    delete actual;

    cout << "Estacion " << codigo << " eliminada correctamente" << endl;

    return true;
}



void Grafo::eliminarAdyacencia(NodoEstacion* estacion, string codigo) {
    NodoAdyacente* actual = estacion->adyacentes;
    NodoAdyacente* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->codigoEstacion == codigo) {

            if (anterior == nullptr) {
                estacion->adyacentes = actual->siguiente;
            }
            else {
                anterior->siguiente = actual->siguiente;
            }

            delete actual;
            return;
        }

        anterior = actual;
        actual = actual->siguiente;
    }
}
