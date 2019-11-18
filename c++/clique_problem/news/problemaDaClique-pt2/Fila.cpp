#include <iostream>
#include "Fila.h"

using namespace std;

Fila::Fila()
{
    c = NULL;
    f = NULL;
}

Fila::~Fila()
{
    No* p = c;

    while(c != NULL){
        c = p->getProx();
        delete p;
        p = c;
    }
}

int Fila::getInicio()
{
    if(c != NULL)
        return c->getId();
        else
            cout << "ERRO";
}

void Fila::enfileira(int id)
{
    No* p = new No();
    p->setId(id);
    p->setProx(NULL);

    if(f == NULL)
        c = p;
        else
            f->setProx(p);
    f = p;
}

int Fila::desenfileira()
{
    No* p;

    if(c != NULL){

        p = c;
        c = p->getProx();

        if(c == NULL)
            f = NULL;

        int val = p->getId();
        delete p;
        return val;
    }

    cout << "Lista vazia";
}

bool Fila::vazia()
{
    if(c == NULL)
        return true;
        else
            return false;
}
