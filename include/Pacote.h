#ifndef PACOTE_H
#define PACOTE_H

#include <iostream>
#include <vector>
#include "CoordR2.h"
#include "Grafo.h"
#include "Pacote.h"
#include "Constantes.h"

using namespace std;

<<<<<<< Updated upstream
class Pacote
{
=======
//LUCAS TOSCHI LEMBRA DE CRIAR O ENUM P/ CORES OBRIGADO

enum cores {
    verde,
    azul,
    amarelo,
    vermelho,
    preto,  
    branco
};

class Pacote {
>>>>>>> Stashed changes
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
        vector<CoordR2> *posicoesCaptura;

        /*
         * Define as possíveis posições de entrega
         * do pacote em questão.
        */
        vector<CoordR2> *posicoesEntrega;

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
         * numero é definido como -1.
         * Cor e posicaoAtual são definidas arbitrariamente.
        */
        Pacote(Grafo grafoCenario, int cor, CoordR2 *posicaoAtual);


        /*
        * ==============
        * MÉTODOS SET
        * ==============
        */
       
        /*
         * Obtém as posições de captura do pacote em questão
         * através do grafo do cenário.
         * Atualiza o vetor posicoesCaptura.
        */
        void setPosicoesCaptura(Grafo grafoCenario, int cor, int numero, CoordR2 *posicaoAtual);
        
        /*
         * Obtém as posições de entrega do pacote em questão
         * através do grafo do cenário.
         * Atualiza o vetor posicoesEntrega.
        */
        void setPosicoesEntrega(Grafo grafoCenraio, int cor, int numero);
        
        /*
         * Define o número do bloco e atualiza as posições de entrega
         * através do grafo do cenário.
         * Atualiza o vetor posicoesCaptura e posicoesEntrega.
        */
        void setNumero(Grafo grafoCenario, int numero);

        /*
         * Define a posição atual do bloco e atualiza as posições de entrega
         * e coleta através do grafo do cenário.
         * Atualiza o vetor posicoesCaptura e posicoesEntrega.
         * OBS: É necessário ter definidos o número e cor do pacote!
        */
        void setPosicaoAtual(Grafo grafoCenario, CoordR2 *posicaoAtual);

        /*
        * =======================
        * MÉTODO PARA IMPRESSÃO
        * =======================
        */

        friend std::ostream & operator<<(std::ostream& output, Pacote const& pacote);
};

#endif