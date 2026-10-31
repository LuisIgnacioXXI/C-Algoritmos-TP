#include <iostream>
#include <stdexcept>

#include "estaciones/Estacion.h"
#include "sistemas/Sistema.h"
#include "talleres/TallerReparaciones.h"

using namespace std;

int main() {

    // ==================================================
    // CREACION DE ESTACIONES DE PRUEBA
    // ==================================================

    Estacion* estacion1 = new Estacion("PLZ", "PlazaDeMayo", "Monserrat", 30, 12);
    Estacion* estacion2 = new Estacion("ABC", "EstacionABC", "Centro", 20, 5);
    Estacion* estacion3 = new Estacion("CAB", "PrimeraJunta", "Caballito", 25, 4);
    Estacion* estacion4 = new Estacion("PAL", "ParquePalermo", "Palermo", 40, 5);
    Estacion* estacion5 = new Estacion("XYZ", "EstacionXYZ", "Belgrano", 50, 10);

    // Estacion especial para probar la cola de espera.
    Estacion* estacionEspera = new Estacion("ESP", "EstacionEspera", "Centro", 10, 0);

    {
        Sistema sistema;

        sistema.agregarEstacion(estacion1);
        sistema.agregarEstacion(estacion2);
        sistema.agregarEstacion(estacion3);
        sistema.agregarEstacion(estacion4);
        sistema.agregarEstacion(estacion5);
        sistema.agregarEstacion(estacionEspera);


        // ==================================================
        // PRUEBAS DE GESTION DE ESTACIONES
        // ==================================================

        cout << "===== PRUEBA 1: ORDENAR POR CAPACIDAD =====" << endl;
        sistema.listarEstacionesOrdenadas(1);

        cout << "===== PRUEBA 2: ORDENAR POR BICICLETAS DISPONIBLES =====" << endl;
        sistema.listarEstacionesOrdenadas(2);

        cout << "===== PRUEBA 3: ESTACIONES CON MENOS DEL 20% DE OCUPACION =====" << endl;
        sistema.listarEstacionesBajaOcupacion();


        // ==================================================
        // PUNTO B1: CONTAR VIAJES POR ESTACION Y FECHA
        // ==================================================

        cout << "===== PRUEBA 4: CONTAR VIAJES POR ESTACION Y FECHA =====" << endl;

        sistema.agregarViaje(Viaje(9001, 101, 12345678, "PLZ", "PAL", 20261001, 35));
        sistema.agregarViaje(Viaje(9002, 102, 87654321, "CAB", "PLZ", 20261002, 20));
        sistema.agregarViaje(Viaje(9003, 103, 12345678, "PLZ", "CAB", 20261003, 45));
        sistema.agregarViaje(Viaje(9004, 104, 12345678, "PAL", "PLZ", 20261005, 30));

        int cantidad = sistema.contarViajesPorOrigenYFecha("PLZ", 20261001, 20261003);

        cout << "Cantidad de viajes desde PLZ entre las fechas indicadas: " << cantidad << endl;


        // ==================================================
        // PUNTO B2: CONSULTAR VIAJES POR DNI
        // ==================================================

        cout << "===== PRUEBA 5: VIAJES POR DNI Y TOTAL DE MINUTOS =====" << endl;

        sistema.mostrarViajesPorDniUsuario(12345678);

        cout << "--- DNI SIN VIAJES ---" << endl;
        sistema.mostrarViajesPorDniUsuario(11111111);


        // ==================================================
        // PUNTO B3: BICICLETAS PARA REVISION POR KILOMETRAJE
        // ==================================================

        cout << "===== PRUEBA 6: BICICLETAS PARA REVISION =====" << endl;

        sistema.agregarBicicleta(Bicicleta(101, "PLZ", "Electrica", "OK", 1200));
        sistema.agregarBicicleta(Bicicleta(102, "CAB", "Mecanica", "OK", 2500));
        sistema.agregarBicicleta(Bicicleta(103, "PAL", "Electrica", "Averiada", 5000));
        sistema.agregarBicicleta(Bicicleta(104, "PLZ", "Mecanica", "OK", 3000));
        sistema.agregarBicicleta(Bicicleta(105, "CAB", "Mecanica", "Averiada", 800));

        cout << "--- Bicicletas con mas de 2000 km ---" << endl;
        sistema.listarBicicletasParaRevision(2000);

        cout << "--- Bicicletas con mas de 5000 km ---" << endl;
        sistema.listarBicicletasParaRevision(5000);

        cout << "--- BICICLETAS CON MAS DE 10000 KM ---" << endl;
        sistema.listarBicicletasParaRevision(10000);


        // ==================================================
        // PUNTO B4: COLA DE ESPERA POR ESTACION
        // ==================================================

        cout << "===== PRUEBA 7: COLA DE ESPERA FIFO =====" << endl;

        Bicicleta bici1(201, "ESP", "Mecanica", "OK", 500);
        Bicicleta bici2(202, "ESP", "Mecanica", "OK", 700);
        Bicicleta bici3(203, "ESP", "Electrica", "OK", 300);

        bici1.setPrestada(true);
        bici2.setPrestada(true);
        bici3.setPrestada(true);

        sistema.agregarBicicleta(bici1);
        sistema.agregarBicicleta(bici2);
        sistema.agregarBicicleta(bici3);

        cout << "--- SOLICITUDES ---" << endl;

        sistema.solicitarBicicleta("ESP", 11111111);
        sistema.solicitarBicicleta("ESP", 22222222);
        sistema.solicitarBicicleta("ESP", 33333333);

        cout << "--- DEVOLUCIONES ---" << endl;

        sistema.devolverBicicleta("ESP", 201);
        sistema.devolverBicicleta("ESP", 202);
        sistema.devolverBicicleta("ESP", 203);

        cout << "--- ESTADO FINAL DE LA ESTACION ---" << endl;
        estacionEspera->mostrarInformacion();


        // ==================================================
        // PUNTO B5: HEAP MINIMO DEL TALLER DE REPARACIONES
        // ==================================================

        cout << "===== PRUEBA 8: TALLER DE REPARACIONES =====" << endl;

        TallerReparaciones taller;

        cout << "--- PRUEBA DE VALIDACION ---" << endl;

        try {
            Bicicleta biciOK(301, "PLZ", "Mecanica", "OK", 500);
            taller.insertarBicicleta(biciOK);
        }
        catch (runtime_error& e) {
            cout << "Error esperado: " << e.what() << endl;
        }

        cout << "--- INGRESO DE BICICLETAS ---" << endl;

        Bicicleta bici4(302, "PLZ", "Mecanica", "Averiada", 1000);
        Bicicleta bici5(303, "CAB", "Mecanica", "Averiada", 1500);
        Bicicleta bici6(304, "PAL", "Mecanica", "Averiada", 2000);

        taller.insertarBicicleta(bici4);
        taller.insertarBicicleta(bici5);
        taller.insertarBicicleta(bici6);

        // La bicicleta electrica recibe prioridad 1 automaticamente.
        Bicicleta biciElectrica(305, "PLZ", "Electrica", "Averiada", 800);
        taller.insertarBicicleta(biciElectrica);

        cout << "--- EXTRACCION POR PRIORIDAD ---" << endl;

        while (!taller.vacio()) {
            Bicicleta bicicleta = taller.extraerMasUrgente();

            cout << "Bicicleta: " << bicicleta.getBiciId() << " | Prioridad: " << bicicleta.getPrioridad() << endl;
        }

        cout << "¿El taller quedo vacio? " << (taller.vacio() ? "Si" : "No") << endl;
    }

    // ==================================================
    // LIBERACION DE MEMORIA
    // ==================================================

    // La tabla hash ya destruyo sus nodos.
    // Liberamos las estaciones creadas dinamicamente.

    delete estacion1;
    delete estacion2;
    delete estacion3;
    delete estacion4;
    delete estacion5;
    delete estacionEspera;

    cout << "===== FIN DE LAS PRUEBAS =====" << endl;

    return 0;
}
