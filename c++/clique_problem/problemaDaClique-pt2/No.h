#ifndef No_H_INCLUDED
#define No_H_INCLUDED
#include "Aresta.h"

class No{

private:

    int id; 
    Aresta* primeiro; //cabeça da lista de arestas
    No* prox;
    int num; //ordem em que o no foi add

    ///GRAFO NÃO DIRECIONADO
    int degree; //grau do vertice
    ///GRAFO DIRECIONADO
    int inDegree; //grau de entrada
    int outDegree; //grau de saida

public:
    No();
    ~No();
    int getDegree();
    int getInDegree();
    int getOutDegree();

    void increaseDegree();
    void increaseInDegree();
    void increaseOutDegree();
    void decreaseDegree();
    void decreaseInDegree();
    void decreaseOutDegree();

    int getId();
    void setId(int id);
    No* getProx();
    void setProx(No *p);
    void setNum(int i);
    int getNum();
    
    Aresta* getArestas(); //retorna a cabeça da lista
    void setArestas(Aresta* arestas); //define a cabeça da lista
    void insereAresta(int vert, Aresta* a); //insere a aresta com a outra extremidade em a->getId
    void insereAresta(int vert, Aresta* a, int peso); //insere a aresta com o peso
    void insereArco(int vert2, Aresta* a); //insere arco que tem como cabeça a->getId
    void insereArco(int vert, Aresta* a, int peso); //insere arco com peso
    void retiraAresta(int vert);//retira aresta com o No vert
    void retiraArco(int vert);//retira arco que tem como cabeça vert
    void imprime();

};

#endif // No_H_INCLUDED


