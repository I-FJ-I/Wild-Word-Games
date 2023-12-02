#include "interprete.h"

int main() {
    string comando;
    while (cin >> comando && interprete_comandos(comando));
}
