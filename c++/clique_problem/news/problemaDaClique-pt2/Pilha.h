#ifndef PILHA_H
#define PILHA_H
#include "No.h"

class Pilha
{
    public:
        Pilha();
        ~Pilha();
        float getTopo();
        void empilha(float val);
        float desempilha();
        bool vazia();
    private:
        No* topo;
};

#endif // PILHA_H
