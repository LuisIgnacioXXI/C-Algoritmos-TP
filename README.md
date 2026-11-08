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



## Análisis de complejidad — Sección B

Para el análisis se utilizan las siguientes variables:

- `n`: cantidad de viajes registrados.
- `B`: cantidad de bicicletas almacenadas en el ABB.
- `h`: altura del ABB.
- `Q`: cantidad de usuarios en la cola de espera.
- `S`: cantidad de estaciones.
- `H`: cantidad de bicicletas en el heap del taller.

### B1. Cantidad de viajes por estación y rango de fechas

**Complejidad temporal: O(n).**

Se recorre el vector de viajes una sola vez y se comprueba si cada viaje corresponde a la estación y al rango de fechas solicitados. Se utiliza un vector porque permite almacenar los viajes y recorrerlos secuencialmente para realizar las consultas.

### B2. Viajes de un usuario y total de minutos pedaleados

**Complejidad temporal: O(n).**

Se recorren todos los viajes y se compara el DNI de cada uno con el DNI solicitado. Cuando coinciden, se muestran sus datos y se acumula la duración. Se utiliza un vector porque permite recorrer los registros secuencialmente y calcular el total en una sola pasada.

### B3. Bicicletas que superan un kilometraje determinado

**Complejidad temporal: O(B).**

Se recorre el árbol para comprobar los kilómetros de cada bicicleta. Se utiliza un ABB porque permite almacenar las bicicletas ordenadas por `bici_id`, buscarlas por identificador y listarlas ordenadamente. Como el árbol no está ordenado por kilometraje, es necesario recorrer todos sus nodos para aplicar este filtro.

### B4. Cola de espera por estación

**Complejidad temporal:**

- Buscar la estación en la tabla hash: O(1) promedio.
- Buscar una bicicleta disponible en el ABB: O(B) en el peor caso.
- Encolar un usuario: O(1) amortizado, sin considerar el costo ocasional de redimensionamiento del vector.
- Desencolar un usuario: O(Q), porque la implementación utiliza un vector y elimina el elemento de la posición cero.
- Buscar la bicicleta devuelta en el ABB: O(h) en el peor caso.

Se utiliza una tabla hash para localizar las estaciones por código y un ABB para almacenar y buscar las bicicletas por ID. La cola permite respetar el orden de llegada de los usuarios (FIFO), de manera que el primero en esperar sea el primero en recibir una bicicleta.

### B5. Cola de prioridad del taller de reparaciones

**Complejidad temporal:**

- Insertar una bicicleta: O(log H).
- Extraer la bicicleta más urgente: O(log H).
- Consultar si el heap está vacío: O(1).

Se utiliza un heap mínimo porque permite mantener en la raíz la bicicleta con menor número de prioridad, es decir, la más urgente. La inserción y la extracción reorganizan el heap mediante intercambios entre nodos, sin necesidad de recorrer todas las bicicletas para encontrar la más urgente.








### Análisis: Altura del ABB y costo de búsqueda — Seccion C

Si las bicicletas se cargan ordenadas por ID creciente, el árbol binario de búsqueda queda **degenerado**, ya que cada nuevo ID es mayor que los anteriores y se inserta como hijo derecho del último nodo.

Por ejemplo, si insertamos las bicicletas con los ID `10, 20, 30, 40 y 50`, obtenemos un árbol de 5 niveles:

```text
10
  \
   20
     \
      30
        \
         40
           \
            50
```

En este caso, la altura es de **5 niveles**. Para buscar la bicicleta con ID `50`, es necesario recorrer los cinco nodos. Por lo tanto, la búsqueda puede tener un costo de **O(n)**, donde `n` es la cantidad de nodos del árbol.

En cambio, si insertamos los mismos ID en un orden que distribuya mejor los nodos, por ejemplo `30, 20, 40, 10 y 50`, obtenemos un árbol de 3 niveles:

```text
       30
      /  \
    20    40
   /        \
  10         50
```

En este caso, la altura es de **3 niveles** y buscar la bicicleta con ID `50` requiere visitar solamente tres nodos.

El método `insertarNodo()` es el mismo en ambos casos: la diferencia está en el orden de inserción. Como nuestro árbol no se reequilibra automáticamente, insertar los datos ordenados puede aumentar su altura y empeorar el costo de búsqueda