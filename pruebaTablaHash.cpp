#include <iostream>
#include "estaciones/Estacion.h"
#include "estructuras/TablaHashEstaciones.h"

using namespace std;

int main() {

    // Creamos tres estaciones con codigos diferentes
    // Producen el mismo indice hash
    Estacion* estacion1 = new Estacion("ABC", "EstacionABC", "Centro", 20, 5);
    Estacion* estacion2 = new Estacion("ACB", "EstacionACB", "Norte", 25, 8);
    Estacion* estacion3 = new Estacion("BAC", "EstacionBAC", "Sur", 30, 10);

    {
        TablaHashEstaciones tabla;

        cout << "===== PRUEBA 1: TABLA VACIA =====" << endl;

        cout << "Cantidad inicial: " << tabla.getCantidad() << endl;

        if (tabla.buscar("XXX") == nullptr) {
            cout << "Correcto: no se encontro XXX" << endl;
        }

        tabla.eliminar("XXX");

        cout << "Cantidad despues de eliminar XXX: " << tabla.getCantidad() << endl;

        cout << "===== PRUEBA 2: INSERTAR ESTACIONES CON COLISIONES =====" << endl;

        tabla.insertar(estacion1);
        tabla.insertar(estacion2);
        tabla.insertar(estacion3);

        cout << "Cantidad esperada: 3" << endl;
        cout << "Cantidad obtenida: " << tabla.getCantidad() << endl;
        cout << "Colisiones registradas: " << tabla.getColisiones() << endl;

        cout << "===== PRUEBA 3: BUSCAR ESTACIONES =====" << endl;

        Estacion* encontrada = tabla.buscar("ABC");

        if (encontrada != nullptr) {
            encontrada->mostrarInformacion();
        }

        encontrada = tabla.buscar("XXX");

        if (encontrada == nullptr) {
            cout << "Correcto: XXX no existe en la tabla" << endl;
        }

        cout << "===== PRUEBA 4: ELIMINAR PRIMER NODO =====" << endl;

        tabla.eliminar("BAC");

        cout << "Cantidad esperada: 2" << endl;
        cout << "Cantidad obtenida: " << tabla.getCantidad() << endl;
        cout << "BAC encontrada: " << (tabla.buscar("BAC") != nullptr) << endl;
        cout << "ACB encontrada: " << (tabla.buscar("ACB") != nullptr) << endl;

        cout << "===== PRUEBA 5: ELIMINAR NODO INTERMEDIO =====" << endl;

        tabla.eliminar("ACB");

        cout << "Cantidad esperada: 1" << endl;
        cout << "Cantidad obtenida: " << tabla.getCantidad() << endl;
        cout << "ACB encontrada: " << (tabla.buscar("ACB") != nullptr) << endl;
        cout << "ABC encontrada: " << (tabla.buscar("ABC") != nullptr) << endl;

        cout << "===== PRUEBA 6: ELIMINAR ULTIMO NODO =====" << endl;

        tabla.eliminar("ABC");

        cout << "Cantidad esperada: 0" << endl;
        cout << "Cantidad obtenida: " << tabla.getCantidad() << endl;
        cout << "Factor de carga: " << tabla.getFactorCarga() << endl;

        cout << "===== PRUEBA 7: ELIMINAR CODIGO INEXISTENTE =====" << endl;

        tabla.eliminar("XXX");

        cout << "Cantidad esperada: 0" << endl;
        cout << "Cantidad obtenida: " << tabla.getCantidad() << endl;
    }

    delete estacion1;
    delete estacion2;
    delete estacion3;

    cout << "===== PRUEBA 8: ELIMINAR UNICO NODO =====" << endl;

    Estacion* estacion4 = new Estacion("XYZ", "EstacionXYZ", "Belgrano", 30, 10);

    {
        TablaHashEstaciones tabla;

        tabla.insertar(estacion4);

        cout << "Cantidad antes de eliminar: " << tabla.getCantidad() << endl;

        tabla.eliminar("XYZ");

        cout << "Cantidad esperada: 0" << endl;
        cout << "Cantidad obtenida: " << tabla.getCantidad() << endl;

        if (tabla.buscar("XYZ") == nullptr) {
            cout << "Correcto: XYZ ya no existe" << endl;
        }
    }

    delete estacion4;

    cout << "===== PRUEBA 9: REUTILIZAR POSICION =====" << endl;

    Estacion* estacion5 = new Estacion("ABC", "EstacionABC", "Centro", 20, 5);
    Estacion* estacion6 = new Estacion("ACB", "EstacionACB", "Norte", 25, 8);

    {
        TablaHashEstaciones tabla;

        tabla.insertar(estacion5);

        cout << "Cantidad despues de insertar ABC: " << tabla.getCantidad() << endl;

        tabla.eliminar("ABC");

        cout << "Cantidad despues de eliminar ABC: " << tabla.getCantidad() << endl;

        tabla.insertar(estacion6);

        cout << "Cantidad esperada: 1" << endl;
        cout << "Cantidad obtenida: " << tabla.getCantidad() << endl;

        if (tabla.buscar("ACB") != nullptr) {
            cout << "Correcto: ACB fue insertada en la posicion liberada" << endl;
        }

        cout << "Colisiones registradas: " << tabla.getColisiones() << endl;
    }

    delete estacion5;
    delete estacion6;

    cout << "===== PRUEBA 10: ESTADISTICAS DE LA TABLA =====" << endl;

    Estacion* estacion7 = new Estacion("PLZ", "PlazaDeMayo", "Monserrat", 30, 12);
    Estacion* estacion8 = new Estacion("ABC", "EstacionABC", "Centro", 20, 5);
    Estacion* estacion9 = new Estacion("CAB", "PrimeraJunta", "Caballito", 25, 4);
    Estacion* estacion10 = new Estacion("PAL", "ParquePalermo", "Palermo", 40, 5);
    Estacion* estacion11 = new Estacion("XYZ", "EstacionXYZ", "Belgrano", 50, 10);

    {
        TablaHashEstaciones tabla;

        tabla.insertar(estacion7);
        tabla.insertar(estacion8);
        tabla.insertar(estacion9);
        tabla.insertar(estacion10);
        tabla.insertar(estacion11);

        cout << "Estaciones insertadas: " << tabla.getCantidad() << endl;
        cout << "Colisiones registradas: " << tabla.getColisiones() << endl;
        cout << "Factor de carga final: " << tabla.getFactorCarga() << endl;
    }

    delete estacion7;
    delete estacion8;
    delete estacion9;
    delete estacion10;
    delete estacion11;

    cout << "===== FIN DE LAS PRUEBAS =====" << endl;

    return 0;
}
