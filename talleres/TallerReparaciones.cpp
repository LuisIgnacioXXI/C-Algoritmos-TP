#include "TallerReparaciones.h"
#include <iostream>
#include <stdexcept>

using namespace std;

void TallerReparaciones::insertarBicicleta(Bicicleta bicicleta) {
    int prioridad;
    
    if (bicicleta.getEstado() != "Averiada") {
        throw runtime_error("No se puede ingresar una bicicleta que no esta averiada");
    }

    if (bicicleta.getTipo() == "Electrica") {
        prioridad = 1;
        cout << "Bicicleta electrica: prioridad 1 asignada automaticamente" << endl;
    }
    else {
        cout << "Ingrese la prioridad de la bicicleta mecanica (1 a 3): ";
        cin >> prioridad;

        while (prioridad < 1 || prioridad > 3) {
            cout << "Prioridad invalida Ingrese 1, 2 o 3: ";
            cin >> prioridad;
        }
    }
    bicicleta.setPrioridad(prioridad);
    bicicletas.encolar(bicicleta);
}


Bicicleta TallerReparaciones::extraerMasUrgente() {
    return bicicletas.extraerPrimero();
}


bool TallerReparaciones::vacio() {
    return bicicletas.vacia();
}
