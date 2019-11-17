#ifndef GRAFO_H
#define GRAFO_H
#include "No.h"
#include "Pilha.h"
#include "Fila.h"
#include "MatrizLin.h"
//#include "ListaEncad.cpp"

class Grafo
{
    private:
        int numVertices;
        int numArestas;
        int numArcos;
        No* primeiro; //primeiro No do grafo
        MatrizLin* adj; //matriz de adjacencia
        //ListaEncad* ListAdj; //lista de adjacencia

    public:
        Grafo();
        ~Grafo();

        ///Busca No e Aresta
        Aresta* buscaAresta(int no1,int no2); //retorna aresta entre os 2 nós passsados por parâmetro
        No* buscaNo(int id); //retorna nó identificado pelo id
        int buscaId(int num); //retorna a id baseado na ordem de inserção dos vertices

        bool ehDirecionado;
        
        ///Manipulacao de MatrizAdj
        void preencheMatrizAdj();

        ///imprime todos os vertices e arestas
        void imprimeVertices();
        void imprimeArestas();

        ///insercao de vertices e arestas
        void insereAresta(int no1,int no2,int peso);
        void insereAresta(int no1,int no2);
        void insereVertice(int id);
        void insereArco(int no1, int no2, int peso);

        ///remocao de vertices e arestas
		void removeAresta(int no1, int no2);
		void removeArco(int no1, int no2);
        void removeNo(int no);

        int grauDoGrafo(); //retorna grau do grafo
        void complementaGrafo(); //transforma grafo atual em seu complementar

        ///Grafo nao direcionado
        int getVerticeDegree(int id); //grau do vertice passado por parametro

        ///Grafo direcionado
        int getVerticeInDegree(int id); //grau de entrada
        int getVerticeOutDegree(int id); //grau de saida


//        ///Busca em Profundidade
//        void deepFirstSearch();
//
//        ///Busca em Largura
//        void breadthFirstSearch();
//
//        ///Auxiliares
//        void dfs(No* p,int* vetorMarcacao);

};

#endif // GRAFO_H

