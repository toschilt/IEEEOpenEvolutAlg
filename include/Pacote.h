#ifndef PACOTE_H
#define PACOTE_H

#include <iostream>
#include <vector>
#include "CoordR2.h"
#include "Grafo.h"
#include "Pacote.h"

using namespace std;

enum kcores_pacotes 
{
    COR_INDEF = -1,
    COR_VERDE,
    COR_AZUL,
    COR_AMARELO,
    COR_VERMELHO,
    COR_PRETO,
    COR_BRANCO
};

class Pacote
{
    private:

    public:
        /*
        * ============
        * ATRIBUTOS
        * ============
        */

        /*
         * Define a cor do pacote em questão.
         * O código de cores está definido em kcores_pacotes.
        */
        int cor;

        /*
         * Define o número do pacote em questão.
        */
        int numero;

        /*
         * Define a posição do bloco em questão.
         * É definido pelos juízes no início de cada rodada.
        */
        CoordR2 *posicaoAtual;

        /*
         * Define as possíveis posições de captura
         * do pacote em questão.
        */
        array<CoordR2, > posicoesColeta;

        /*
         * Define as possíveis posições de entrega
         * do pacote em questão.
        */
        CoordR2 *posicoesEntrega;

        /*
        * ==============
        * CONSTRUTORES
        * ==============
        */

        /*
         * Construtor padrão. É definido:
         * cor = COR_INDEF,
         * numero = -1,
         * posicaoAtual = nullptr,
         * posicoesCaptura = nullptr,
         * posicoesEntrega = nullptr
        */
        Pacote();

        /*
         * Construtor. É definido:
         * posicaoAtual = nullptr,
         * posicoesCaptura = nullptr,
         * posicoesEntrega = nullptr.
         * Os demais parâmetros são definidos arbitrariamente.
        */
        Pacote(int cor, int number);

        /*
         * Construtor. 
         * As possíveis posições de captura e coleta são calculadas
         * a partir do grafo fornecido.
         * Cor e posicaoAtual são definidas arbitrariamente.
        */
        Pacote(Grafo grafoCenario, int cor, int numero, CoordR2 *posicaoAtual);

        /*
         * Construtor. 
         * As possíveis posições de captura e coleta são calculadas
         * a partir do grafo fornecido.
         * Cor, número e posicaoAtual são definidas arbitrariamente.
        */
        Pacote(int color, int number, Grafo graph, CoordR2 *posicaoAtual);

        /*
        * ==============
        * MÉTODOS SET
        * ==============
        */
        void setnumero(int number);
        void setposicaoAtual(Grafo graph, CoordR2 currentPosition);

        /*
        * =========================
        * MÉTODOS PARA IMPRESSÃO
        * =========================
        */
        void printposicoesCaptura();
        void printposicoesEntrega();
};

#endif