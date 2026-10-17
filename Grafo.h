#ifndef GRAFO_H
#define GRAFO_H

#include <string>

class Grafo {
private:
    struct NodoAdyacente {
        std::string codigoEstacion;
        NodoAdyacente* siguiente;

        NodoAdyacente(const std::string& codigo)
            : codigoEstacion(codigo), siguiente(nullptr) {}
    };

    struct NodoEstacion {
        std::string codigo;
        NodoAdyacente* adyacentes;
        NodoEstacion* siguiente;

        NodoEstacion(const std::string& cod)
            : codigo(cod), adyacentes(nullptr), siguiente(nullptr) {}
    };

    NodoEstacion* estaciones;

    NodoEstacion* buscarNodo(const std::string& codigo);
    void liberarAdyacentes(NodoAdyacente* nodo);

public:
    Grafo();
    ~Grafo();

    bool agregarEstacion(const std::string& codigo);
    bool agregarConexion(const std::string& origen,
                         const std::string& destino);

    void mostrarConexiones();
    void caminoMasCorto(const std::string& origen,
                        const std::string& destino);

    bool eliminarEstacion(const std::string& codigo);
};

#endif
