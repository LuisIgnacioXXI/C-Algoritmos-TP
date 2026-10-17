#pragma once

#include <string>

using namespace std;

class Estacion {
    private:
        std::string codigo;
        std::string nombre;
        std::string barrio;
        int capacidadAnclajes;
        int cantidadBicisDisponibles;

    public:
        Estacion(string codigo, string nombre, string barrio, int capacidadAnclajes, int bicisDisponibles);

        std::string getCodigo();
        std::string getNombre();
        std::string getBarrio();
        int getCapacidadAnclajes();
        int getCantidadBicisDisponibles();

        void mostrarInformacion();
        
};



