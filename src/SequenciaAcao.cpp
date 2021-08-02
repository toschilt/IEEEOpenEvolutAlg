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
    //Passa por toda a sequência, calcula os fitness individuais, e salva o melhor
    this->melhorFitness = -INFINITY;

    for(int i = 0; i < TAMANHO_VETOR_SEQUENCIAPACOTES; i++)
    {
        this->fitness[i] = this->sequenciasPacotes->at(i)->calculaFitness(this->sequenciaAcoes, posInicial);

        if(this->fitness[i] > this->melhorFitness)
        {
            this->melhorFitness = this->fitness[i];
            this->indiceMelhorFitness = i;
        }
    }

    return this->melhorFitness;
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

void SequenciaAcao::crossover()
{
    //cout << "Entrei na função crossover!" << endl;
    //ESTAMOS USANDO ELITISMO
    vector<SequenciaPacotes*> *novaPopulacao = new vector<SequenciaPacotes*>;

    vector<Pacote*> *genesMelhorDeTodos = sequenciasPacotes->at(indiceMelhorFitness)->sequenciaPacotes;
    for(int i = 0; i < TAMANHO_VETOR_SEQUENCIAPACOTES; i++)
    {
        //TODO se ficar muito pesado, pensar em como melhorar isso aqui
        if(i == indiceMelhorFitness)
        {
            //cout << "Salvei melhor de todos" << endl;
            continue;
        }

        SequenciaPacotes *sequenciaPacotesEmQuestao = this->sequenciasPacotes->at(i);
        vector<Pacote*> *novaSequenciaGenes = new vector<Pacote*>;
        set<Pacote*> pacotesConsiderados;

        int indiceMelhorTodos = 0;
        int indiceIndividuo = 0;

        while(pacotesConsiderados.size() < QUANTIDADE_PACOTES &&
              indiceMelhorTodos < QUANTIDADE_PACOTES && 
              indiceIndividuo < QUANTIDADE_PACOTES)
        {
            if(indiceIndividuo >= QUANTIDADE_PACOTES || rand() % 100 < TAXA_CROSSOVER_SEQUENCIAPACOTES)
            {
                //Pegando do melhor de todos!
                while(indiceMelhorTodos < QUANTIDADE_PACOTES && 
                      pacotesConsiderados.find(genesMelhorDeTodos->at(indiceMelhorTodos)) != pacotesConsiderados.end())
                {
                    indiceMelhorTodos++;
                } 
                
                if(indiceMelhorTodos < QUANTIDADE_PACOTES) {
                    novaSequenciaGenes->push_back(genesMelhorDeTodos->at(indiceMelhorTodos));
                    pacotesConsiderados.insert(genesMelhorDeTodos->at(indiceMelhorTodos));
                }
            }
            else
            {
                //Pegando do indivíduo em questão!
                while(indiceIndividuo < QUANTIDADE_PACOTES &&
                      pacotesConsiderados.find(sequenciaPacotesEmQuestao->sequenciaPacotes->at(indiceIndividuo)) != pacotesConsiderados.end())
                {
                    indiceIndividuo++;
                } 

                if(indiceIndividuo < QUANTIDADE_PACOTES) {
                    novaSequenciaGenes->push_back(sequenciaPacotesEmQuestao->sequenciaPacotes->at(indiceIndividuo));
                    pacotesConsiderados.insert(sequenciaPacotesEmQuestao->sequenciaPacotes->at(indiceIndividuo));
                }
            }
        }

        SequenciaPacotes *novoIndividuo = new SequenciaPacotes(novaSequenciaGenes, grafoCenario);
        novaPopulacao->push_back(novoIndividuo);
    }

    novaPopulacao->push_back(sequenciasPacotes->at(indiceMelhorFitness));
    this->sequenciasPacotes = novaPopulacao;

    /*for(int i = 0; i < this->sequenciasPacotes->size(); i++)
    {
        //cout << *(this->sequenciasPacotes->at(i)) << endl;
        cout << *(novaPopulacao->at(i)) << endl;
        cout << "AAAAAAAAAAAAA ODEIO SERVIÇO DE TELEFONIA MÓVEL PEREÇA AGORA MESMO" << endl;
    }*/
}

void SequenciaAcao::mutacao(int indiceDestravamentoMutacao)
{
    //Vai até TAMANHO_VETOR_SEQUENCIAPACOTES - 1 pq no crossover garantimos que o melhor de todos
    //está por último!
    for(int i = 0; i < TAMANHO_VETOR_SEQUENCIAPACOTES - 1; i++)
    {
        for(int j = 0; j < QUANTIDADE_PACOTES; j++) 
        {
            if(rand() % 100 < TAXA_MUTACAO_SEQUENCIAPACOTES*indiceDestravamentoMutacao) 
            {
                int indiceTroca = rand() % QUANTIDADE_PACOTES;
                
                Pacote **pacote1 = &(this->sequenciasPacotes->at(i)->sequenciaPacotes->at(indiceTroca));
                Pacote **pacote2 = &(this->sequenciasPacotes->at(i)->sequenciaPacotes->at(j));
                Pacote **aux = pacote1;
                pacote1 = pacote2;
                pacote2 = aux;
            }
        }
    }
}

bool SequenciaAcao::calculoCondicaoGenocidio() {
    int counter = 0;
    for(int i = 0; i < TAMANHO_VETOR_SEQUENCIAPACOTES; i++) {
        if(this->sequenciasPacotes->at(i)->fitness == melhorFitness) {
            counter++;
        }
    }
    return counter > QUANTIDADE_CONDICAO_GENOCIDIO;
}

bool SequenciaAcao::genocidio() {
    if(calculoCondicaoGenocidio()) {
        cout << "Entrei no genocidio" << endl;
        bool melhorDeTodosSalvo = false;

        for(int i = 0; i < TAMANHO_VETOR_SEQUENCIAPACOTES; i++) {
            if(!melhorDeTodosSalvo && this->sequenciasPacotes->at(i)->fitness == melhorFitness) {
                melhorDeTodosSalvo = true;
                continue;
            }

            vector<Pacote*> *novaSequencia = new vector<Pacote*>;
            *novaSequencia = *(this->sequenciasPacotes->at(i)->sequenciaPacotes);
            
            this->sequenciasPacotes->erase(this->sequenciasPacotes->begin() + i);
            shuffle(novaSequencia->begin(), novaSequencia->end(), std::default_random_engine(rand()));

            SequenciaPacotes *novaSequenciaPacotes = new SequenciaPacotes(novaSequencia, this->grafoCenario);
            this->sequenciasPacotes->push_back(novaSequenciaPacotes);
        }
        return true;
    }
    return false;
}

void SequenciaAcao::atualizaPopulacao(int indiceDestravamentoMutacao)
{
    if(!this->genocidio()) {
        this->crossover();
        this->mutacao(indiceDestravamentoMutacao);
    }
}

ostream& operator<<(ostream& os, const SequenciaAcao& acoes)
{
    for(int i = 0; i < TAMANHO_VETOR_SEQUENCIAACAO; i++)
    {
        os << acoes.sequenciaAcoes->at(i) << " ";
        
    }

    os << endl;
    
    return os;
}