#ifndef TALLER_REPARACIONES_H
#define TALLER_REPARACIONES_H

#include "../estructuras/ColaPrioridad.h"
#include "../bicicletas/Bicicleta.h"

class TallerReparaciones {
    private:
        ColaPrioridad<Bicicleta> bicicletas;

    public:
        void insertarBicicleta(Bicicleta bicicleta);
        Bicicleta extraerMasUrgente();
        bool vacio();
};

#endif

