#include "Pacote.h"

using namespace std;

//MÉTODOS CONSTRUTORES
Pacote::Pacote()
{
    this->cor = COR_INDEF;
    this->numero = -1;
    this->posicaoAtual = nullptr;
    this->posicoesCaptura = nullptr;
    posicoesEntrega = nullptr;
}

Pacote::Pacote(int cor, int numero)
{
    this->cor = cor;
    this->numero = numero;
    this->posicaoAtual = nullptr;
    this->posicoesCaptura = nullptr;
    posicoesEntrega = nullptr;
}

Pacote::Pacote(Grafo grafoCenario, int cor, int numero, CoordR2 *posicaoAtual)
{
    this->cor = cor;
    this->numero = numero;
    this->posicaoAtual = posicaoAtual;

    posicoesCaptura = new vector<CoordR2>;
    posicoesEntrega = new vector<CoordR2>;

    setPosicoesCaptura(grafoCenario, this->cor, this->numero, posicaoAtual);
    setPosicoesEntrega(grafoCenario, cor, numero);
}

Pacote::Pacote(Grafo grafoCenario, int cor, CoordR2 *posicaoAtual)
{
    this->cor = cor;
    this->numero = -1;
    this->posicaoAtual = posicaoAtual;

    posicoesCaptura = new vector<CoordR2>;
    posicoesEntrega = new vector<CoordR2>;

    setPosicoesCaptura(grafoCenario, this->cor, this->numero, posicaoAtual);
    setPosicoesEntrega(grafoCenario, this->cor, this->numero);
}

void Pacote::setPosicoesCaptura(Grafo grafoCenario, int cor, int numero, CoordR2 *posicaoAtual)
{
    int x = posicaoAtual->x;
    int y = posicaoAtual->y;

    CoordR2 above = CoordR2(x, y - 1);
    CoordR2 bellow = CoordR2(x, y + 1);
    CoordR2 left = CoordR2(x - 1, y);
    CoordR2 right = CoordR2(x + 1, y);

    if(!grafoCenario.Get_Vizinhos(above).empty())
    {
        posicoesCaptura->push_back(above);
    }

    if(!grafoCenario.Get_Vizinhos(bellow).empty())
    {
        posicoesCaptura->push_back(bellow);
    }
        
    if(!grafoCenario.Get_Vizinhos(left).empty())
    {
        posicoesCaptura->push_back(left);
    }
        
    if(!grafoCenario.Get_Vizinhos(right).empty())
    {
        posicoesCaptura->push_back(right);
    }
}

void Pacote::setPosicoesEntrega(Grafo grafoCenario, int cor, int numero)
{
    if(this->cor >= 4)
    {
        if(numero != -1) 
        {
            int shelf = numero % 5;

            if(shelf == 0)
            {   
                posicoesEntrega->push_back(CoordR2(5, 0));
            }
            else
            {
                posicoesEntrega->push_back(CoordR2(shelf, 0));
            }
        }
    }
    else
    {
        switch(this->cor) 
        {
            case 0:
                posicoesEntrega->push_back(CoordR2(0, 5));
                posicoesEntrega->push_back(CoordR2(6, 5));
                break;
            
            case 1:
                posicoesEntrega->push_back(CoordR2(1, 5));
                posicoesEntrega->push_back(CoordR2(5, 5));
                break;

            case 2:
                posicoesEntrega->push_back(CoordR2(2, 5));
                posicoesEntrega->push_back(CoordR2(4, 5));
                break;

            case 3:
                posicoesEntrega->push_back(CoordR2(3, 5));
                break;
        }
    }
}

void Pacote::setNumero(Grafo grafoCenario, int numero)
{
    if(numero != -1)
    {
        this->numero = numero;
        posicoesEntrega->clear();
        setPosicoesEntrega(grafoCenario, -1, this->numero);
    }
    else
    {
        cout << "[PACOTE] ERRO - número inválido em setNumero!" << endl;
    }
}

void Pacote::setPosicaoAtual(Grafo grafoCenario, CoordR2 *posicaoAtual) 
{
    if(posicaoAtual != nullptr) 
    {
        this->posicaoAtual = posicaoAtual;
        
        if(numero != -1 && cor != -1)
        {
            setPosicoesCaptura(grafoCenario, cor, numero, posicaoAtual);
            setPosicoesEntrega(grafoCenario, cor, numero);
        }
        else
        {
            cout << "[PACOTE] ERRO - número e cor não foram antes de setPosicaoAtual" << endl;
        }
    }
    else
    {
        cout << "[PACOTE] ERRO - posicaoAtual inválida em setPosicaoAtual" << endl;
    }
}

std::ostream& operator<<(std::ostream& stringLoad, Pacote const& pacote)
{ 
    stringLoad << "Pacote {\n";
    stringLoad << "Cor: " << pacote.cor << "\n";
    stringLoad << "Número: " << pacote.numero << "\n";
    stringLoad << "Posição Atual: (" << pacote.posicaoAtual->x << ", " << pacote.posicaoAtual->y << ")\n";

    return stringLoad;
}
