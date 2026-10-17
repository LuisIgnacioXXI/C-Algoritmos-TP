
#include "Grafo.h"
#include <iostream>
using namespace std;

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

Grafo::NodoEstacion* Grafo::buscarNodo(const string& codigo) {
    NodoEstacion* actual = estaciones;

    while (actual != nullptr) {
        if (actual->codigo == codigo) {
            return actual;
        }
        actual = actual->siguiente;
    }

    return nullptr;
}

bool Grafo::agregarEstacion(const string& codigo) {
    if (buscarNodo(codigo) != nullptr) {
        return false;
    }

    NodoEstacion* nueva = new NodoEstacion(codigo);
    nueva->siguiente = estaciones;
    estaciones = nueva;

    return true;
}

bool Grafo::agregarConexion(const string& origen,
                            const string& destino) {
    if (origen == destino) {
        return false;
    }

    NodoEstacion* nodoOrigen = buscarNodo(origen);
    NodoEstacion* nodoDestino = buscarNodo(destino);

    if (nodoOrigen == nullptr || nodoDestino == nullptr) {
        return false;
    }

    NodoAdyacente* actual = nodoOrigen->adyacentes;
    while (actual != nullptr) {
        if (actual->codigoEstacion == destino) {
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

void Grafo::caminoMasCorto(const string& origen,
                           const string& destino) {
    if (buscarNodo(origen) == nullptr ||
        buscarNodo(destino) == nullptr) {
        cout << "Error: alguna estacion no existe en el grafo."
             << endl;
        return;
    }

    if (origen == destino) {
        cout << "Camino mas corto: " << origen << endl;
        cout << "Cantidad de tramos: 0" << endl;
        return;
    }

    int cantidad = 0;
    NodoEstacion* actual = estaciones;

    while (actual != nullptr) {
        cantidad++;
        actual = actual->siguiente;
    }

    string* visitadas = new string[cantidad];
    string* predecesoras = new string[cantidad];
    string* cola = new string[cantidad];

    int inicio = 0;
    int fin = 0;
    int cantidadVisitadas = 0;

    cola[fin++] = origen;
    visitadas[cantidadVisitadas] = origen;
    predecesoras[cantidadVisitadas] = "";
    cantidadVisitadas++;

    bool encontrado = false;

    while (inicio < fin && !encontrado) {
        string codigoActual = cola[inicio++];
        NodoEstacion* nodoActual = buscarNodo(codigoActual);

        NodoAdyacente* vecino = nodoActual->adyacentes;

        while (vecino != nullptr && !encontrado) {
            bool yaVisitada = false;

            for (int i = 0; i < cantidadVisitadas; i++) {
                if (visitadas[i] == vecino->codigoEstacion) {
                    yaVisitada = true;
                    break;
                }
            }

            if (!yaVisitada) {
                visitadas[cantidadVisitadas] =
                    vecino->codigoEstacion;
                predecesoras[cantidadVisitadas] = codigoActual;
                cantidadVisitadas++;

                cola[fin++] = vecino->codigoEstacion;

                if (vecino->codigoEstacion == destino) {
                    encontrado = true;
                }
            }

            vecino = vecino->siguiente;
        }
    }

    if (encontrado) {
        string* camino = new string[cantidad];
        int longitud = 0;
        string codigo = destino;

        while (codigo != "") {
            camino[longitud++] = codigo;

            if (codigo == origen) {
                break;
            }

            string anterior = "";

            for (int i = 0; i < cantidadVisitadas; i++) {
                if (visitadas[i] == codigo) {
                    anterior = predecesoras[i];
                    break;
                }
            }

            codigo = anterior;
        }

        cout << "Camino mas corto: ";

        for (int i = longitud - 1; i >= 0; i--) {
            cout << camino[i];

            if (i > 0) {
                cout << " -> ";
            }
        }

        cout << endl;
        cout << "Cantidad de tramos: " << longitud - 1 << endl;

        delete[] camino;
    } else {
        cout << "No existe un camino entre "
             << origen << " y " << destino << "." << endl;
    }

    delete[] visitadas;
    delete[] predecesoras;
    delete[] cola;
}


bool Grafo::eliminarEstacion(const string& codigo) {
    NodoEstacion* actual = estaciones;
    NodoEstacion* anterior = nullptr;

    while (actual != nullptr && actual->codigo != codigo) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == nullptr) {
        return false;
    }

    NodoEstacion* otra = estaciones;

    while (otra != nullptr) {
        NodoAdyacente* vecino = otra->adyacentes;
        NodoAdyacente* anteriorVecino = nullptr;

        while (vecino != nullptr) {
            if (vecino->codigoEstacion == codigo) {
                if (anteriorVecino == nullptr) {
                    otra->adyacentes = vecino->siguiente;
                } else {
                    anteriorVecino->siguiente = vecino->siguiente;
                }

                delete vecino;
                break;
            }

            anteriorVecino = vecino;
            vecino = vecino->siguiente;
        }

        otra = otra->siguiente;
    }

    if (anterior == nullptr) {
        estaciones = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    liberarAdyacentes(actual->adyacentes);
    delete actual;

    return true;
}
