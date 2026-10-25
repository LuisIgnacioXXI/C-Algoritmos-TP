#ifndef BICICLETA_H
#define BICICLETA_H

#include <string>
using namespace std;

class Bicicleta {
private:
    int biciId;
    string codigoEstacion;
    string tipo;
    string estado;
    int kilometros;

    int prioridad;

    bool prestada;

public:
    Bicicleta();
    Bicicleta(int biciId, string codigoEstacion, string tipo, string estado, int kilometros);
    
    int getBiciId();
    string getCodigoEstacion();
    string getTipo();
    string getEstado();
    int getKilometros();

    int getPrioridad();

    void setEstado(string nuevoEstado);
    void setCodigoEstacion(string nuevoCodigo);
    void setPrioridad(int nuevaPrioridad);

    bool getPrestada();
    void setPrestada(bool prestada);
};

#endif
