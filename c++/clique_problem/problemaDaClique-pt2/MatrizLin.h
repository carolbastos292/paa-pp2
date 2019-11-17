#ifndef MATRIZLIN_H
#define MATRIZLIN_H


class MatrizLin
{
    public:
        MatrizLin(int);
        ~MatrizLin();
        void set(int i,int j, float val);
        float get(int i,int j);
        void imprime();
        void setDimensao(int i);
        int nl,nc;
        float *vet;
        int detInd(int i,int j);
};

#endif // MATRIZLIN_H
