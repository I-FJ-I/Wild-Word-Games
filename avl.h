#ifndef _AVL
#define _AVL

#include <iostream>
#include <list>

using namespace std;

class Nodo {
    friend class Arbol;
    Nodo * hijo_izquierdo;
    Nodo * hijo_derecho;
    string elemento;
    int altura;
    public:
        Nodo(string elemento);
        ~Nodo();
};

class Arbol {
    int numero_palabras;
    Nodo * RSI(Nodo * nodo);
    Nodo * RSD(Nodo * nodo);
    Nodo * RDI(Nodo * nodo);
    Nodo * RDD(Nodo * nodo);
    int altura(Nodo * nodo);
    void actualizar_altura(Nodo * nodo);
    public:
        Arbol();
        ~Arbol();
        Nodo * raiz;
        void insertar(Nodo * &nodo, string palabra);
        bool buscar(string palabra);
        void vaciar();
        int get_tamano() {return numero_palabras;}
        void saco_palabras(Nodo * nodo, string palabra1, string palabra2, list<string> &resultado);
};

#endif