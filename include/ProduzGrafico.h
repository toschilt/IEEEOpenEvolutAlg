#ifndef PRODUZGRAFICO_H
#define PRODUZGRAFICO_H

#include "pbPlots.hpp"
#include "supportLib.hpp"

#include <vector>
#include <string>

using namespace std;

class ProduzGrafico {
    private:
        ProduzGrafico() {}
    
    public:
        static void dataToPng(string nomePNG, vector<double> xs, vector<double> ys);
};

#endif