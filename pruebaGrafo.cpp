#include <iostream>
#include "estructuras/Grafo.h"

using namespace std;

int main() {

    Grafo grafo;

    cout << "===== PRUEBA 1: AGREGAR ESTACIONES =====" << endl;

    grafo.agregarEstacion("PLZ");
    grafo.agregarEstacion("CAB");
    grafo.agregarEstacion("PAL");
    grafo.agregarEstacion("ABC");
    grafo.agregarEstacion("XYZ");

    cout << endl;

    cout << "Intentar agregar una estacion duplicada:" << endl;
    grafo.agregarEstacion("PLZ");

    cout << endl;
    cout << "===== PRUEBA 2: AGREGAR CONEXIONES =====" << endl;

    grafo.agregarConexion("PLZ", "CAB");
    grafo.agregarConexion("PLZ", "PAL");
    grafo.agregarConexion("CAB", "ABC");
    grafo.agregarConexion("PAL", "ABC");

    cout << endl;

    cout << "Intentar agregar una conexion repetida:" << endl;
    grafo.agregarConexion("PLZ", "CAB");

    cout << endl;

    cout << "Intentar conectar una estacion consigo misma:" << endl;
    grafo.agregarConexion("PLZ", "PLZ");

    cout << endl;

    cout << "Intentar conectar estaciones inexistentes:" << endl;
    grafo.agregarConexion("PLZ", "ZZZ");

    cout << endl;
    cout << "===== PRUEBA 3: MOSTRAR CONEXIONES =====" << endl;

    grafo.mostrarConexiones();

    cout << endl;
    cout << "===== PRUEBA 4: CAMINO MAS CORTO =====" << endl;

    grafo.caminoMasCorto("PLZ", "ABC");

    cout << endl;
    cout << "===== PRUEBA 5: CAMINO SIN CONEXION =====" << endl;

    grafo.caminoMasCorto("PLZ", "XYZ");

    cout << endl;
    cout << "===== PRUEBA 6: ESTACION INEXISTENTE =====" << endl;

    grafo.caminoMasCorto("PLZ", "ZZZ");

    cout << endl;
    cout << "===== PRUEBA 7: ELIMINAR ESTACION =====" << endl;

    grafo.eliminarEstacion("CAB");

    cout << endl;
    cout << "Conexiones despues de eliminar CAB:" << endl;

    grafo.mostrarConexiones();

    cout << endl;
    cout << "Volver a buscar un camino entre PLZ y ABC:" << endl;

    grafo.caminoMasCorto("PLZ", "ABC");

    cout << endl;
    cout << "===== PRUEBA 8: ELIMINAR ESTACION INEXISTENTE =====" << endl;

    grafo.eliminarEstacion("ZZZ");

    cout << endl;

    return 0;
}




