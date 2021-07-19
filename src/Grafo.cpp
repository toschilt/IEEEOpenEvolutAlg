#include "CoordR2.h"
#include "Grafo.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>

using namespace  std;

void Grafo::Le_Plataforma(const char nome_arquivo[])
{
    string lineAux;

    ifstream myfile(nome_arquivo);

    if (myfile.is_open()) //Checa se o arquivo foi aberto com sucesso
    {
        int cont = 0;
        while (!myfile.eof()) //enquanto end of file for false continua
        {
            getline(myfile, lineAux); // como foi aberto em modo texto(padrão) e não binário(ios::bin) pega cada linha
            //Pegando as dimensões da plataforma na primeira linha
            if(cont == 0)
            {
                int aux = lineAux.find(" ");
                dim[0] = stoi(lineAux.substr(0,aux));
                dim[1] = stoi(lineAux.substr(aux+1,lineAux.size()-1)); 
            }
            //Unindo linha com linha gerando a plataforma no formato txt
            if(cont != 0)
            {
                plataforma.push_back(lineAux);
            }
            cont++;
        }
        myfile.close();
        return;
    }

    else
    {
        // cout << "Não foi possível abrir o arquivo txt!\n";
    }
    return;
}

void Grafo:: Gera_Grafo()
{
    for (int row = 0; row < dim[0]; row++)
    {
        for (int col = 0; col < dim[1]; col++)
        {
            if(plataforma[row][col] == '-')
            {
                CoordR2 adj_indices[4] = {CoordR2(col+1,row),CoordR2(col,row+1),CoordR2(col-1,row),CoordR2(col,row-1)};
                vector<CoordR2> adj_list;
                for (int k = 0; k < 4; k++)
                {
                    if( (adj_indices[k].x>=0) &&  (adj_indices[k].x<dim[1]) && (adj_indices[k].y>=0) && (adj_indices[k].y<dim[0]))
                        if(plataforma[adj_indices[k].y][adj_indices[k].x] == '-')
                            adj_list.push_back(adj_indices[k]);
                }
                grafo[to_string(col) + "," + to_string(row)] = adj_list;
            }
        }
    }
    
}


Grafo::Grafo(const char nome_arquivo[]){
    Le_Plataforma(nome_arquivo);
}

Grafo::Grafo(){
    // cout << "Grafo Inicializado! " << endl;
}

void Grafo::Print_Plataforma_txt(){
    for (int i = 0; i < dim[0]; i++)
    {
        // cout<<plataforma[i]<<endl;
    }
    
    return;
}

void Grafo::Print_Grafo()
{
    // cout << "Total de vertices: " << grafo.size() << endl;
    for (auto& it: grafo)
    {
        // cout << "(" << it.first << ") : ";
        for (int i = 0; i < it.second.size(); i++)
        {
            // cout << it.second[i] << " ";
        }
        // cout << endl;
    }
}

vector<CoordR2> Grafo::Get_Vizinhos(CoordR2 vertice)
{
    string key = to_string(int(vertice.x)) + "," + to_string(int(vertice.y));
    vector<CoordR2> list_adj;
    if(grafo.find(key) != grafo.end())
    {
        list_adj = grafo.at(key);
    }
    else
    {
     // cout << "Vertice nao existe!" << endl;   
    }
    return list_adj;
}

/*void Grafo::Plataforma_Img()
{
    cv::namedWindow("Plataforma",cv::WINDOW_NORMAL);
    cv::Mat Img (dim[0],dim[1],CV_8UC3, cv::Scalar(255,255,255));
    for (int i = 0; i < dim[0]; i++)
    {
        for (int j = 0; j < dim[1]; j++)
        {
            if(plataforma[i][j] == '*')
                Img.at<cv::Vec3b>(i,j) = cv::Vec3b(150,150,150);
            if(plataforma[i][j] == 'b')
                Img.at<cv::Vec3b>(i,j) = cv::Vec3b(255,0,0);
            if(plataforma[i][j] == 'g')
                Img.at<cv::Vec3b>(i,j) = cv::Vec3b(0,255,0);
            if(plataforma[i][j] == 'r')
                Img.at<cv::Vec3b>(i,j) = cv::Vec3b(0,0,255);
            if(plataforma[i][j] == 'y')
                Img.at<cv::Vec3b>(i,j) = cv::Vec3b(0,255,255);
        }
        
    }
    cv::imshow("Plataforma",Img);
    cv::waitKey();
}*/

