#include "PlanejamentoRobo.h"


PlanejamentoRobo::PlanejamentoRobo(StatusRobo *robo) 
{
    this->melhorFitness = -INFINITY;
    this->sequenciasAcao = new vector<SequenciaAcao*>;
    
    for(int i = 0; i < TAMANHO_VETOR_SEQUENCIAACAO; i++)
    {
        // cout << "[PLANEJAMENTOROBO] Antes de criar uma nova SequenciaAcao" << endl;
        this->sequenciasAcao->push_back(new SequenciaAcao(robo));
        // cout << "[PLANEJAMENTOROBO] Depois de criar uma nova SequenciaAcao" << endl;
        //TODO encapsular gerar sequencia aleatória no construtor da classe SequenciaAcao
        // cout << "[PLANEJAMENTOROBO] Aviso antes de instanciar a sequência de ações aleatória" << endl;
        this->geraSequenciaAleatoria(this->sequenciasAcao->at(i)->sequenciaAcoes);
        // cout << "[PLANEJAMENTOROBO] Aviso depois de instanciar a sequência de ações aleatória" << endl;
    }
}

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

void PlanejamentoRobo::inicializaPlanejamento(StatusRobo *robo)
{
    //TODO excluir isso aqui depois
}

float PlanejamentoRobo::calculaFitness()
{
    // cout << "[PLANEJAMENTOROBO] Entrando na função calculaFitness()" << endl;
    for(int i = 0; i < TAMANHO_VETOR_SEQUENCIAACAO; i++) 
    {
        // cout << "[PLANEJAMENTOROBO] Antes de calcular o fitness de uma ação!" << endl;
        this->fitness[i] = this->sequenciasAcao->at(i)->calculaFitness();
        
        if(this->fitness[i] > this->melhorFitness)
        {
            this->melhorFitness = this->fitness[i];
            this->indiceMelhorCombinacao = i;
        }
    }

    return this->melhorFitness;
}

void PlanejamentoRobo::atualizaPopulacaoPacotes()
{
    // cout << "[PLANEJAMENTOROBO] Entrou na função atualizaPopulacaoPacotes()" << endl;
    for(int i = 0; i < TAMANHO_VETOR_SEQUENCIAACAO; i++) 
    {
        // cout << "[PLANEJAMENTOROBO] (Iteração " << i << "). Antes de atualizar as sequências de ação" << endl;
        this->sequenciasAcao->at(i)->atualizaPopulacao();
    }
    // cout << "[PLANEJAMENTOROBO] Saiu da função atualizaPopulacaoPacotes()" << endl;
}


void PlanejamentoRobo::mutacao()
{

    for(int i = 0; i < TAMANHO_VETOR_SEQUENCIAACAO; i++)
    {
        SequenciaAcao *sequenciaAtual = sequenciasAcao->at(i);

        //for(int pintoGRANDE = 0; pintoGRANDE < QUANTIDADE_ACOES; pintoGRANDE++) {
            //cout << sequenciaAtual->sequenciaAcoes->at(pintoGRANDE) << " ";
        //}
        //cout << endl;

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
                //cout << "sanitycheck case 1 - j = " << j << endl;
                sequenciaAtual->sequenciaAcoes->at(j) = entrega;

                armazenamentoRobo--;
            }
            else if(armazenamentoRoboTemporario < 0)
            {
                //cout << "sanitycheck case 2 - j = " << j << endl;
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
                            //cout << "MUTEI CARALHO BIRRRRR em j = " << j << endl;
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
                            //cout << "MUTEI CARALHO BIRRRRR em j = " << j << endl;
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

        //for(int pintoGRANDE = 0; pintoGRANDE < QUANTIDADE_ACOES; pintoGRANDE++) {
            //cout << sequenciaAtual->sequenciaAcoes->at(pintoGRANDE) << " ";
        //}
        //cout << endl;
    }
}


void PlanejamentoRobo::genocidio()
{
    //TODO A cada xx iterações, mata todos e cria uma nova população com base nos yy melhores
}

void PlanejamentoRobo::atualizaPopulacaoAcoes()
{
    //cout << "Atualiza População Sequencia Acao" << endl;
    this->mutacao();
    //cout << "Saiu da mutação" << endl;
    
    bool condicaoParaGenocidio = false; //TODO Pensar em quando os genocídios precisam ocorrer

    if(condicaoParaGenocidio) 
    {
        this->genocidio(); 
    }
}

void PlanejamentoRobo::evoluiNGeracoes(int n) 
{
    // cout << "[PLANEJAMENTOROBO] Início da Evolução por N gerações" << endl;
    for(int i = 0; i < n; i++)
    {
        // cout << "[PLANEJAMENTOROBO] AG Externo - Geração " << i << endl;
        for(int j = 0; j < GERACOES_EVOLUTIVO_INTERNO; j++)
        {
            // cout << "[PLANEJAMENTOROBO] Antes de entrar na função calculaFitness()" << endl;
            this->calculaFitness();

            cout << "Iteração " << j << ": Melhor fitness INTERNO: " << melhorFitness << endl;

            // cout << "[PLANEJAMENTOROBO] Antes de entrar na função atualizaPopulacaoPacotes()" << endl;
            this->atualizaPopulacaoPacotes();
        }

        cout << "Iteração " << i << ": Melhor fitness EXTERNO: " << melhorFitness << endl;

        // cout << "[PLANEJAMENTOROBO] Antes de entrar na função atualizaPopulacaoAcoes()" << endl;
        this->atualizaPopulacaoAcoes();
    }
}