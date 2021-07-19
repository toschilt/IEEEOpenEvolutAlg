#include "SequenciaAcao.h"

SequenciaAcao::SequenciaAcao(StatusRobo *robo) 
{
    sequenciasPacotes = new vector<SequenciaPacotes*>;
    sequenciaAcoes = new vector<int>;
    
    //Gera sequências de blocos aleatórias
    for(int i = 0; i < TAMANHO_VETOR_SEQUENCIAPACOTES; i++)
    {
        vector<Pacote*> *novaSequencia = new vector<Pacote*>;
        *novaSequencia = *(robo->pacotesDisponiveis);
        //cout << "[SEQUENCIAACAO] Tamanho da novaSequencia: " << novaSequencia->size() << endl;
        shuffle(novaSequencia->begin(), novaSequencia->end(), std::default_random_engine(rand()));

        SequenciaPacotes *novaSequenciaPacotes = new SequenciaPacotes(novaSequencia, robo->grafoCenario);
        this->sequenciasPacotes->push_back(novaSequenciaPacotes);
    }

    this->posInicial = robo->posInicial;
    this->grafoCenario = robo->grafoCenario;
    this->indiceMelhorFitness = -1;
    this->melhorFitness = -INFINITY;
}

float SequenciaAcao::calculaFitness()
{
    //cout << "[SEQUENCIAACAO] Entrou na função calculaFitness!" << endl;
    //Passa por toda a sequência, calcula os fitness individuais, e salva o melhor
    this->melhorFitness = -INFINITY;

    for(int i = 0; i < TAMANHO_VETOR_SEQUENCIAPACOTES; i++)
    {
        //cout << "[SEQUENCIAACAO] Antes de calcular o fitness de uma sequência de pacotes!" << endl;
        this->fitness[i] = this->sequenciasPacotes->at(i)->calculaFitness(this->sequenciaAcoes, posInicial);
        //cout << "Fitness sequencia pacote " << i << ": " << this->fitness[i] << endl;
        if(this->fitness[i] > this->melhorFitness)
        {
            this->melhorFitness = this->fitness[i];
            this->indiceMelhorFitness = i;
        }
    }

    cout << "Melhor sequencia de pacotes: " << this->melhorFitness << endl;
    return this->melhorFitness;
}

void SequenciaAcao::atualizaPopulacao()
{
    //cout << "Atualiza População Sequencia Pacotes" << endl;
    this->crossover();
    this->mutacao();
}


void SequenciaAcao::crossover()
{
    //ESTAMOS USANDO ELITISMO
    vector<SequenciaPacotes*> *novaPopulacao = new vector<SequenciaPacotes*>;

    vector<Pacote*> *genesMelhorDeTodos = sequenciasPacotes->at(indiceMelhorFitness)->sequenciaPacotes;
    for(int i = 0; i < TAMANHO_VETOR_SEQUENCIAPACOTES; i++)
    {
        //TODO se ficar muito pesado, pensar em como melhorar isso aqui
        if(i == indiceMelhorFitness)
        {
            continue;
        }

        vector<Pacote*> *novaSequenciaGenes = new vector<Pacote*>;

        for(int j = 0; j < QUANTIDADE_PACOTES; j++)
        {
            if(rand() % 100 < TAXA_CROSSOVER_SEQUENCIAPACOTES)
            {
                novaSequenciaGenes->push_back(genesMelhorDeTodos->at(j));
            }
            else
            {
                novaSequenciaGenes->push_back(sequenciasPacotes->at(i)->sequenciaPacotes->at(j));
            }
        }

        SequenciaPacotes *novoIndividuo = new SequenciaPacotes(novaSequenciaGenes, grafoCenario);
        novaPopulacao->push_back(novoIndividuo);
    }

    novaPopulacao->push_back(sequenciasPacotes->at(indiceMelhorFitness));
    sequenciasPacotes = novaPopulacao;
    //TODO cuidar de garbage collect depois
}


void SequenciaAcao::mutacao()
{
    //Vai até TAMANHO_VETOR_SEQUENCIAPACOTES - 1 pq no crossover garantimos que o melhor de todos
    //está por último!
    for(int i = 0; i < TAMANHO_VETOR_SEQUENCIAPACOTES - 1; i++)
    {
        for(int j = 0; j < QUANTIDADE_PACOTES; j++) 
        {
            //float taxaMutacaoFinal = TAXA_MUTACAO_SEQUENCIAPACOTES * (1 - this->fitness[j]);

            if(rand() % 100 < TAXA_MUTACAO_SEQUENCIAPACOTES) 
            {
                int indiceTroca = rand() % QUANTIDADE_PACOTES;
                
                Pacote *pacote1 = this->sequenciasPacotes->at(i)->sequenciaPacotes->at(indiceTroca);
                Pacote *pacote2 = this->sequenciasPacotes->at(i)->sequenciaPacotes->at(j);
                Pacote *aux = pacote1;
                pacote1 = pacote2;
                pacote2 = aux;
            }
        }
    }
}

bool SequenciaAcao::coinflip(float probabilidadeSucesso) 
{
    int flip = rand() % 100;
    if(flip > probabilidadeSucesso)
    { 
        return false; 
    }
    
    return true;
}