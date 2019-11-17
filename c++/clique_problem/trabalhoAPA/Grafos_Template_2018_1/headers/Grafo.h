#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include "bibliotecas.h"

class Grafo{
    private:
        vector <No> listaNos;

    public:
        string output;
        Grafo();
        ~Grafo();
        bool orderAux(const No& a, const No& b);
        void adcionarNo(int  id,float pesoNo);
        void removerNo(int id);
        void readFile(char *path);
        void readFile2(string path);
        void writeFile(string path, int numClausulas, int numLiterais, int k);
        void showInfo();
        bool noEstaNoGrafo(int index);
        int getOrdemGrafo();
        bool grafoTrivial();
        bool grafoNulo();
        int getGrauNo(int id);
        bool vizinho(int id1, int id2);
        bool grafoCompleto();
        No getNo(int id);
        void removeAresta(int id1, int id2);
        void adicionaAresta(int id1,int id2, float peso);
        void acharCliqueMaxima();
        bool verificaSolucao(vector <No> nosNaSolucao);
        bool formaClique(vector<No>nosNaSolucao, No noCandidato);
        void reduzSat(int valorClique);
        int cliqueMaximaForcaBruta();
};


#endif // GRAFO_H_INCLUDED
