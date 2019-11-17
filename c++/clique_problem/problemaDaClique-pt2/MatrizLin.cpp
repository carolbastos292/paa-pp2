#include "MatrizLin.h"
#include <iostream>
using namespace std;

MatrizLin::MatrizLin(int mm)
{
    nl = mm;
    nc = mm;
    vet = new float[nl*nc];
}

MatrizLin::~MatrizLin()
{
    delete []vet;
}

void MatrizLin::setDimensao(int i)
{
    nl = i;
    nc = i;
    vet = new float[i*i];
}

int MatrizLin::detInd(int i, int j)
{
    if(i >= 0 && i < nl && j >= 0 && j < nc)
        return i*nc + j;
    else
        return -1; // indice invalido
}

float MatrizLin::get(int i, int j)
{
    int k = detInd(i, j);
    if(k != -1)
        return vet[k];
    else {
        cout << "Indice invalido!" << endl;
    }
}

void MatrizLin::set(int i, int j, float val)
{
    int k = detInd(i, j);
    if(k != -1)
    vet[k] = val;
    else
        cout << "Indice invalido!" << endl;
}

void MatrizLin::imprime()
{
    for(int i=0;i<nl;i++)
    {
        for(int j=0;j<nc;j++)
        {
            cout<<get(i,j)<<" ";
        }
        cout<<endl;
    }
}
