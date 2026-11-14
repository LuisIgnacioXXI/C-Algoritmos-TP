#include <iostream>
#include "bicicletas/Bicicleta.h"
#include "estructuras/ArbolBicicletas.h"

using namespace std;

int main() {
    ArbolBicicletas arbol;

    // Crear bicicletas de prueba
    Bicicleta b1(30, "PLZ", "Electrica", "OK", 1200);
    Bicicleta b2(20, "CAB", "Mecanica", "Averiada", 2500);
    Bicicleta b3(40, "PAL", "Electrica", "OK", 1800);
    Bicicleta b4(10, "XYZ", "Mecanica", "OK", 3000);
    Bicicleta b5(50, "ABC", "Mecanica", "Averiada", 500);

    // 1. Insertar bicicletas
    cout << "=== INSERTAR BICICLETAS ===" << endl;

    arbol.insertar(b1);
    arbol.insertar(b2);
    arbol.insertar(b3);
    arbol.insertar(b4);
    arbol.insertar(b5);

    // 2. Mostrar recorrido inorder
    cout << "=== RECORRIDO INORDER ===" << endl;
    arbol.listarInorder();

    // 3. Buscar una bicicleta existente
    cout << "=== BUSCAR BICICLETA 40 ===" << endl;

    Bicicleta* encontrada = arbol.buscar(40);

    if (encontrada != nullptr) {
        encontrada->mostrarInformacion();
    } 
    else {
        cout << "No se encontro la bicicleta" << endl;
    }

    // 4. Buscar una bicicleta inexistente
    cout << "=== BUSCAR BICICLETA 99 ===" << endl;

    Bicicleta* noEncontrada = arbol.buscar(99);

    if (noEncontrada == nullptr) {
        cout << "La bicicleta no existe" << endl;
    }

    // 5. Contar bicicletas averiadas
    cout << "=== CANTIDAD DE BICICLETAS AVERIADAS ===" << endl;
    cout << "Cantidad: " << arbol.contarAveriadas() << endl;

    // 6. Calcular altura
    cout << "=== ALTURA DEL ARBOL ===" << endl;
    cout << "Altura: " << arbol.obtenerAltura() << endl;

    // 7. Listar bicicletas que superan cierto kilometraje
    cout << "=== BICICLETAS CON MAS DE 1500 KM ===" << endl;
    arbol.listarPorKilometros(1500);
  
    // 8. Eliminar una hoja
    cout << "=== ELIMINAR BICICLETA 10 (HOJA) ===" << endl;
    arbol.eliminar(10);
    arbol.listarInorder();

    // 9. Eliminar un nodo con un hijo
    cout << "=== ELIMINAR BICICLETA 40 (UN HIJO) ===" << endl;
    arbol.eliminar(40);
    arbol.listarInorder();

    // 10. Eliminar un nodo con dos hijos
    cout << "=== ELIMINAR BICICLETA 30 (DOS HIJOS) ===" << endl;
    arbol.eliminar(30);
    arbol.listarInorder();

    // 11. Verificar altura después de eliminar
    cout << "=== ALTURA DESPUES DE ELIMINAR ===" << endl;
    cout << "Altura: " << arbol.obtenerAltura() << endl;

    
    // 12. Intentar insertar un ID duplicado
    cout << "=== INSERTAR BICICLETA CON ID DUPLICADO (50) ===" << endl;

    Bicicleta duplicada(50, "PLZ", "Electrica", "OK", 900);
    arbol.insertar(duplicada);

    cout << "Arbol despues de intentar insertar el duplicado:" << endl;
    arbol.listarInorder();

    
    // 13. Eliminar todos los nodos y comprobar que el arbol quede vacio
    cout << "=== ELIMINAR TODOS LOS NODOS ===" << endl;

    arbol.eliminar(20);
    arbol.eliminar(50);

    cout << "El arbol esta vacio? ";

    if (arbol.estaVacio()) {
        cout << "Si" << endl;
    } 
    else {
        cout << "No" << endl;
    }

    cout << "Altura final: " << arbol.obtenerAltura() << endl;




    // El destructor del arbol libera los nodos restantes.
    return 0;
}

