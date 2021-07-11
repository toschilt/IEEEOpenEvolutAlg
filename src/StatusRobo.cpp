#include "StatusRobo.h"

StatusRobo::StatusRobo()
{
    this->limiteArmazenamento = 4;
    this->posInicial = new CoordR2(0, 0);
    pacotesDisponíveis = nullptr;
}

StatusRobo::StatusRobo(int limiteArmazenamento, CoordR2 *posInicial, Pacote *pacotesDisponíveis)
{
    this->limiteArmazenamento = limiteArmazenamento;
    this->posInicial = posInicial;
    this->pacotesDisponíveis = pacotesDisponíveis;
}