#include "PlanejamentoRobo.h"


PlanejamentoRobo::PlanejamentoRobo(StatusRobo *robo) 
{
    this->melhorFitness = -INFINITY;
    this->sequenciasAcao = new vector<SequenciaAcao*>;
    
    for(int i = 0; i < TAMANHO_VETOR_SEQUENCIAACAO; i++)
    {
        cout << "[PLANEJAMENTOROBO] Antes de criar uma nova SequenciaAcao" << endl;
        this->sequenciasAcao->push_back(new SequenciaAcao(robo));
        cout << "[PLANEJAMENTOROBO] Depois de criar uma nova SequenciaAcao" << endl;
        //TODO encapsular gerar sequencia aleatória no construtor da classe SequenciaAcao
        cout << "[PLANEJAMENTOROBO] Aviso antes de instanciar a sequência de ações aleatória" << endl;
        this->sequenciasAcao->at(i)->sequenciaAcoes = this->geraSequenciaAleatoria();
        cout << "[PLANEJAMENTOROBO] Aviso depois de instanciar a sequência de ações aleatória" << endl;
    }
}

int* PlanejamentoRobo::geraSequenciaAleatoria() 
{
    int quantidadeDeColetas = 0;
    int *acoes = (int*) malloc(QUANTIDADE_ACOES*sizeof(int));

    for(int j = 0; j < QUANTIDADE_ACOES; j++)
    {

        //Armazenamento do robô está cheio
        if(quantidadeDeColetas > ARMAZENAMENTO_ROBO)
        { 
            acoes[j] = entrega;
        } 
        else
        {
            acoes[j] = rand() % 2; 
        }

        if(acoes[j] == coleta)
        { 
            quantidadeDeColetas++;
        }
        else
        { 
            quantidadeDeColetas--;
        }
    
    }

    return acoes;
}

void PlanejamentoRobo::inicializaPlanejamento(StatusRobo *robo)
{
    //TODO excluir isso aqui depois
}

float PlanejamentoRobo::calculaFitness()
{
    cout << "[PLANEJAMENTOROBO] Entrando na função calculaFitness()" << endl;
    for(int i = 0; i < TAMANHO_VETOR_SEQUENCIAACAO; i++) 
    {
        cout << "[PLANEJAMENTOROBO] Antes de calcular o fitness de uma ação!" << endl;
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
    for(int i = 0; i < TAMANHO_VETOR_SEQUENCIAACAO; i++) 
    {
        this->sequenciasAcao->at(i)->atualizaPopulacao();
    }
}

void PlanejamentoRobo::mutacao()
{
    int blocosParaEntregar = 1;

    for(int i = 0; i < TAMANHO_VETOR_SEQUENCIAACAO; i++)
    {
        SequenciaAcao *sequenciaEmQuestao = sequenciasAcao->at(i);

        for(int j = 1; j < QUANTIDADE_ACOES; j++)
        {
            if(sequenciaEmQuestao->sequenciaAcoes[j] == entrega)
            {
                blocosParaEntregar--;
            }
            else
            {
                blocosParaEntregar++;
            }

            if(rand() % 100 < TAXA_MUTACAO_SEQUENCIACAO)
            {
                if(sequenciaEmQuestao->sequenciaAcoes[j] == entrega && blocosParaEntregar < ARMAZENAMENTO_ROBO)
                {
                    if(sequenciaEmQuestao->sequenciaAcoes[j+1] == coleta && blocosParaEntregar + 1 >= ARMAZENAMENTO_ROBO)
                    {   
                        continue;
                    }

                    sequenciaEmQuestao->sequenciaAcoes[j] = coleta;
                    blocosParaEntregar = blocosParaEntregar + 2;
                    
                }
                else if(blocosParaEntregar > 0)
                {
                    if(sequenciaEmQuestao->sequenciaAcoes[j+1] == entrega && blocosParaEntregar - 1 < 1)
                    {   
                        continue;
                    }
                    sequenciaEmQuestao->sequenciaAcoes[j] = entrega;
                    blocosParaEntregar = blocosParaEntregar - 2;
                }
            }
        }
    }
}

void PlanejamentoRobo::genocidio()
{
    //TODO A cada xx iterações, mata todos e cria uma nova população com base nos yy melhores
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

void PlanejamentoRobo::evoluiNGeracoes(int n) 
{
    cout << "[PLANEJAMENTOROBO] Início da Evolução por N gerações" << endl;
    for(int i = 0; i < n; i++)
    {
        cout << "[PLANEJAMENTOROBO] AG Externo - Geração " << i << endl;
        for(int j = 0; j < GERACOES_EVOLUTIVO_INTERNO; j++)
        {
            cout << "[PLANEJAMENTOROBO] Antes de entrar na função calculaFitness()" << endl;
            this->calculaFitness();

            cout << "[PLANEJAMENTOROBO] Antes de entrar na função atualizaPopulacaoPacotes()" << endl;
            this->atualizaPopulacaoPacotes();
        }

        cout << "[PLANEJAMENTOROBO] Antes de entrar na função atualizaPopulacaoAcoes()" << endl;
        this->atualizaPopulacaoAcoes();
    }
}