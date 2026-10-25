#include "NodoABB.h"
#include <iostream>
using namespace std;

NodoABB::NodoABB(Bicicleta bicicleta) {
    this->bicicleta = bicicleta;
    this->izquierdo = nullptr;
    this->derecho = nullptr;
}

Bicicleta* NodoABB::getBicicleta() {
    return &bicicleta;
}

NodoABB* NodoABB::getIzquierdo() {
    return izquierdo;
}

NodoABB* NodoABB::getDerecho() {
    return derecho;
}

void NodoABB::setIzquierdo(NodoABB* nuevoIzquierdo) {
    izquierdo = nuevoIzquierdo;
}

void NodoABB::setDerecho(NodoABB* nuevoDerecho) {
    derecho = nuevoDerecho;
}

void NodoABB::insertarNodo(NodoABB* nodoNuevo) {
    int idNuevo = nodoNuevo->getBicicleta()->getBiciId();
    int idActual = bicicleta.getBiciId();

    if (idNuevo < idActual) {
        if (izquierdo == nullptr) {
            izquierdo = nodoNuevo;
        } 
        else {
            izquierdo->insertarNodo(nodoNuevo);
        }
    } 
    else if (idNuevo > idActual) {
        if (derecho == nullptr) {
            derecho = nodoNuevo;
        } 
        else {
            derecho->insertarNodo(nodoNuevo);
        }
    } 
    else {
        delete nodoNuevo;
    }
}

Bicicleta* NodoABB::buscarNodo(int biciId) {
    Bicicleta* biciEncontrada = nullptr;
    int idActual = bicicleta.getBiciId();

    if (biciId == idActual) {
        biciEncontrada = &bicicleta;
    }
    else if (biciId < idActual) {
        if (izquierdo != nullptr) {
            biciEncontrada = izquierdo->buscarNodo(biciId);
        }
    } 
    else {
        if (derecho != nullptr) {
            biciEncontrada = derecho->buscarNodo(biciId);
        }
    }

    return biciEncontrada;
}

void NodoABB::listarInorderNodo() {
    if (izquierdo != nullptr) {
        izquierdo->listarInorderNodo();
    }
    cout << "ID: " << bicicleta.getBiciId() << endl;
    cout << "Estacion: " << bicicleta.getCodigoEstacion() << endl;
    cout << "Tipo: " << bicicleta.getTipo() << endl;
    cout << "Estado: " << bicicleta.getEstado() << endl;
    cout << "Kilometros: " << bicicleta.getKilometros() << endl;
    if (derecho != nullptr) {
        derecho->listarInorderNodo();
    }
}

int NodoABB::contarAveriadasNodo() {
    int cantidad = 0;

    // Contar la bicicleta actual
    if (bicicleta.getEstado() == "Averiada") {
        cantidad += 1;
    }

    // Contar las bicicletas averiadas del subárbol izquierdo
    if (izquierdo != nullptr) {
        cantidad += izquierdo->contarAveriadasNodo();
    }

    // Contar las bicicletas averiadas del subárbol derecho
    if (derecho != nullptr) {
        cantidad += derecho->contarAveriadasNodo();
    }

    return cantidad;
}

int NodoABB::obtenerAlturaNodo() {
    int alturaIzquierda = 0;
    int alturaDerecha = 0;
    int altura = 0;

    if (izquierdo != nullptr) {
        alturaIzquierda = izquierdo->obtenerAlturaNodo();
    }

    if (derecho != nullptr) {
        alturaDerecha = derecho->obtenerAlturaNodo();
    }

    if (alturaIzquierda > alturaDerecha) {
        altura = alturaIzquierda + 1;
    }
    else {
        altura = alturaDerecha + 1;
    }

    return altura;
}

void NodoABB::destruirNodo() {
    if (izquierdo != nullptr) {
        izquierdo->destruirNodo();
    }

    if (derecho != nullptr) {
        derecho->destruirNodo();
    }

    delete this;
}

