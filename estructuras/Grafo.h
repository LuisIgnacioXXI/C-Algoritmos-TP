#ifndef GRAFO_H
#define GRAFO_H

#include <string>
using namespace std;

class Grafo {
private:
    struct NodoAdyacente {
        string codigoEstacion;
        NodoAdyacente* siguiente;

        NodoAdyacente(const string& codigo)
            : codigoEstacion(codigo), siguiente(nullptr) {}
    };

    struct NodoEstacion {
        string codigo;
        NodoAdyacente* adyacentes;
        NodoEstacion* siguiente;

        NodoEstacion(const string& cod)
            : codigo(cod), adyacentes(nullptr), siguiente(nullptr) {}
    };

    NodoEstacion* estaciones;

    NodoEstacion* buscarNodo(const string& codigo);
    void liberarAdyacentes(NodoAdyacente* nodo);

public:
    Grafo();
    ~Grafo();

    bool agregarEstacion(const string& codigo);
    bool agregarConexion(const string& origen, const string& destino);

    void mostrarConexiones();
    void caminoMasCorto(const string& origen, const string& destino);

    bool eliminarEstacion(const string& codigo);
};

#endif
