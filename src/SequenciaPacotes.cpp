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
        fitness += 20 - (distancia*2);
    }
    else if (pacote->cor == 4)
    {
        fitness += 100 - (distancia*2);
    }
    else
    {
        fitness += 200 - (distancia*2);
    }

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

float SequenciaPacotes::calculaPontosEntrega(Pacote* pacote, int distancia)
{
    int fitness = 0;

    if(pacote->cor < 4)
    {
        fitness += 100 - (distancia*5);
    }
    else if (pacote->cor == 4)
    {
        fitness += 500 - (distancia*5);
    }
    else
    {
        fitness += 1000 - (distancia*5);
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

float SequenciaPacotes::calculaFitness(vector <int> *sequenciaAcoes, CoordR2 *posicaoInicialRobo)
{
    //cout << "[SEQUENCIAPACOTES] Entrou na função calculaFitness" << endl;
    float fitness = 0;

    //cout << "[SEQUENCIAPACOTES] Antes de declarar a pacotesColetados" << endl;
    set<Pacote*> pacotesColetados;
    //cout << "[SEQUENCIAPACOTES] Depois de declarar a pacotesColetados" << endl;

    CoordR2 *posicaoAtualRobo = posicaoInicialRobo;

    for(int i = 0; i < QUANTIDADE_ACOES; i++)
    {
        //cout << "[SEQUENCIAPACOTES] Iteração " << i << " sobre a quantidade de ações!" << endl;
        if(sequenciaAcoes->at(i) == coleta)
        {
            //cout << "[SEQUENCIAPACOTES] (Iteração " << i << "- this->pacoteAtual: " << this->pacoteAtual << ") - É uma coleta!" << endl;
            pacotesColetados.insert(this->sequenciaPacotes->at(this->pacoteAtual));
            //cout << "[SEQUENCIAPACOTES] (Iteração " << i << ") - Realizou a inserção de um pacote" << endl;
            fitness += this->coletaPacote(posicaoAtualRobo, this->sequenciaPacotes->at(this->pacoteAtual));

            this->pacoteAtual++;      
        }
        else // ENTREGA
        {
            //cout << "[SEQUENCIAPACOTES] (Iteração " << i << ") - É uma entrega!" << endl;
            //cout << "[SEQUENCIAPACOTES] Antes de entrar na entregaPacote" << endl;
            fitness += this->entregaPacote(posicaoAtualRobo, pacotesColetados);
            //cout << "[SEQUENCIAPACOTES] Saiu da entregaPacote" << endl;
        }

        // cout << sequenciaAcoes->at(i) << " ";
    }
    // cout << endl;

    this->pacoteAtual = 0;

    return fitness;
}
