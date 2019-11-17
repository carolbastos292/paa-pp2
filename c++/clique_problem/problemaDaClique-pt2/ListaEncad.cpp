#include "ListaEncad.h"
#include <iostream>
using namespace std;
ListaEncad::ListaEncad()
{
    primeiro = NULL;
}

ListaEncad::~ListaEncad()
{
    Aresta *p = primeiro;
    while(p != NULL){
        Aresta* t = p->getProx();
        delete p;
        p = t;
    }
}

void ListaEncad::insereFinal(int id)
{
    Aresta* p = new Aresta();
    Aresta* t = primeiro;
    p->setId(id);

    if(t == NULL){
        primeiro = p;
        p->setProx(NULL);
    }else{
        while(t->getProx() != NULL){
            t = t->getProx();
            t->setProx(p);
            p->setProx(NULL);
        }
    }
}

bool ListaEncad::busca(int id)
{
    Aresta* p = primeiro;
    while(p!=NULL){
        if(p->getId()){

        }
    }
}

void ListaEncad::imprime()
{
    Aresta* p = primeiro;
    while(p!=NULL){
        cout<< p->getId() << " ";
        p = p->getProx();
    }
}

void ListaEncad::retira(int id)
{
    Aresta* p = primeiro;
    Aresta* aux = NULL;

    while(p!=NULL){
        if(p->getId() == id)
            break;
        aux = p;
        p = p->getProx();
    }
    if(aux == NULL){
        primeiro = primeiro->getProx();
        delete p;
    }else{
        if(p == NULL){
            aux = NULL;
            delete p;
        }else{
            aux->setProx(p->getProx());
            delete p;
        }
    }
}
