
#ifndef ESTACION_H
#define ESTACION_H

#include <string>
#include "../estructuras/Cola.h"

using namespace std;

class Estacion {
    private:
        string codigo;
        string nombre;
        string barrio;
        int capacidadAnclajes;
        int cantidadBicisDisponibles;
        Cola<int> colaEspera;

    public:
        Estacion(string codigo, string nombre, string barrio, int capacidadAnclajes, int bicisDisponibles);

        string getCodigo();
        string getNombre();
        string getBarrio();
        int getCapacidadAnclajes();
        int getCantidadBicisDisponibles();
        void mostrarInformacion();

        void encolarUsuario(int dniUsuario);
        void desencolarUsuario();
        int obtenerUsuarioEnEspera();
        bool hayUsuariosEsperando();
        void retirarBicicleta();
        void agregarBicicletaDisponible();
};

#endif

