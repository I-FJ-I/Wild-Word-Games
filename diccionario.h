#ifndef _DICC
#define _DICC

#include "avl.h"
#include "hash.h"

class Diccionario {
    TablaHash tabla;
    TablaHashJuana juana;
    Arbol arbol;
    public:
        Diccionario() {};
        void vaciar();
        void insertar(string palabra);
        bool consultar(string palabra) {return tabla.consultar(palabra);}
        int tamano() {return arbol.get_tamano();}
        string juego1(string palabra) {return juana.obtener(palabra);}
        void juego2(string palabra1, string palabra2, list<string>& resultado) {
            arbol.saco_palabras(arbol.raiz, palabra1, palabra2, resultado);
        }
};

#endif