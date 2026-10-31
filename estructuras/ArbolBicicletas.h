#ifndef ARBOL_BICICLETAS_H
#define ARBOL_BICICLETAS_H

#include "NodoABB.h"

class ArbolBicicletas {
    private:
        NodoABB* raiz;

    public:
        ArbolBicicletas();
        ~ArbolBicicletas();

        bool estaVacio();

        void insertar(Bicicleta bicicleta);
        Bicicleta* buscar(int biciId);
        void listarInorder();
        int contarAveriadas();
        int obtenerAltura();

        void eliminar(int biciId);

        void listarPorKilometros(int kilometrosMinimos);

        Bicicleta* buscarDisponibleEnEstacion(string codigoEstacion);
};

#endif

