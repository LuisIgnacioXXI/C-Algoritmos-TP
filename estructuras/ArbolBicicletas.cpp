#include "ArbolBicicletas.h"
#include <iostream>

using namespace std;

// Constructor
ArbolBicicletas::ArbolBicicletas() {
    raiz = nullptr;
}

ArbolBicicletas::~ArbolBicicletas() {
    if (raiz != nullptr) {
        raiz->destruirNodo();
        raiz = nullptr;
    }
}

bool ArbolBicicletas::estaVacio() {
    return raiz == nullptr;
}

void ArbolBicicletas::insertar(Bicicleta bicicleta) {
    NodoABB* nodoNuevo = new NodoABB(bicicleta);
    if (estaVacio()) {
        raiz = nodoNuevo;
    } 
    else {
        raiz->insertarNodo(nodoNuevo);
    }
}

Bicicleta* ArbolBicicletas::buscar(int biciId) {
    Bicicleta* biciEncontrada = nullptr;
    if (!estaVacio()) {
        biciEncontrada = raiz->buscarNodo(biciId);
    }
    return biciEncontrada;
}

void ArbolBicicletas::listarInorder() {
    if (!estaVacio()) {
        raiz->listarInorderNodo();
    }
}

int ArbolBicicletas::contarAveriadas() {
    int contador = 0;
    if (!estaVacio()) {
        contador = raiz->contarAveriadasNodo();
    }
    return contador;
}

int ArbolBicicletas::obtenerAltura() {
    int altura = 0;
    if (!estaVacio()) {
        altura = raiz->obtenerAlturaNodo();
    }
    return altura;
}

void ArbolBicicletas::eliminar(int biciId) {
    if (buscar(biciId) != nullptr) {
        raiz = raiz->eliminarNodo(biciId);
    }
}

void ArbolBicicletas::listarPorKilometros(int kilometrosMinimos) {
    bool encontrado = false;

    if (!estaVacio()) {
        encontrado = raiz->listarPorKilometrosNodo(kilometrosMinimos);
    }

    if (!encontrado) {
        cout << "No hay bicicletas que superen ese kilometraje" << endl;
    }
}

Bicicleta* ArbolBicicletas::buscarDisponibleEnEstacion(string codigoEstacion) {
    Bicicleta* biciEncontrada = nullptr;
    if (!estaVacio()) {
        biciEncontrada = raiz->buscarDisponibleEnEstacionNodo(codigoEstacion);
    }
    return biciEncontrada;
}
