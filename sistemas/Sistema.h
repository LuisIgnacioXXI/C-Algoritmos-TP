#ifndef SISTEMA_H
#define SISTEMA_H

#include "../viajes/Viaje.h"
#include "../bicicletas/Bicicleta.h"
#include "../estructuras/Vector.h"
#include "../estructuras/TablaHashEstaciones.h"
#include "../estructuras/Grafo.h"
#include "../estructuras/ArbolBicicletas.h"
#include "../talleres/TallerReparaciones.h"

class Sistema {
    private:
        Vector<Viaje> viajes;
        ArbolBicicletas arbolBicicletas;
        TallerReparaciones taller;
        TablaHashEstaciones tablaEstaciones;
        Grafo grafo;

    public:
        Sistema();

        void mostrarEstacion(string codigo);
        void agregarEstacion(Estacion* estacion);
        void eliminarEstacion(string codigo);




        // Ejercicio B
        int contarViajesPorOrigenYFecha(string codigoEstacion, int fechaDesde, int fechaHasta);
        void mostrarViajesPorDniUsuario(int dniUsuario);
        void listarBicicletasParaRevision(int kilometrosMinimos);

        void solicitarBicicleta(string codigoEstacion, int dniUsuario);
        void devolverBicicleta(string codigoEstacion, int biciId);
        void validarEstacion(Estacion* estacion);
        void validarBicicleta(Bicicleta* bicicleta);
};

#endif

