#include "SequenciaPacotes.h"

SequenciaPacotes::SequenciaPacotes(vector<Pacote*> *pacotes, Grafo *grafoCenario)
{
    this->sequenciaPacotes = pacotes;
    this->pacoteAtual = 0;
    this->fitness = 0;

    this->grafoCenario = grafoCenario;
}

int SequenciaPacotes::calculaCustoDeslocamento(CoordR2 coordenadaAtual, CoordR2 coordenadaAlvo)
{
    vector<CoordR2> deslocamentoTotal = this->grafoCenario->Breadth_First_Search(coordenadaAtual, coordenadaAlvo); 

    return deslocamentoTotal.size();
}

float SequenciaPacotes::calculaPontosColeta(Pacote* pacote, int distancia)
{
    int fitness = 0;

    if(pacote->cor < 4)
    {
        fitness += GANHO_COLETA_PACOTE_COLORIDO - (distancia*PENALIDADE_QUADRANTE_DESLOCADO);
    }
    else if (pacote->cor == 4)
    {
        fitness += GANHO_COLETA_PACOTE_PRETO - (distancia*PENALIDADE_QUADRANTE_DESLOCADO);
    }
    else
    {
        fitness += GANHO_COLETA_PACOTE_BRANCO - (distancia*PENALIDADE_QUADRANTE_DESLOCADO);
    }

    return fitness;
}

float SequenciaPacotes::calculaPontosEntrega(Pacote* pacote, int distancia)
{
    int fitness = 0;

    if(pacote->cor < 4)
    {
        fitness += GANHO_ENTREGA_PACOTE_COLORIDO - (distancia*PENALIDADE_QUADRANTE_DESLOCADO);
    }
    else if (pacote->cor == 4)
    {
        fitness += GANHO_ENTREGA_PACOTE_PRETO - (distancia*PENALIDADE_QUADRANTE_DESLOCADO);
    }
    else
    {
        fitness += GANHO_ENTREGA_PACOTE_BRANCO - (distancia*PENALIDADE_QUADRANTE_DESLOCADO);
    }

    return fitness;
}

CoordR2 SequenciaPacotes::encontraMelhorPosicaoEntrega(CoordR2 coordenadaAtual, Pacote* pacote, int* menorDistancia)
{
    (*menorDistancia) = this->calculaCustoDeslocamento(coordenadaAtual, pacote->posicoesEntrega->at(0));
    int distancia = 0;

    CoordR2 melhorPosicao = pacote->posicoesEntrega->at(0);
 
    for(int i = 1; i < pacote->posicoesEntrega->size(); i++)
    {
        distancia = this->calculaCustoDeslocamento(coordenadaAtual, pacote->posicoesEntrega->at(i));

        if(distancia < (*menorDistancia)) 
        {
            (*menorDistancia) = distancia;
            melhorPosicao = pacote->posicoesEntrega->at(i);
        }
    }  

    return melhorPosicao;
}

float SequenciaPacotes::entregaPacote(CoordR2 *posicaoAtualRobo, set<Pacote*> pacotesColetados)
{
    // Iteradores dos pacotes para escolher o melhor pacote a ser entregue
    set<Pacote*>::iterator iteradorPacotes = pacotesColetados.begin();

    CoordR2 posicaoEntregaAtual;
    CoordR2 melhorPosicaoEntrega;

    int distanciaAtual = 0;
    int melhorDistancia = 0;

    Pacote* melhorPacote;

    // Inicializa melhores parametros com o pacote inicial
    melhorPosicaoEntrega = this->encontraMelhorPosicaoEntrega((*posicaoAtualRobo), (*iteradorPacotes), &melhorDistancia);
    melhorPacote = (*iteradorPacotes);
    iteradorPacotes++;

    // Itera por todos os pacotes caso existam e escolhe o melhor pacote para entrega no momento
    while (iteradorPacotes != pacotesColetados.end())
    { 
        posicaoEntregaAtual = this->encontraMelhorPosicaoEntrega((*posicaoAtualRobo), *iteradorPacotes, &distanciaAtual);
        if(melhorDistancia > distanciaAtual)
        {
            melhorDistancia = distanciaAtual;
            melhorPacote = (*iteradorPacotes);
            melhorPosicaoEntrega = posicaoEntregaAtual;
        }
        iteradorPacotes++;
    }
    //----------------------------------------------------------------

    // atualiza posicao do robo, pacotes coletados e fitness
    (*posicaoAtualRobo) = melhorPosicaoEntrega;

    int fitness = this->calculaPontosEntrega(melhorPacote, melhorDistancia);

    iteradorPacotes = pacotesColetados.find(melhorPacote);
    pacotesColetados.erase(iteradorPacotes);
    //----------------------------------------------------------------

    return fitness;
}

float SequenciaPacotes::coletaPacote(CoordR2 *posicaoAtualRobo, Pacote* pacote)
{
    int menorDistancia = this->calculaCustoDeslocamento((*posicaoAtualRobo), pacote->posicoesCaptura->at(0));
    int distancia = 0;

    CoordR2 melhorPosicao = pacote->posicoesCaptura->at(0);
 
    for(int i = 1; i < pacote->posicoesCaptura->size(); i++)
    {
        distancia = this->calculaCustoDeslocamento((*posicaoAtualRobo), pacote->posicoesCaptura->at(i));

        if(distancia < menorDistancia) 
        {
            menorDistancia = distancia;
            melhorPosicao = pacote->posicoesCaptura->at(i);
        }
    }

    int fitness = this->calculaPontosColeta(pacote, distancia);
    (*posicaoAtualRobo) = melhorPosicao;

    return fitness;
}

float SequenciaPacotes::calculaFitness(vector <int> *sequenciaAcoes, CoordR2 *posicaoInicialRobo)
{
    float fitness = 0;

    set<Pacote*> pacotesColetados;

    CoordR2 *posicaoAtualRobo = new CoordR2();
    *posicaoAtualRobo = *posicaoInicialRobo;

    for(int i = 0; i < QUANTIDADE_ACOES; i++)
    {
        if(sequenciaAcoes->at(i) == coleta)
        {
            pacotesColetados.insert(this->sequenciaPacotes->at(this->pacoteAtual));
            fitness += this->coletaPacote(posicaoAtualRobo, this->sequenciaPacotes->at(this->pacoteAtual));

            this->pacoteAtual++;      
        }
        else // ENTREGA
        {
            fitness += this->entregaPacote(posicaoAtualRobo, pacotesColetados);
        }
    }

    this->pacoteAtual = 0;
    this->fitness = fitness;

    return fitness;
}

ostream& operator<<(ostream& os, const SequenciaPacotes& pacotes)
{
    for(int i = 0; i < QUANTIDADE_ACOES/2; i++)
    {
        os << *(pacotes.sequenciaPacotes->at(i));
        os << endl;
    }

    return os;
}