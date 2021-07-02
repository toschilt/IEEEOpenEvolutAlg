#include <iostream>
#include <vector>
#include "Pacote.h"
#include "CoordR2.h"
#include "Grafo.h"

int main() {

    /*
     * =========================
     * DEFINIÇÕES INICIAIS
     * =========================
    */

    CoordR2 *initialPosition = new CoordR2(1, 1);
    Grafo *scenarioGraph = new Grafo("../files/plataforma.txt");
    scenarioGraph->Gera_Grafo();



    return 0;
}