#include <string>

using namespace std;

class Estacion {
    private:
        string codigo;
        string nombre;
        string barrio;
        int capacidadAnclajes;
        int cantidadBicisDisponibles;

    public:
        Estacion(string codigo, string nombre, string barrio, int capacidadAnclajes, int bicisDisponibles);

        string getCodigo();
        string getNombre();
        string getBarrio();
        int getCapacidadAnclajes();
        int getCantidadBicisDisponibles();

        void mostrarInformacion();
};



