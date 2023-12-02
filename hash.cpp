#include "hash.h"
#include <algorithm>

TablaHash::TablaHash() {
    tamano_actual = 0;
    tamano_total = 100113;
    tabla = new string[tamano_total];
}

TablaHash::~TablaHash() {
    delete[] tabla;
}

int TablaHash::hash(string palabra) {
    unsigned int clave = 5381;
    int i = 0;
    while (i < palabra.length()) {
        clave = clave * 33 xor (unsigned int)palabra[i];
        i++;
    }
    return clave % tamano_total;
}

int TablaHash::redispersion(string palabra, unsigned int antigua_clave, int i) {
    return (antigua_clave + ((unsigned int)(palabra[0]+palabra[(palabra.length()-1)>>1]*33))*i) % tamano_total;
}

void TablaHash::reestructurar() {
    int tamano_antiguo = tamano_total;
    tamano_total = (tamano_total << 1) - 1;
    string * antigua_tabla = tabla;
    tabla = new string[tamano_total];
    tamano_actual = 0;
    int i = 0;
    while (i < tamano_antiguo) {
        string elemento = antigua_tabla[i];
        if (elemento != "")
            insertar(elemento);
        i++;
    }
    delete[] antigua_tabla;
}

void TablaHash::insertar(string palabra) {
    unsigned int clave = hash(palabra);
    if (tabla[clave] != "" && tabla[clave] != palabra) {
        int i = 1;
        unsigned int antigua_clave = clave;
        clave = redispersion(palabra, antigua_clave, i);
        while (tabla[clave] != "" && tabla[clave] != palabra) {
            i++;
            clave = redispersion(palabra, antigua_clave, i);
        }
    }  
    if (tabla[clave] != palabra) {
        tabla[clave] = palabra;
        tamano_actual++;
    }
    if (tamano_actual*100/tamano_total >= 75)
        reestructurar();
}

void TablaHash::vaciar() {
    string * aux = tabla;
    tabla = new string[tamano_total];
    delete[] aux;
    tamano_actual = 0;
}

bool TablaHash::consultar(string palabra) {
    unsigned int clave = hash(palabra);
    if (tabla[clave] == palabra)
        return true;
    int i = 1;
    unsigned int antigua_clave = clave;
    clave = redispersion(palabra, antigua_clave, i);
    while (tabla[clave] != "" && tabla[clave] != palabra) {
        i++;
        clave = redispersion(palabra, antigua_clave, i);
    }
    return tabla[clave] == palabra;
}

string TablaHashJuana::letras_en_orden(string palabra) {
    sort(palabra.begin(), palabra.end());   
    return palabra;
}

void TablaHashJuana::insertar(string palabra) {
    string letras_ord = letras_en_orden(palabra);
    int clave = hash(letras_ord);
    int antigua_clave = clave;
    int i = 0;
    while (tabla[clave] != "" && letras_en_orden(tabla[clave]) != letras_ord) {
        i++;
        clave = redispersion(letras_ord, antigua_clave, i);
    }
    if (tabla[clave] == "")
        tamano_actual++;
    if (tabla[clave] == "" || tabla[clave] > palabra)
        tabla[clave] = palabra;
    if (tamano_actual*100/tamano_total >= 75)
        reestructurar();
}

string TablaHashJuana::obtener(string palabra) {
    string letras_ord = letras_en_orden(palabra);
    int clave = hash(letras_ord);
    int antigua_clave = clave;
    int i = 0;
    while (tabla[clave] != "" && letras_en_orden(tabla[clave]) != letras_ord) {
        i++;
        clave = redispersion(letras_ord, antigua_clave, i);
    }
    return tabla[clave];
}
