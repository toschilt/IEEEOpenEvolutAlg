#include "PlanejamentoRobo.h"

void PlanejamentoRobo::geraSequenciaAleatoria(vector<int> *sequenciaAcoes) 
{
    sequenciaAcoes->push_back(coleta);

    int armazenamentoAtual = 1;
    int blocosColetados = 1;

    for(int j = 1; j < (QUANTIDADE_ACOES - 1); j++)
    {
        if(blocosColetados < QUANTIDADE_PACOTES && armazenamentoAtual <= 0)
        {
            sequenciaAcoes->push_back(coleta);
        }
        else if(armazenamentoAtual >= ARMAZENAMENTO_ROBO || blocosColetados == QUANTIDADE_PACOTES)
        { 
            sequenciaAcoes->push_back(entrega);
        }
        else
        {
            sequenciaAcoes->push_back(rand() % 2); 
        }

        if(sequenciaAcoes->at(j) == coleta)
        { 
            armazenamentoAtual++;
            blocosColetados++;
        }
        else
        { 
            armazenamentoAtual--;
        }
    }
    
    sequenciaAcoes->push_back(entrega);
}

PlanejamentoRobo::PlanejamentoRobo(StatusRobo *robo) 
{
    this->melhorFitness = -INFINITY;
    this->melhorFitnessAnterior = 0;
    this->indiceDestravamentoMutacao = 1;

    this->sequenciasAcao = new vector<SequenciaAcao*>;
    
    for(int i = 0; i < TAMANHO_VETOR_SEQUENCIAACAO; i++)
    {
        this->sequenciasAcao->push_back(new SequenciaAcao(robo));
        //TODO encapsular gerar sequencia aleatória no construtor da classe SequenciaAcao
        this->geraSequenciaAleatoria(this->sequenciasAcao->at(i)->sequenciaAcoes);
    }
}

void PlanejamentoRobo::atualizaPopulacaoPacotes()
{
    for(int i = 0; i < TAMANHO_VETOR_SEQUENCIAACAO; i++) 
    {
        this->sequenciasAcao->at(i)->atualizaPopulacao(this->indiceDestravamentoMutacao);
    }
}

void PlanejamentoRobo::genocidio()
{
    //TODO A cada xx iterações, mata todos e cria uma nova população com base nos yy melhores
}

void PlanejamentoRobo::mutacao()
{

    for(int i = 0; i < TAMANHO_VETOR_SEQUENCIAACAO; i++)
    {
        if(i == this->indiceMelhorCombinacao)
        {
            continue;
        }
            
        SequenciaAcao *sequenciaAtual = sequenciasAcao->at(i);

        int numColetas = 1;
        int armazenamentoRobo = 1;
        
        for(int j = 1; j < (QUANTIDADE_ACOES - 1); j++)
        {
            int armazenamentoRoboTemporario = armazenamentoRobo;
            int numColetasTemporario = numColetas;

            //CHECANDO O ATUAL
            if(sequenciaAtual->sequenciaAcoes->at(j) == coleta)
            {
                armazenamentoRoboTemporario++;
                numColetasTemporario++;
            }
            else
            {
                armazenamentoRoboTemporario--;
            }

            //SANITY CHECK - ajusta antes de SEQUER cogitar em mutar
            if(armazenamentoRoboTemporario > ARMAZENAMENTO_ROBO || numColetasTemporario >= QUANTIDADE_PACOTES)
            {
                sequenciaAtual->sequenciaAcoes->at(j) = entrega;

                armazenamentoRobo--;
            }
            else if(armazenamentoRoboTemporario < 0)
            {
                sequenciaAtual->sequenciaAcoes->at(j) = coleta;

                armazenamentoRobo++;
                numColetas++;
            }
            else if(rand() % 100 < TAXA_MUTACAO_SEQUENCIACAO)
            {
                //VAMOS MUTAR!
                //cout << "TO PENSANDO EM MUTAR" << endl;
                switch(sequenciaAtual->sequenciaAcoes->at(j))
                {
                    case coleta:
                        //Vamos trocar a COLETA por uma ENTREGA!
                        //Só é possível caso não esteja vazio
                        if(armazenamentoRobo > 0)
                        {
                            sequenciaAtual->sequenciaAcoes->at(j) = entrega;
                            armazenamentoRobo--;
                        } 
                        else 
                        {
                            armazenamentoRobo = armazenamentoRoboTemporario;
                            numColetas = numColetasTemporario;
                        }
                        break;

                    case entrega:
                        //Vamos trocar a ENTREGA por uma COLETA!
                        //Só é possível caso não esteja cheio
                        if(armazenamentoRobo < ARMAZENAMENTO_ROBO)
                        {
                            sequenciaAtual->sequenciaAcoes->at(j) = coleta;
                            armazenamentoRobo++;
                            numColetas++;
                        } 
                        else 
                        {
                            armazenamentoRobo = armazenamentoRoboTemporario;
                            numColetas = numColetasTemporario;
                        }
                        break;
                }
            }
            else 
            {
                armazenamentoRobo = armazenamentoRoboTemporario;
                numColetas = numColetasTemporario;
            }
        }
    }
}

void PlanejamentoRobo::atualizaPopulacaoAcoes()
{
    this->mutacao();
    
    bool condicaoParaGenocidio = false; //TODO Pensar em quando os genocídios precisam ocorrer

    if(condicaoParaGenocidio) 
    {
        this->genocidio(); 
    }
}

float PlanejamentoRobo::calculaFitness()
{
    for(int i = 0; i < TAMANHO_VETOR_SEQUENCIAACAO; i++) 
    {
        this->fitness[i] = this->sequenciasAcao->at(i)->calculaFitness();
        
        if(this->fitness[i] > this->melhorFitness)
        {
            this->melhorFitness = this->fitness[i];
            this->indiceMelhorCombinacao = i;
        }
    }

    return this->melhorFitness;
}

void PlanejamentoRobo::evoluiNGeracoes(int n) 
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < GERACOES_EVOLUTIVO_INTERNO; j++)
        {
            this->melhorFitnessAnterior = this->melhorFitness;

            this->calculaFitness();

            //Tentando destravar o fitness!
            if(this->melhorFitnessAnterior == this->melhorFitness)
            {
                this->indiceDestravamentoMutacao = this->indiceDestravamentoMutacao + TAXA_MUTACAO_ADICIONAL;
            }
            else
            {
                this->indiceDestravamentoMutacao = 1;
            }

            this->atualizaPopulacaoPacotes();
        }


        this->atualizaPopulacaoAcoes();
    }

    this->printResults();
}

void PlanejamentoRobo::printResults()
{
    //A evolução foi finalizada. Imprimindo resultados.
    cout << "Evolução encerrada!" << endl;
    cout << "SEQUÊNCIA DE AÇÕES:" << endl;

    cout << "(0 para coleta e 1 para entrega)" << endl;
    cout << *(this->sequenciasAcao->at(this->indiceMelhorCombinacao));

    SequenciaAcao *sequenciaAcaoEmQuestao = this->sequenciasAcao->at(this->indiceDestravamentoMutacao);
    SequenciaPacotes *sequenciaPacotesEmQuestao = sequenciaAcaoEmQuestao->sequenciasPacotes->at(sequenciaAcaoEmQuestao->indiceMelhorFitness);
    cout << *sequenciaPacotesEmQuestao;
}