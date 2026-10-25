#include "Sistema.h"
#include "iostream"
#include <stdexcept>

using namespace std;

int Sistema::contarViajesPorOrigenYFecha(string codigoEstacion, int fechaDesde, int fechaHasta){
    int contador = 0;
    for (int i = 0; i < viajes.getTamanio(); i++) {
        if (viajes[i].getEstacionOrigen() == codigoEstacion &&
            viajes[i].getFecha() >= fechaDesde &&
            viajes[i].getFecha() <= fechaHasta) {
            contador++;
        }
    }
    return contador;
}
// La complejidad es O(n), (n) es la cantidad de viajes: revisamos cada viaje una vez




void Sistema::mostrarViajesPorDniUsuario(int dniUsuario){
    int totalMinutos = 0;
    bool encontrado = false;
    for (int i = 0; i < viajes.getTamanio(); i++) {
        if (viajes[i].getDniUsuario() == dniUsuario) {
            encontrado = true;
            cout << "ID del viaje: " << viajes[i].getViajeId() << endl;
            cout << "Estacion de origen: " << viajes[i].getEstacionOrigen() << endl;
            cout << "Estacion de destino: " << viajes[i].getEstacionDestino() << endl;
            cout << "Duracion: " << viajes[i].getDuracionMin() << " minutos" << endl;
            cout << "-------------------" << endl;
            totalMinutos += viajes[i].getDuracionMin();
        }
    }
    if (encontrado) {
        cout << "Total de minutos pedaleados: " << totalMinutos << endl;
    } 
    else {
        cout << "No se encontraron viajes para ese DNI" << endl;
    }
}
/* Si hay (n) viajes registrados:
  - Recorremos los (n) elementos una sola vez
  - En cada iteración realizamos una comparación del DNI
  - Cuando coincide, mostramos datos y sumamos la duración, operaciones de costo constante
    Por lo tanto, la complejidad temporal es O(n). La razón para usar el vector es que necesitamos almacenar los viajes y recorrerlos secuencialmente
*/





void Sistema::listarBicicletasParaRevision(int kilometrosMinimos){
    arbolBicicletas.listarPorKilometros(kilometrosMinimos);
}

// En el peor caso, se visitan las (n) bicicletas, de modo que la complejidad es O(n) 
// se utiliza un ABB porque permite almacenar las bicicletas ordenadas por ID, buscarlas y listarlas en orden. 
// Para filtrar por kilometraje, sin embargo, hay que recorrer todos sus nodos




void Sistema::solicitarBicicleta(string codigoEstacion, int dniUsuario) {
    Estacion* estacion = tablaEstaciones.buscar(codigoEstacion);
    validarEstacion(estacion);

    if (estacion->hayUsuariosEsperando() || estacion->getCantidadBicisDisponibles() == 0) {
        estacion->encolarUsuario(dniUsuario);
        cout << "Hay usuarios esperando, " << "se agrego el DNI " << dniUsuario << " a la cola" << endl;
        return;
    }

    Bicicleta* bicicleta = arbolBicicletas.buscarDisponibleEnEstacion(codigoEstacion);

    if (bicicleta == nullptr) {
        estacion->encolarUsuario(dniUsuario);
        cout << "No hay bicicletas disponibles, " << "se agrego el DNI " << dniUsuario << " a la cola de espera" << endl;
        return;
    }

    bicicleta->setPrestada(true);
    estacion->retirarBicicleta();

    cout << "Bicicleta entregada: " << bicicleta->getBiciId() << endl;
}

/* 
   O(B) promedio para la tabla hash
   la tabla hash permite encontrar rápidamente la estación por su código, mientras que el ABB
   centraliza todas las bicicletas y permite buscarlas por ID. Como el árbol no está ordenado
   por estación ni por disponibilidad, encontrar una bicicleta apta para retirar puede requerir
   recorrer todos sus nodos
*/

void Sistema::devolverBicicleta(string codigoEstacion, int biciId) {
    Estacion* estacion = tablaEstaciones.buscar(codigoEstacion);
    validarEstacion(estacion);

    Bicicleta* bicicleta = arbolBicicletas.buscar(biciId);
    validarBicicleta(bicicleta);

    if (!bicicleta->getPrestada()) {
        cout << "La bicicleta no figura como prestada" << endl;
        return;
    }

    bicicleta->setCodigoEstacion(codigoEstacion);

    if (bicicleta->getEstado() == "Averiada") {
        cout << "La bicicleta fue devuelta, pero esta averiada" << endl;
        return;
    }

    if (estacion->hayUsuariosEsperando()) {
        int dniUsuario = estacion->obtenerUsuarioEnEspera();
        estacion->desencolarUsuario();

        bicicleta->setPrestada(true);
        cout << "Bicicleta " << biciId << " asignada al usuario DNI " << dniUsuario << endl;
    } 
    else {
        bicicleta->setPrestada(false);
        estacion->agregarBicicletaDisponible();
        cout << "Bicicleta " << biciId << " devuelta y disponible en la estacion " << codigoEstacion << endl;
    }
}

/*
  Complejidad temporal: O(h+Q) en el peor caso, suponiendo búsqueda promedio O(1) en la tabla hash 
  el ABB permite localizar la bicicleta devuelta por su ID, y la tabla hash permite localizar
  la estación de destino. La cola respeta el orden de llegada de los usuarios, 
  aunque su implementación actual con un vector puede hacer que desencolar cueste O(Q)
*/

void Sistema::validarEstacion(Estacion* estacion) {
    if (estacion == nullptr) {
        throw runtime_error("No se encontró la estacion");
    }
}

void Sistema::validarBicicleta(Bicicleta* bicicleta){
    if (bicicleta == nullptr){
        throw runtime_error("No se encontró la bicicleta");
    }
}
