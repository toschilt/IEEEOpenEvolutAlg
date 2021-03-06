#include "StatusRobo.h"

StatusRobo::StatusRobo()
{
    this->limiteArmazenamento = 4;
    this->posInicial = new CoordR2(0, 0);
    pacotesDisponiveis = nullptr;
}

StatusRobo::StatusRobo(Grafo *grafoCenario, int limiteArmazenamento, CoordR2 *posInicial, vector<Pacote*> *pacotesDisponiveis)
{
    this->grafoCenario = grafoCenario;
    this->limiteArmazenamento = limiteArmazenamento;
    this->posInicial = posInicial;
    this->pacotesDisponiveis = pacotesDisponiveis;
}
