#ifndef VIAJE_H
#define VIAJE_H

#include <string>
using namespace std;

class Viaje {
private:
    int viajeId;
    int biciId;
    int dniUsuario;
    string estacionOrigen;
    string estacionDestino;
    int fecha;
    int duracionMin;

public:
    Viaje(); // Constructor por defecto necesario para arreglos dinámicos (new Viaje[N])

    Viaje(int viajeId, int biciId, int dniUsuario, string estacionOrigen, string estacionDestino, int fecha, int duracionMin);

    int getViajeId();
    int getBiciId();
    int getDniUsuario();
    string getEstacionOrigen();
    string getEstacionDestino();
    int getFecha();
    int getDuracionMin();
    
};

#endif

