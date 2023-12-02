#include "diccionario.h"

void Diccionario::vaciar() {
    arbol.vaciar();
    tabla.vaciar();
    juana.vaciar();
};

void Diccionario::insertar(string palabra) {
    arbol.insertar(arbol.raiz, palabra);
    tabla.insertar(palabra);
    juana.insertar(palabra);
};