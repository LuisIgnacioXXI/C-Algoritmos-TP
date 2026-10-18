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
    bool encontrado = false;
    for (int i = 0; i < bicicletas.getTamanio(); i++) {
        if (bicicletas[i].getKilometros() > kilometrosMinimos) {
            encontrado = true;
            cout << "ID bicicleta: " << bicicletas[i].getBiciId() << endl;
            cout << "Kilometros: " << bicicletas[i].getKilometros() << endl;
            cout << "Estado: " << bicicletas[i].getEstado() << endl;
            cout << "-------------------" << endl;
        }
    }
    if (!encontrado) {
        cout << "No hay bicicletas que superen ese kilometraje" << endl;
    }
}
// Si hay (n) bicicletas almacenadas, el ciclo recorre todas una vez. Por lo tanto la complejidad temporal es O(n)




void Sistema::solicitarBicicleta(string codigoEstacion, int dniUsuario){
    Estacion* estacion = tablaEstaciones.buscar(codigoEstacion);
    validarEstacion(estacion);

    if (estacion->getCantidadBicisDisponibles() == 0) {
        estacion->encolarUsuario(dniUsuario);
        cout << "No hay bicicletas disponibles" << endl;
        cout << "Usuario agregado a la cola de espera" << endl;
        return;
    }

    // Buscamos una bicicleta en buen estado en esa estacion
    for (int i = 0; i < bicicletas.getTamanio(); i++) {
        if (bicicletas[i].getCodigoEstacion() == codigoEstacion && bicicletas[i].getEstado() == "OK") {
            estacion->retirarBicicleta();
            cout << "Bicicleta entregada: " << bicicletas[i].getBiciId() << endl;
            return;
        }
    }
    cout << "No se encontro una bicicleta disponible" << endl;
}

/* Se utiliza una tabla hash para localizar la estación por su código en O(1) promedio. 
Luego, se recorre el vector de bicicletas para encontrar una bicicleta en buen estado perteneciente a esa estación, 
por lo que la complejidad temporal de la operación es O(n) en el peor caso */


void Sistema::devolverBicicleta(string codigoEstacion, int biciId) {
    Estacion* estacion = tablaEstaciones.buscar(codigoEstacion);
    validarEstacion(estacion);
    
    for (int i = 0; i < bicicletas.getTamanio(); i++) {
        if (bicicletas[i].getBiciId() == biciId) {

            bicicletas[i].setCodigoEstacion(codigoEstacion);

            if (estacion->hayUsuariosEsperando()) {
                int dniUsuario = estacion->obtenerUsuarioEnEspera();
                estacion->desencolarUsuario();
                cout << "Bicicleta asignada al usuario DNI: " << dniUsuario << endl;
            } 
            else {
                bicicletas[i].setEstado("OK");
                estacion->agregarBicicletaDisponible();
                cout << "Bicicleta devuelta" << endl;
            }
            return;
        }
    }
    cout << "No se encontro la bicicleta" << endl;
}

/* Se utiliza una tabla hash para localizar la estación y un vector para almacenar las bicicletas. 
La búsqueda de la bicicleta por identificador requiere recorrer el vector, O(n) 
Además, si hay usuarios esperando, la operación desencola al primero; como la cola actual utiliza un vector y desplaza los elementos
 al eliminar el primero puede llegar a O(n+q) */

void Sistema::validarEstacion(Estacion* estacion) {
    if (estacion == nullptr) {
        throw runtime_error("La estacion no existe");
    }
}