vector<CoordR2> Grafo::Breadth_First_Search(CoordR2 v_ini, CoordR2 v_fin)
{
    //Checa se os vertices de ini e fim existem:
    vector<CoordR2> vizinhos_ini, vizinhos_fim;
    vizinhos_ini = Get_Vizinhos(v_ini);
    vizinhos_fim = Get_Vizinhos(v_fin);
    if(vizinhos_ini.empty())
    {
        // cout << "Vertice inicial nao existe!" << endl;
        return vizinhos_ini;
    }
    if(vizinhos_fim.empty())
    {
        // cout << "Vertice final nao existe!" << endl;
        return vizinhos_fim;
    }
    //Fila que guardará lista de caminhos com vértices a serem visitados
    queue<vector<CoordR2>> fila;
    vector<CoordR2> ini_fila;
    ini_fila.push_back(v_ini);
    fila.push(ini_fila);
    //Guardará vértices visitados com sua profundidade
    vector<CoordR2> visitados;
    //Guarda o caminho entre os pontos
    vector<CoordR2> caminho;
    //Enquanto existir caminhos na fila
    while (!fila.empty())
    {
        //Pega o primeiro caminho na fila, removendo-o de tal
        caminho = fila.front();
        fila.pop();
        //Pega o último vértice do caminho (vértice que será analisado)
        CoordR2 vertice = caminho.back();
        //// cout << "Vertice atual: " << vertice << endl;
        //Checa se tal vértice não é o vértice final (saída do labirinto)
        if(vertice == v_fin)
        {
            //Se for significa que já achamos o caminho
            return caminho;
        }
        else //se não achamos o vertice final
        {
            //booleando que checará se o vertice atual ja foi visitado
            bool foiVisitado = false;
            for (int i = 0; i < visitados.size(); i++)
            {
                if(vertice == visitados[i])
                    foiVisitado = true;
            }
            //Se nao foi visitado, temos que visita-lo
            if(!foiVisitado)
            {
                //Pega os vizinhos
                vector<CoordR2> vizinhos = Get_Vizinhos(vertice);
                for (int i = 0; i < vizinhos.size(); i++)
                {
                    //// cout << "Vizinhos: " << vizinhos[i] << endl;
                    //Gera novo caminho tomando o caminho antigo e insirindo o vizinho no final
                    vector<CoordR2> novo_caminho = caminho;
                    novo_caminho.push_back(vizinhos[i]);
                    //Insere o caminho na fila
                    fila.push(novo_caminho);
                }
                //Marca como visitado
                visitados.push_back(vertice);
            }
        }
    }
}

/*void Grafo::Caminho_Img(vector<CoordR2> caminho)
{
    cv::namedWindow("Plataforma",cv::WINDOW_NORMAL);
    cv::Mat Img (dim[0],dim[1],CV_8UC3, cv::Scalar(255,255,255));
    for (int i = 0; i < dim[0]; i++)
    {
        for (int j = 0; j < dim[1]; j++)
        {
            if(plataforma[i][j] == '*')
                Img.at<cv::Vec3b>(i,j) = cv::Vec3b(150,150,150);
            if(plataforma[i][j] == 'b')
                Img.at<cv::Vec3b>(i,j) = cv::Vec3b(255,0,0);
            if(plataforma[i][j] == 'g')
                Img.at<cv::Vec3b>(i,j) = cv::Vec3b(0,255,0);
            if(plataforma[i][j] == 'r')
                Img.at<cv::Vec3b>(i,j) = cv::Vec3b(0,0,255);
            if(plataforma[i][j] == 'y')
                Img.at<cv::Vec3b>(i,j) = cv::Vec3b(0,255,255);
        }
    }

    for (int i = 0; i < caminho.size(); i++)
    {
        Img.at<cv::Vec3b>(int(caminho[i].y),int(caminho[i].x)) =  cv::Vec3b(150,255,0);
    }
    
    cv::imshow("Plataforma",Img);
    cv::waitKey();
}*/