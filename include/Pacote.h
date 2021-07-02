#ifndef PACOTE_H
#define PACOTE_H

#include <iostream>
#include <vector>
#include "CoordR2.h"
#include "Grafo.h"

using namespace std;

//LUCAS TOSCHI LEMBRA DE CRIAR O ENUM P/ CORES OBRIGADO

class Pacote {
    private:

    public:
        /*
         * PADRÃO DE CORES
         * 0 -> verde
         * 1 -> azul
         * 2 -> amarelo
         * 3 -> vermelho
         * 4 -> preto
         * 5 -> branco
        */
        int cor;

        int numero;

        /*
         * Posição do bloco deicidida pelos juízes
        */
        CoordR2 posicaoAtual;

        /*
         * Posições possíveis para captura do pacote
        */
        vector<CoordR2> posicoesCaptura;

        /*
         * Posições possíveis para entrega do pacote
        */
        vector<CoordR2> posicoesEntrega;

        Pacote();
        Pacote(int color, int number);
        Pacote(int color, Grafo graph, CoordR2 currentPosition);
        Pacote(int color, int number, Grafo graph, CoordR2 currentPosition);

        //MÉTODOS SET
        void setnumero(int number);
        void setposicaoAtual(Grafo graph, CoordR2 currentPosition);

        //MÉTODOS PRINT
        void printposicoesCaptura();
        void printposicoesEntrega();
};

#endif