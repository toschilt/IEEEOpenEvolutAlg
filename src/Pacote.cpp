#include "Pacote.h"

using namespace std;

Pacote::Pacote() 
{
    cor = -1;
    numero = -1;
    posicaoAtual = nullptr;
    posicoesCaptura = nullptr;
    posicoesEntrega = nullptr;
}

Pacote::Pacote(int cor, int numero)
{
    this->cor = cor;
    this->numero = numero;
    posicaoAtual = nullptr;
    posicoesCaptura = nullptr;
    posicoesEntrega = nullptr;
}

Pacote::Pacote(Grafo grafoCenario, int cor, CoordR2 *posicaoAtual)
{
    this->cor = cor;
    this->numero = -1;
    this->posicaoAtual = posicaoAtual;

    int x = posicaoAtual.x;
    int y = posicaoAtual.y;

    /*
    Checa as possíveis posições de coleta para
    esse pacote
    */
    CoordR2 above = CoordR2(x, y - 1);
    CoordR2 bellow = CoordR2(x, y + 1);
    CoordR2 left = CoordR2(x - 1, y);
    CoordR2 right = CoordR2(x + 1, y);

    if(!graph.Get_Vizinhos(above).empty())
        this->posicoesCaptura.push_back(above);

    if(!graph.Get_Vizinhos(bellow).empty())
        this->posicoesCaptura.push_back(bellow);

    if(!graph.Get_Vizinhos(left).empty())
        this->posicoesCaptura.push_back(left);

    if(!graph.Get_Vizinhos(right).empty())
        this->posicoesCaptura.push_back(right);

    switch(cor) {
        case 0:
            this->posicoesEntrega.push_back(CoordR2(0, 5));
            this->posicoesEntrega.push_back(CoordR2(6, 5));
            break;
            
        case 1:
            this->posicoesEntrega.push_back(CoordR2(1, 5));
            this->posicoesEntrega.push_back(CoordR2(5, 5));
            break;

        case 2:
            this->posicoesEntrega.push_back(CoordR2(2, 5));
            this->posicoesEntrega.push_back(CoordR2(4, 5));
            break;

        case 3:
            this->posicoesEntrega.push_back(CoordR2(3, 5));
            break;
    }
}

Pacote::Pacote(int cor, int numero, Grafo graph, CoordR2 posicaoAtual) {
    this->cor = cor;
    this->numero = numero;
    this->posicaoAtual = posicaoAtual;

    int x = posicaoAtual.x;
    int y = posicaoAtual.y;

    /*
    Checa as possíveis posições de coleta para
    esse pacote
    */
    CoordR2 above = CoordR2(x, y - 1);
    CoordR2 bellow = CoordR2(x, y + 1);
    CoordR2 left = CoordR2(x - 1, y);
    CoordR2 right = CoordR2(x + 1, y);

    if(!graph.Get_Vizinhos(above).empty())
        this->posicoesCaptura.push_back(above);

    if(!graph.Get_Vizinhos(bellow).empty())
        this->posicoesCaptura.push_back(bellow);

    if(!graph.Get_Vizinhos(left).empty())
        this->posicoesCaptura.push_back(left);

    if(!graph.Get_Vizinhos(right).empty())
        this->posicoesCaptura.push_back(right);

    if(cor >= 4) {
        if(numero != -1) {
            int shelf = numero % 5;
            if(shelf == 0)
                this->posicoesEntrega.push_back(CoordR2(5, 0));
            else
                this->posicoesEntrega.push_back(CoordR2(shelf, 0));
        }
    }
    else {
        switch(cor) {
            case 0:
                this->posicoesEntrega.push_back(CoordR2(0, 5));
                this->posicoesEntrega.push_back(CoordR2(6, 5));
                break;
            
            case 1:
                this->posicoesEntrega.push_back(CoordR2(1, 5));
                this->posicoesEntrega.push_back(CoordR2(5, 5));
                break;

            case 2:
                this->posicoesEntrega.push_back(CoordR2(2, 5));
                this->posicoesEntrega.push_back(CoordR2(4, 5));
                break;

            case 3:
                this->posicoesEntrega.push_back(CoordR2(3, 5));
                break;
        }
    }
}

void Pacote::setnumero(int numero) {
    if(numero != -1) {
        this->numero = numero;

        this->posicoesEntrega.clear();
        int shelf = numero % 5;
        if(shelf == 0)
            this->posicoesEntrega.push_back(CoordR2(5, 0));
        else
            this->posicoesEntrega.push_back(CoordR2(shelf, 0));
    }
    else {
        cout << "[Pacote] Falha em setar - número inválido!" << endl;
    }
}

void Pacote::setposicaoAtual(Grafo graph, CoordR2 posicaoAtual) {
    if(posicaoAtual.x == -1 || posicaoAtual.y == -1) {
        this->posicaoAtual = posicaoAtual;

        int x = posicaoAtual.x;
        int y = posicaoAtual.y;

        /*
        Checa as possíveis posições de coleta para
        esse pacote
        */
        CoordR2 above = CoordR2(x, y - 1);
        CoordR2 bellow = CoordR2(x, y + 1);
        CoordR2 left = CoordR2(x - 1, y);
        CoordR2 right = CoordR2(x + 1, y);

        if(!graph.Get_Vizinhos(above).empty())
            this->posicoesCaptura.push_back(above);

        if(!graph.Get_Vizinhos(bellow).empty())
            this->posicoesCaptura.push_back(bellow);

        if(!graph.Get_Vizinhos(left).empty())
            this->posicoesCaptura.push_back(left);

        if(!graph.Get_Vizinhos(right).empty())
            this->posicoesCaptura.push_back(right);
        }

    else {
        cout << "[Pacote] Falha em setar - posição nula!" << endl;
    }
}

void Pacote::printposicoesCaptura() {
    for(int i = 0; i < this->posicoesCaptura.size(); i++) {
        cout << "[Pacote] Capture: " << this->posicoesCaptura[i] << endl;
    }
}

void Pacote::printposicoesEntrega() {
    for(int i = 0; i < this->posicoesEntrega.size(); i++) {
        cout << "[Pacote] Deliver: " << this->posicoesEntrega[i] << endl;
    }
}