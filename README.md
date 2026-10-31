### Tabla hash de estaciones

Las estaciones se indexan por su código mediante una tabla hash de tamaño 11. La función hash suma los valores ASCII de los caracteres del código y calcula el módulo 11.

Para resolver las colisiones se utiliza **encadenamiento**, almacenando las estaciones que comparten una misma posición mediante una lista enlazada.

Con los 5 datos de prueba (`PLZ`, `ABC`, `CAB`, `PAL` y `XYZ`), se registró **1 colisión** y se obtuvo un factor de carga final de **0,4545** (5/11).

Instrucciones para compilar:

### Pruebas de tabla hash:
g++ -std=c++17 -Wall -Wextra pruebaTablaHash.cpp estaciones/Estacion.cpp estructuras/TablaHashEstaciones.cpp estructuras/NodoHash.cpp -o pruebaTablaHash.exe

.\pruebaTablaHash.exe


### Pruebas de Sistema:
g++ -std=c++17 -Wall -Wextra pruebaSistema.cpp sistemas/Sistema.cpp estaciones/Estacion.cpp estructuras/TablaHashEstaciones.cpp estructuras/NodoHash.cpp estructuras/ArbolBicicletas.cpp estructuras/NodoABB.cpp bicicletas/Bicicleta.cpp viajes/Viaje.cpp talleres/TallerReparaciones.cpp -o pruebaSistema.exe

.\pruebaSistema.exe