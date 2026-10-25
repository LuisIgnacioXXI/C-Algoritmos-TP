#ifndef NODO_ABB_H
#define NODO_ABB_H

#include "../bicicletas/Bicicleta.h"

class NodoABB {
    private:
        Bicicleta bicicleta;
        NodoABB* izquierdo;
        NodoABB* derecho;

    public:
        NodoABB(Bicicleta bicicleta);

        Bicicleta* getBicicleta();
        NodoABB* getIzquierdo();
        NodoABB* getDerecho();

        void setIzquierdo(NodoABB* nuevoIzquierdo);
        void setDerecho(NodoABB* nuevoDerecho);

        void insertarNodo(NodoABB* nodoNuevo);
        Bicicleta* buscarNodo(int biciId);
        void listarInorderNodo();
        int contarAveriadasNodo();
        int obtenerAlturaNodo();
        void destruirNodo();

        NodoABB* eliminarNodo(int biciId);

        bool listarPorKilometrosNodo(int kilometrosMinimos);

        Bicicleta* buscarDisponibleEnEstacionNodo(string codigoEstacion);
};

#endif
