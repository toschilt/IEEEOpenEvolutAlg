#ifndef STATUSROBO_H
#define STATUSROBO_H

#include "CoordR2.h"
#include "Pacote.h"
#include "Constantes.h"
#include <vector>

class StatusRobo
{
    private:

    public:
        /*
        * ============
        * ATRIBUTOS
        * ============
        */

        /*
         * Define o limite do armazenamento do robô para
         * guardar os blocos.
         * Definido através das limitações construtivas do robô.
        */
        int limiteArmazenamento;

        /*
         * Define a orientação do robô em relação ao cenário.
         * Definido através das limitações construtivas do robô.
         * Código de orientações estabelecido no enum korientacaoRobo.
        */
        int orientacao;

        /*
         * A posição inicial do robô no cenário.
         * É definido pelos jurados a cada rodada.
        */
        CoordR2 *posInicial;

        /*
         * Vetor de pacotes disponíveis no cenário para coleta
         * É definido pelos jurados a cada rodada e obtido
         * através dos algoritmos de Visão Computacional.
        */
        vector<Pacote*> *pacotesDisponiveis;

        /*
         * Grafo construído do grafo em questão.
        */
        Grafo *grafoCenario;
    
        /*
        * ==============
        * CONSTRUTORES
        * ==============
        */

        /*
         * Construtor padrão. É definido:
         * limiteArmazenamento = 4,
         * posInicial = (0,0),
         * pacotesDisponíveis = nullptr.
        */
        StatusRobo();

        /*
         * Construtor a partir de parâmetros arbitrários.
        */
        StatusRobo(Grafo *grafoCenario, int limiteArmazenamento, CoordR2 *posInicial, vector<Pacote*> *pacotesDisponiveis);
};

#endif