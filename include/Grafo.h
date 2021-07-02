#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <string>
#include <unordered_map>
#include "CoordR2.h"

using namespace std;

class Grafo
{
    private:
        //Tabela hash que contém como chave uma coordenada em string e como conteúdo a lista de coordenadas adjacentes
        std::unordered_map<string, vector<CoordR2>> grafo;
        //Guarda a plataforma fornecida no txt
        vector<string> plataforma;
        //Guarda dimensões da plataforma - primeiro o número de linhas, segundo o número de colunas
        int dim[2];

    public:
    
        //Métodos construtor
        Grafo(const char nome_arquivo[]);

        Grafo();
        //Função para ler a plataforma
        void Le_Plataforma(const char nome_arquivo[]);
        //Função para printar a plataforma como txt
        void Print_Plataforma_txt();
        //Gera grafo na representação de listas de adjacentes a partir da plataforma lida
        void Gera_Grafo();
        //Printa a estrutura atual do grafo
        void Print_Grafo();
        //Métodos para retornar a lista de adjacentes a partir de um vertice
        vector<CoordR2> Get_Vizinhos(CoordR2 vertice);
        //Gera imagem da plataforma
        void Plataforma_Img();
        //Aplica o algorito de busca em largura a fim de encontrar o caminho mínimo entre dois vértices
        vector<CoordR2> Breadth_First_Search(CoordR2 v_ini, CoordR2 v_fin);     
        //Desenha caminho na imagem da plataforma
        void Caminho_Img(vector<CoordR2> caminho);
};


#endif