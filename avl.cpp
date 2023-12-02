#include "avl.h"

int max(int a, int b) {
    if (a > b)
        return a;
    return b;
}

Nodo::Nodo(string palabra) {
    hijo_derecho = NULL;
    hijo_izquierdo = NULL;
    elemento = palabra;
    altura = 0;
}

Nodo::~Nodo(){
    delete hijo_derecho;
    delete hijo_izquierdo;
}

Arbol::Arbol(){
    raiz = NULL;
    numero_palabras = 0;
}

Arbol::~Arbol() {delete raiz;}

Nodo * Arbol::RSI(Nodo * nodo) {
    Nodo * nuevo_padre = nodo->hijo_izquierdo;
    nodo->hijo_izquierdo = nuevo_padre->hijo_derecho;
    nuevo_padre->hijo_derecho = nodo;
    actualizar_altura(nodo);
    actualizar_altura(nuevo_padre);
    return nuevo_padre;
}

Nodo * Arbol::RSD(Nodo * nodo) {
    Nodo * nuevo_padre = nodo->hijo_derecho;
    nodo->hijo_derecho = nuevo_padre->hijo_izquierdo;
    nuevo_padre->hijo_izquierdo = nodo;
    actualizar_altura(nodo);
    actualizar_altura(nuevo_padre);
    return nuevo_padre;
}

Nodo * Arbol::RDI(Nodo * nodo) {
    nodo->hijo_izquierdo = RSD(nodo->hijo_izquierdo);
    return RSI(nodo);
}

Nodo * Arbol::RDD(Nodo * nodo) {
    nodo->hijo_derecho = RSI(nodo->hijo_derecho);
    return RSD(nodo);
}

int Arbol::altura(Nodo * nodo) {
    if (nodo != NULL)
        return nodo->altura;
    return -1;
}

void Arbol::actualizar_altura(Nodo * nodo) {
    if (nodo != NULL)
        nodo->altura = 1 + max(altura(nodo->hijo_izquierdo), altura(nodo->hijo_derecho));
}

void Arbol::insertar(Nodo * &nodo, string palabra) {
    if (nodo == NULL) {
        nodo = new Nodo(palabra);
        numero_palabras++;
    }else if (palabra < nodo->elemento) {
        insertar(nodo->hijo_izquierdo, palabra);
        if (altura(nodo->hijo_izquierdo) - altura(nodo->hijo_derecho) > 1) {
            if (palabra < nodo->hijo_izquierdo->elemento)
                nodo = RSI(nodo);
            else
                nodo = RDI(nodo);
        }else 
            actualizar_altura(nodo);
    }else if (palabra > nodo->elemento) {
        insertar(nodo->hijo_derecho, palabra);
        if (altura(nodo->hijo_derecho) - altura(nodo->hijo_izquierdo) > 1) {
            if (palabra > nodo->hijo_derecho->elemento)
                nodo = RSD(nodo);
            else 
                nodo = RDD(nodo);
        }else 
            actualizar_altura(nodo);
    }
}

bool Arbol::buscar(string palabra){
    Nodo * iterador = raiz;
    while (iterador != NULL) {
        if (palabra < iterador->elemento)
            iterador = iterador->hijo_izquierdo;
        else if (palabra > iterador->elemento)
            iterador = iterador->hijo_derecho;
        else
            return true;
    }
    return false;
}

void Arbol::vaciar(){
    Nodo * antigua_raiz = raiz;
    raiz = NULL;
    numero_palabras = 0;
    delete antigua_raiz;
}

void Arbol::saco_palabras(Nodo * nodo, string palabra1, string palabra2, list<string> &resultado) {
    if (nodo == NULL) return;
    if (nodo->elemento > palabra1)
        saco_palabras(nodo->hijo_izquierdo, palabra1, palabra2, resultado);
    if (nodo->elemento > palabra1 && nodo->elemento < palabra2)
        resultado.push_back(nodo->elemento);
    if (nodo->elemento < palabra2)
        saco_palabras(nodo->hijo_derecho, palabra1, palabra2, resultado);
}