/*
Si las bicicletas se cargan ordenadas por ID creciente, el árbol binario de búsqueda queda degenerado,
ya que cada nuevo ID es mayor que los anteriores y se inserta como hijo derecho del último nodo.

Por ejemplo, si insertamos las bicicletas con ID 10, 20, 30, 40 y 50, el árbol tendrá una altura
de 5 niveles. Para buscar la bicicleta con ID 50 será necesario recorrer los cinco nodos. 
En general, la búsqueda puede tener un costo de O(n).

En cambio, si insertamos los mismos ID en un orden que distribuya mejor los nodos,
 por ejemplo 30, 20, 40, 10 y 50, obtenemos un árbol de 3 niveles. 
 Buscar la bicicleta 50 requiere visitar solo tres nodos.

El método `insertarNodo()` es el mismo en ambos casos: la diferencia se debe al orden de inserción.
Como nuestro árbol no se reequilibra automáticamente, insertar los datos ordenados 
puede aumentar su altura y empeorar el costo de búsqueda.
*/

NodoABB* NodoABB::eliminarNodo(int biciId) {
    int idActual = bicicleta.getBiciId();

    if (biciId < idActual) {
        if (izquierdo != nullptr) {
            izquierdo = izquierdo->eliminarNodo(biciId);
        }
    } 
    else if (biciId > idActual) {
        if (derecho != nullptr) {
            derecho = derecho->eliminarNodo(biciId);
        }
    } 
    else {
        // CASO 1: el nodo es una hoja.
        if (izquierdo == nullptr && derecho == nullptr) {
            delete this;
            return nullptr;
        }

        // CASO 2: el nodo tiene solamente un hijo.
        if (izquierdo == nullptr) {
            NodoABB* hijo = derecho;
            delete this;
            return hijo;
        }

        if (derecho == nullptr) {
            NodoABB* hijo = izquierdo;
            delete this;
            return hijo;
        }

        // CASO 3: el nodo tiene dos hijos.
        NodoABB* sucesor = derecho;

        while (sucesor->izquierdo != nullptr) {
            sucesor = sucesor->izquierdo;
        }

        bicicleta = *(sucesor->getBicicleta());

        derecho = derecho->eliminarNodo(
            sucesor->getBicicleta()->getBiciId()
        );
    }

    return this;
}


bool NodoABB::listarPorKilometrosNodo(int kilometrosMinimos) {
    bool encontrado = false;

    if (izquierdo != nullptr) {
        if (izquierdo->listarPorKilometrosNodo(kilometrosMinimos)) {
            encontrado = true;
        }
    }
    
    if (bicicleta.getKilometros() > kilometrosMinimos) {
        cout << "ID: " << bicicleta.getBiciId() << endl;
        cout << " | Estacion: " << bicicleta.getCodigoEstacion() << endl;
        cout << " | Tipo: " << bicicleta.getTipo() << endl; 
        cout << " | Estado: " << bicicleta.getEstado() << endl;
        cout << " | Kilometros: " << bicicleta.getKilometros() << endl;
        cout << endl;

        encontrado = true;
    }

    if (derecho != nullptr) {
        if (derecho->listarPorKilometrosNodo(kilometrosMinimos)) {
            encontrado = true;
        }
    }

    return encontrado;
}

Bicicleta* NodoABB::buscarDisponibleEnEstacionNodo(string codigoEstacion) {
    Bicicleta* biciEncontrada = nullptr;

    if (bicicleta.getCodigoEstacion() == codigoEstacion && bicicleta.getEstado() == "OK" && !bicicleta.getPrestada()) {
        biciEncontrada = &bicicleta;
    }

    if (biciEncontrada == nullptr && izquierdo != nullptr) {
        biciEncontrada = izquierdo->buscarDisponibleEnEstacionNodo(codigoEstacion);
    }

    if (biciEncontrada == nullptr && derecho != nullptr) {
        biciEncontrada = derecho->buscarDisponibleEnEstacionNodo(codigoEstacion);
    }

    return biciEncontrada;
}
