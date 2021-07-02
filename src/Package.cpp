#include "Package.h"
#include "Grafo.h"
#include <iostream>

using namespace std;

//MÉTODOS CONSTRUTORES
Package::Package() {
    this->color = -1;
    this->number = -1;
}

Package::Package(int color, int number) {
    this->color = color;
    this->number = number;
    this->currentPosition = CoordR2(-1, -1);
}

Package::Package(int color, Grafo graph, CoordR2 currentPosition) {
    this->color = color;
    this->number = -1;
    this->currentPosition = currentPosition;

    int x = currentPosition.x;
    int y = currentPosition.y;

    /*
    Checa as possíveis posições de coleta para
    esse pacote
    */
    CoordR2 above = CoordR2(x, y - 1);
    CoordR2 bellow = CoordR2(x, y + 1);
    CoordR2 left = CoordR2(x - 1, y);
    CoordR2 right = CoordR2(x + 1, y);

    if(!graph.Get_Vizinhos(above).empty())
        this->capturePositions.push_back(above);

    if(!graph.Get_Vizinhos(bellow).empty())
        this->capturePositions.push_back(bellow);

    if(!graph.Get_Vizinhos(left).empty())
        this->capturePositions.push_back(left);

    if(!graph.Get_Vizinhos(right).empty())
        this->capturePositions.push_back(right);

    switch(color) {
        case 0:
            this->deliverPositions.push_back(CoordR2(0, 5));
            this->deliverPositions.push_back(CoordR2(6, 5));
            break;
            
        case 1:
            this->deliverPositions.push_back(CoordR2(1, 5));
            this->deliverPositions.push_back(CoordR2(5, 5));
            break;

        case 2:
            this->deliverPositions.push_back(CoordR2(2, 5));
            this->deliverPositions.push_back(CoordR2(4, 5));
            break;

        case 3:
            this->deliverPositions.push_back(CoordR2(3, 5));
            break;
    }
}

Package::Package(int color, int number, Grafo graph, CoordR2 currentPosition) {
    this->color = color;
    this->number = number;
    this->currentPosition = currentPosition;

    int x = currentPosition.x;
    int y = currentPosition.y;

    /*
    Checa as possíveis posições de coleta para
    esse pacote
    */
    CoordR2 above = CoordR2(x, y - 1);
    CoordR2 bellow = CoordR2(x, y + 1);
    CoordR2 left = CoordR2(x - 1, y);
    CoordR2 right = CoordR2(x + 1, y);

    if(!graph.Get_Vizinhos(above).empty())
        this->capturePositions.push_back(above);

    if(!graph.Get_Vizinhos(bellow).empty())
        this->capturePositions.push_back(bellow);

    if(!graph.Get_Vizinhos(left).empty())
        this->capturePositions.push_back(left);

    if(!graph.Get_Vizinhos(right).empty())
        this->capturePositions.push_back(right);

    if(color >= 4) {
        if(number != -1) {
            int shelf = number % 5;
            if(shelf == 0)
                this->deliverPositions.push_back(CoordR2(5, 0));
            else
                this->deliverPositions.push_back(CoordR2(shelf, 0));
        }
    }
    else {
        switch(color) {
            case 0:
                this->deliverPositions.push_back(CoordR2(0, 5));
                this->deliverPositions.push_back(CoordR2(6, 5));
                break;
            
            case 1:
                this->deliverPositions.push_back(CoordR2(1, 5));
                this->deliverPositions.push_back(CoordR2(5, 5));
                break;

            case 2:
                this->deliverPositions.push_back(CoordR2(2, 5));
                this->deliverPositions.push_back(CoordR2(4, 5));
                break;

            case 3:
                this->deliverPositions.push_back(CoordR2(3, 5));
                break;
        }
    }
}

void Package::setNumber(int number) {
    if(number != -1) {
        this->number = number;

        this->deliverPositions.clear();
        int shelf = number % 5;
        if(shelf == 0)
            this->deliverPositions.push_back(CoordR2(5, 0));
        else
            this->deliverPositions.push_back(CoordR2(shelf, 0));
    }
    else {
        cout << "[PACKAGE] Falha em setar - número inválido!" << endl;
    }
}

void Package::setCurrentPosition(Grafo graph, CoordR2 currentPosition) {
    if(currentPosition.x == -1 || currentPosition.y == -1) {
        this->currentPosition = currentPosition;

        int x = currentPosition.x;
        int y = currentPosition.y;

        /*
        Checa as possíveis posições de coleta para
        esse pacote
        */
        CoordR2 above = CoordR2(x, y - 1);
        CoordR2 bellow = CoordR2(x, y + 1);
        CoordR2 left = CoordR2(x - 1, y);
        CoordR2 right = CoordR2(x + 1, y);

        if(!graph.Get_Vizinhos(above).empty())
            this->capturePositions.push_back(above);

        if(!graph.Get_Vizinhos(bellow).empty())
            this->capturePositions.push_back(bellow);

        if(!graph.Get_Vizinhos(left).empty())
            this->capturePositions.push_back(left);

        if(!graph.Get_Vizinhos(right).empty())
            this->capturePositions.push_back(right);
        }

    else {
        cout << "[PACKAGE] Falha em setar - posição nula!" << endl;
    }
}

void Package::printCapturePositions() {
    for(int i = 0; i < this->capturePositions.size(); i++) {
        cout << "[PACKAGE] Capture: " << this->capturePositions[i] << endl;
    }
}

void Package::printDeliverPositions() {
    for(int i = 0; i < this->deliverPositions.size(); i++) {
        cout << "[PACKAGE] Deliver: " << this->deliverPositions[i] << endl;
    }
}