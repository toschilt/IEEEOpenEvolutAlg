#include <iostream>
#include <vector>
#include "Pacote.h"
#include "CoordR2.h"
#include "Grafo.h"

#include "StatusRobo.h"
#include "PlanejamentoRobo.h"


int main() {

    /*
     * =========================
     * DEFINIÇÕES INICIAIS
     * =========================
    */

    CoordR2 *posicaoInicial = new CoordR2(1, 1);
    Grafo *cenarioGrafo = new Grafo("../files/plataforma.txt");
    cenarioGrafo->Gera_Grafo();

    vector<Pacote*> *pacotesDisponiveis; //Ver como serão coletados esses dados

    StatusRobo *robo = new StatusRobo(ARMAZENAMENTO_ROBO, posicaoInicial, pacotesDisponiveis);

    PlanejamentoRobo *planejamento = new PlanejamentoRobo(robo);
    planejamento->evoluiNGeracoes(GERACOES);


    return 0;
}