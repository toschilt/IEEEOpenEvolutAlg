#ifndef SEQUENCIAPACOTES_H
#define SEQUENCIAPACOTES_H

#define QUANTIDADE_PACOTES  32

#define PACOTE_BRANCO       0
#define PACOTE_PRETO        1
#define PACOTE_AMARELO      2
#define PACOTE_VERMELHO     3
#define PACOTE_VERDE        4
#define PACOTE_AZUL         5

typedef float retornoCalcFitness;

class SequenciaPacotes {
    private:

    public:

    
    retornoCalcFitness calculaFitness(int *sequenciaAcoes);
    
};

#endif