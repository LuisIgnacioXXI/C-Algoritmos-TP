#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#include "estructuras/TablaHashEstaciones.h"
#include "estructuras/Grafo.h"
#include "estructuras/Vector.h"
#include "estructuras/ColaPrioridad.h"

#include "estaciones/Estacion.h"
#include "viajes/Viaje.h"
#include "bicicletas/Bicicleta.h"
#include "Sistemas/Sistema.h"
#include "talleres/TallerReparaciones.h"


using namespace std;


bool cargarEstaciones(TablaHashEstaciones& tabla, const string& nombreArchivo) {

    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cout << "Error: no se pudo abrir " << nombreArchivo << endl;
        return false;
    }

    string codigo, nombre, barrio;
    int capacidadAnclajes, bicisDisponibles;

    while (archivo >> codigo >> nombre >> barrio >> capacidadAnclajes >> bicisDisponibles) {
        Estacion* estacion = new Estacion(
            codigo, nombre, barrio,
            capacidadAnclajes, bicisDisponibles
        );

        if (tabla.agregar(estacion)) {
        } else {
            cout << "No se pudo agregar la estacion " << codigo << endl;
            delete estacion;
        }
    }

    return true;
}

bool cargarGrafo(Grafo& grafo, TablaHashEstaciones& tabla, const string& nombreArchivo) {

    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cout << "Error: no se pudo abrir " << nombreArchivo << endl;
        return false;
    }

    string origen, destino;

    while (archivo >> origen >> destino) {
        if (tabla.buscar(origen) == nullptr) {
            cout << "Error: no existe la estacion " << origen << endl;
            continue;
        }
        if (tabla.buscar(destino) == nullptr) {
            cout << "Error: no existe la estacion " << destino << endl;
            continue;
        }
        if (!grafo.agregarConexion(origen, destino)) {
            cout << "No se pudo agregar la conexion " << origen << " - " << destino << endl;
        }
    }

    return true;
}

int main() {
    
    
    TablaHashEstaciones tabla(11);
    Grafo grafo;

    if (!cargarEstaciones(tabla, "estaciones.txt")) {
        return 1;
    }

    for (int i = 0; i < tabla.getCantidad(); i++) {
        Estacion* estacion = tabla.obtenerEstacionPorIndice(i);

        if (estacion != nullptr) {
            if (!grafo.agregarEstacion(estacion->getCodigo())) {
                cout << "Error al agregar la estacion " << estacion->getCodigo() << " al grafo." << endl;
                return 1;
            }
        }
    }

    if (!cargarGrafo(grafo, tabla, "ciclovias.txt")) {
        return 1;
    }

    cout << "Cantidad de estaciones cargadas: " << tabla.getCantidad() << endl;

    cout << "\nTodas las estaciones:" << endl;
    tabla.mostrarTodas();

    cout << "\nColisiones: " << tabla.getColisiones() << endl;
    cout << "Factor de carga: " << tabla.factorCarga() << endl;

    cout << "\nConexiones del grafo:" << endl;
    grafo.mostrarConexiones();

    cout << "\nPrueba de camino mas corto:" << endl;
    grafo.caminoMasCorto("PLZ", "PAL");

    cout << "\nPrueba de camino existente:" << endl;
    grafo.caminoMasCorto("PLZ", "PAL");

    cout << "\nPrueba de camino inexistente:" << endl;
    grafo.caminoMasCorto("PLZ", "AIS");

    cout << "\n=== BUSQUEDA DE ESTACION ===" << endl;
    Estacion* encontrada = tabla.buscar("PLZ");

    if (encontrada != nullptr) {
        encontrada->mostrarInformacion();
    } 
    else {
        cout << "Estacion no encontrada." << endl;
    }

    cout << "\n=== ORDENADAS POR CAPACIDAD ===" << endl;
    tabla.listarPorCapacidad();

    cout << "\n=== ORDENADAS POR BICICLETAS ===" << endl;
    tabla.listarPorBicisDisponibles();

    cout << "\n=== BAJA OCUPACION ===" << endl;
    tabla.listarBajaOcupacion();

    /*cout << "\n=== PRUEBA DE ELIMINACION INTEGRADA ===" << endl;

    if (tabla.eliminar("CAB")) {
        cout << "Estacion CAB eliminada de la tabla hash." << endl;
        grafo.eliminarEstacion("CAB");
        cout << "Estacion CAB eliminada del grafo." << endl;
    } else {
        cout << "No se encontro la estacion CAB." << endl;
    }

    cout << "\nEstaciones restantes:" << endl;
    tabla.mostrarTodas();

    cout << "\nConexiones restantes:" << endl;
    grafo.mostrarConexiones();

    cout << "\nPrueba de recorrido despues de eliminar CAB:" << endl;
    grafo.caminoMasCorto("PLZ", "PAL");*/

    return 0;
}


