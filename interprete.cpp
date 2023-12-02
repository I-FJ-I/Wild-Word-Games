#include "interprete.h"
#include "diccionario.h"

Diccionario diccionario;

inline void no_implementado() {
    cout << "No implementado" << endl;
}

inline void total_palabras() {
    cout <<  "Total diccionario: " << diccionario.tamano() << " palabras" << endl;
}

string normalizar_palabra(string palabra) {
    string palabra_normalizada;
    char letra;
    for (unsigned int i = 0; i < palabra.length(); i++) {
        letra = palabra[i];
        if (letra >= 'a' && letra <= 'z')
            letra = toupper(letra);
        else if (letra == (char)0xc3) {
            i++;
            letra = palabra[i];
            switch (letra) {
                case (char)0xa1:
                case (char)0x81:
                    letra = (char)0x41; break;
                case (char)0xa9:
                case (char)0x89:
                    letra = (char)0x45; break;
                case (char)0xad:
                case (char)0x8d:
                    letra = (char)0x49; break;
                case (char)0xb3:
                case (char)0x93:
                    letra = (char)0x4f; break;
                case (char)0xba:
                case (char)0x9a:
                    letra = (char)0x55; break;
                case (char)0xb1:
                case (char)0xbc:
                    palabra_normalizada += (char)0xc3;
                    letra -= 0x20; break;
                default:
                    palabra_normalizada += (char)0xc3; break;
            }   
        }
        palabra_normalizada += letra;
    }
    return palabra_normalizada;
}

void insertar() {
    string palabra;
    int numeroPalabrasNuevas = 0;
    while (cin >> palabra && palabra != "</insertar>") {
        palabra = normalizar_palabra(palabra);
        diccionario.insertar(palabra);
        numeroPalabrasNuevas++;
    }
    cout << "Insertando: " << numeroPalabrasNuevas << " palabras" << endl;
    total_palabras();
}

void vaciar() {
    diccionario.vaciar();
    cout << "Vaciando" << endl;
    total_palabras();
}

void consultar() {
    string palabra, situacion;
    cin >> palabra;
    if (diccionario.consultar(normalizar_palabra(palabra))) situacion = "Encontrada";
    else situacion = "No encontrada";
    cout << "Buscando: " << normalizar_palabra(palabra) << " -> " << situacion << endl;
}

void partidas() {
    string palabra;
    cout << "Partidas:";
    while (cin >> palabra && palabra != "</partidas>")
        cout << " " << normalizar_palabra(palabra);
    cout << endl;
    no_implementado();
}

void alocado() {
    string palabra;
    cin >> palabra;
    cout << "Alocado: " << normalizar_palabra(palabra) << endl;
    no_implementado();
}

void cesar() {
    string palabra;
    cin >> palabra;
    cout << "César: " << normalizar_palabra(palabra) << endl;
    no_implementado();
}

void juanagrama() {
    string palabra;
    cin >> palabra;
    string resultado = diccionario.juego1(normalizar_palabra(palabra));
    cout << "Juanagrama: " << normalizar_palabra(palabra) << " ->";
    if (resultado != "")
        cout  << " " << resultado;
    cout << endl;
}

void saco() {
    string palabra1, palabra2;
    list<string> saco_palabras;
    cin >> palabra1 >> palabra2;
    palabra1 = normalizar_palabra(palabra1);
    palabra2 = normalizar_palabra(palabra2);
    cout << "Saco: " << palabra1 << " " << palabra2 << " ->";
    diccionario.juego2(palabra1, palabra2, saco_palabras);
    for (list<string>::iterator iterador = saco_palabras.begin(); iterador != saco_palabras.end(); iterador++) {
        cout << " " << *iterador;
    }
    cout << endl;
}

void consome() {
    string palabra;
    cin >> palabra;
    cout << "Consomé: " << normalizar_palabra(palabra) << endl;
    no_implementado();
}

void alargapalabras() {
    string palabra;
    cin >> palabra;
    cout << "Alarga: " << normalizar_palabra(palabra) << endl;
    no_implementado();
}

inline bool exit() {
    cout << "Saliendo..." << endl;
    return false;
}

bool interprete_comandos(string comando) {
    if (comando == "<insertar>")        insertar();
    else if (comando == "<vaciar>")     vaciar();
    else if (comando == "<buscar>")     consultar();
    else if (comando == "<partidas>")   partidas();
    else if (comando == "<alocado>")    alocado();
    else if (comando == "<césar>")      cesar();
    else if (comando == "<juanagra>")   juanagrama();
    else if (comando == "<saco>")       saco();
    else if (comando == "<consomé>")    consome();
    else if (comando == "<alarga>")     alargapalabras();
    else if (comando == "<exit>")       return exit();
    return true;
}
