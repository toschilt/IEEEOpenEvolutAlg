#include <iostream>
#include <vector>
#include <chrono>
#include "Pacote.h"
#include "CoordR2.h"
#include "Grafo.h"
#include "StatusRobo.h"
#include "PlanejamentoRobo.h"
#include "Constantes.h"

vector<Pacote*> *setPacotes(Grafo *grafoCenario) {
    Pacote *b1 = new Pacote(*grafoCenario, 4, 3, new CoordR2(4, 2));
    Pacote *b2 = new Pacote(*grafoCenario, 5, 9, new CoordR2(4, 2));
    Pacote *b3 = new Pacote(*grafoCenario, 5, 7, new CoordR2(4, 2));
    Pacote *b4 = new Pacote(*grafoCenario, 2, -1, new CoordR2(4, 2));
    Pacote *b5 = new Pacote(*grafoCenario, 5, 4, new CoordR2(5, 2));
    Pacote *b6 = new Pacote(*grafoCenario, 4, 10, new CoordR2(5, 2));
    Pacote *b7 = new Pacote(*grafoCenario, 5, 6, new CoordR2(5, 3));
    Pacote *b8 = new Pacote(*grafoCenario, 5, 3, new CoordR2(5, 3));
    Pacote *b9 = new Pacote(*grafoCenario, 5, 11, new CoordR2(5, 3));
    Pacote *b10 = new Pacote(*grafoCenario, 1, -1, new CoordR2(4, 3));

    vector<Pacote*> *pacotesDisponiveis = new vector<Pacote*>;
    pacotesDisponiveis->push_back(b1);
    pacotesDisponiveis->push_back(b2);
    pacotesDisponiveis->push_back(b3);
    pacotesDisponiveis->push_back(b4);
    pacotesDisponiveis->push_back(b5);
    pacotesDisponiveis->push_back(b6);
    pacotesDisponiveis->push_back(b7);
    pacotesDisponiveis->push_back(b8);
    pacotesDisponiveis->push_back(b9);
    pacotesDisponiveis->push_back(b10);

    return pacotesDisponiveis;
}


int main() {

    /*
     * =========================
     * DEFINIÇÕES INICIAIS
     * =========================
    */

    cout << "[MAIN] Início do programa!" << endl;

    Grafo *grafoCenario = new Grafo("../files/plataforma.txt");
    grafoCenario->Gera_Grafo();

    CoordR2 *posicaoInicial = new CoordR2(1, 1);

    vector<Pacote*>* pacotesDisponiveis;
    pacotesDisponiveis = setPacotes(grafoCenario);
    cout << "[MAIN] Setou os pacotes!" << endl;

    StatusRobo *sid = new StatusRobo(grafoCenario, ARMAZENAMENTO_ROBO, posicaoInicial, pacotesDisponiveis);
    cout << "[MAIN] Criou o StatusRobo!" << endl;
    
    PlanejamentoRobo *planejamento = new PlanejamentoRobo(sid);
    cout << "[MAIN] Criou o PlanejamentoRobo" << endl;

    cout << "[MAIN] Evoluindo N gerações AGORA!" << endl;
    planejamento->evoluiNGeracoes(GERACOES);
    cout << "[MAIN] Cabô, vamo pra casa nessa porra!" << endl;

    return 0;
}