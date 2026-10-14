#include <iostream>
#include "estaciones/Estacion.h"
#include "bicicletas/Bicicleta.h"
#include "viajes/Viaje.h"

using namespace std;

int main() {
    Estacion estacion("PLZ", "PlazaDeMayo", "San Martin", 30, 12);

    cout << endl;
    estacion.mostrarInformacion();
    cout << endl;

    return 0;
}
