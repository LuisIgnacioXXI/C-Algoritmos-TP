#include <iostream>
#include "estaciones/Estacion.h"
#include "sistemas/Sistema.h"

using namespace std;

int main() {

    // Creamos las estaciones de prueba
    Estacion* estacion1 = new Estacion("PLZ", "PlazaDeMayo", "Monserrat", 30, 12);
    Estacion* estacion2 = new Estacion("ABC", "EstacionABC", "Centro", 20, 5);
    Estacion* estacion3 = new Estacion("CAB", "PrimeraJunta", "Caballito", 25, 4);
    Estacion* estacion4 = new Estacion("PAL", "ParquePalermo", "Palermo", 40, 5);
    Estacion* estacion5 = new Estacion("XYZ", "EstacionXYZ", "Belgrano", 50, 10);

    {
        Sistema sistema;

        sistema.agregarEstacion(estacion1);
        sistema.agregarEstacion(estacion2);
        sistema.agregarEstacion(estacion3);
        sistema.agregarEstacion(estacion4);
        sistema.agregarEstacion(estacion5);

        cout << "===== PRUEBA 1: ORDENAR POR CAPACIDAD =====" << endl;
        sistema.listarEstacionesOrdenadas(1);

        cout << "===== PRUEBA 2: ORDENAR POR BICICLETAS DISPONIBLES =====" << endl;
        sistema.listarEstacionesOrdenadas(2);

        cout << "===== PRUEBA 3: ESTACIONES CON MENOS DEL 20% DE OCUPACION =====" << endl;
        sistema.listarEstacionesBajaOcupacion();
    }

    // La tabla hash ya destruyo sus nodos
    // Liberamos las estaciones creadas dinamicamente
    delete estacion1;
    delete estacion2;
    delete estacion3;
    delete estacion4;
    delete estacion5;

    cout << "===== FIN DE LAS PRUEBAS =====" << endl;

    return 0;
}
