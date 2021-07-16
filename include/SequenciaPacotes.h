#ifndef SEQUENCIAPACOTES_H
#define SEQUENCIAPACOTES_H

#include "Pacote.h"
#include "Constantes.h"

typedef float retornoCalcFitness;

class SequenciaPacotes {
    private:

    public:

    vector<Pacote*> *sequenciaPacotes;

    retornoCalcFitness calculaFitness(int *sequenciaAcoes);

    SequenciaPacotes(vector<Pacote*> *sequencia);
    
};


#endif