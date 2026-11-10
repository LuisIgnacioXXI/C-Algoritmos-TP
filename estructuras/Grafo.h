#ifndef GRAFO_H
#define GRAFO_H

#include <string>
using namespace std;

class Grafo {
    private:
        struct NodoAdyacente {
            string codigoEstacion;
            NodoAdyacente* siguiente;

            NodoAdyacente(string codigo) {
                this->codigoEstacion = codigo;
                this->siguiente = nullptr;
            }
        };

        struct NodoEstacion {
            string codigo;
            NodoAdyacente* adyacentes;
            NodoEstacion* siguiente;

            NodoEstacion(string codigo) {
                this->codigo = codigo;
                this->adyacentes = nullptr;
                this->siguiente = nullptr;
            }
        };

        NodoEstacion* estaciones;

        NodoEstacion* buscarNodo(string codigo);
        void liberarAdyacentes(NodoAdyacente* nodo);

    public:
        Grafo();
        ~Grafo();

        void agregarEstacion(string codigo);
        void agregarConexion(string origen, string destino);

        void mostrarConexiones();
        void caminoMasCorto(string origen, string destino);

        void eliminarEstacion(string codigo);
        void eliminarAdyacencia(NodoEstacion* estacion, string codigo);
};

#endif

