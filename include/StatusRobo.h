#ifndef STATUSROBO_H
#define STATUSROBO_H

#include "CoordR2.h"
#include "Pacote.h"

/* 
 * Definição das constantes que definem a orientação do robô.
 * ORIENTACAO_PRATILEIRA - garra voltada para as pratileiras
 * ORIENTACAO_ENTREGA_COLORIDOS - garra voltada para as regiões coloridas
 * ORIENTACAO_DIREITA - garra voltada para a direita, olhando para as pratileiras
 * ORIENTACAO_ESQUERDA - garra voltada para a esquerda, olhando para as pratileiras
*/
enum korientacaoRobo {
    ORIENTACAO_PRATILEIRA,
    ORIENTACAO_ENTREGA_COLORIDOS,
    ORIENTACAO_DIREITA,
    ORIENTACAO_ESQUERDA
};

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
        Pacote *pacotesDisponíveis;
    
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
        StatusRobo(int limiteArmazenamento, CoordR2 *posInicial, Pacote *pacotesDisponíveis);
};

#endif