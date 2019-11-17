#include "Pilha.h"
#include <iostream>
using namespace std;
Pilha::Pilha()
{
    topo = NULL;
}

Pilha::~Pilha()
{
    No* p = topo;
    while(topo != NULL){
        topo = p->getProx();
        delete p;
        p = topo;
    }
}
float Pilha::getTopo()
{
    if(topo != NULL){
        return topo->getId();
    }else{
        cout<< "Erro! Pilha vazia" << endl;
    }
}

void Pilha::empilha(float val)
{
    No* p = new No();
    p->setId(val);
    p->setProx(topo);
    topo = p;
}

float Pilha::desempilha()
{
    No* p;
    float val;
    if(topo != NULL){
        p = topo;
        topo = p->getProx();
        val = p->getId();
        delete p;
    }else{
        cout<< "Erro!" << endl;
    }
    return val;
}

bool Pilha::vazia()
{
    return (topo == NULL);
}
