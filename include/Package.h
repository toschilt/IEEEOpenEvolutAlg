#ifndef PACKAGE
#define PACKAGE

#include <iostream>
#include <vector>
#include "CoordR2.h"
#include "Grafo.h"

using namespace std;

class Package {
    private:

    public:
        /*
        PADRÃO DE CORES
        0 -> verde
        1 -> azul
        2 -> amarelo
        3 -> vermelho
        4 -> preto
        5 -> branco
        */
        int color;

        /*
        Número do bloco preto/branco
        Se o bloco é colorido, recebe valor -1.
        */
        int number;

        /*
        Posição do bloco deicidida pelos juízes
        */
        CoordR2 currentPosition;

        /*
        Posições possíveis para captura do pacote
        */
        vector<CoordR2> capturePositions;

        /*
        Posições possíveis para entrega do pacote
        */
        vector<CoordR2> deliverPositions;

        //MÉTODOS CONSTRUTORES
        Package();
        Package(int color, int number);
        Package(int color, Grafo graph, CoordR2 currentPosition);
        Package(int color, int number, Grafo graph, CoordR2 currentPosition);

        //MÉTODOS SET
        void setNumber(int number);
        void setCurrentPosition(Grafo graph, CoordR2 currentPosition);

        //MÉTODOS PRINT
        void printCapturePositions();
        void printDeliverPositions();
};

#endif
