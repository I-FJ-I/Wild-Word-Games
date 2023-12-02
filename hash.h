#ifndef _HASH
#define _HASH

#include <iostream>

using namespace std;

class TablaHash {
    friend class TablaHashJuana;
    int tamano_total;
    int tamano_actual;
    string * tabla;
    int hash(string palabra);
    int redispersion(string palabra, unsigned int antigua_clave, int i);
    void reestructurar();
    public:
        TablaHash();
        ~TablaHash();
        void vaciar();
        virtual void insertar(string palabra);
        bool consultar(string palabra);
        int get_tamano() {return tamano_actual;};
};

class TablaHashJuana : public TablaHash{
    string letras_en_orden(string palabra);
    public:
        void insertar(string palabra);
        string obtener(string palabra);
};

#endif
