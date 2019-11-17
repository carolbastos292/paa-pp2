#include "No.h"
#include <iostream>

using namespace std;

No::No(){

    degree = 0;
    inDegree = 0;
    outDegree = 0;
    primeiro = NULL;

}

No::~No(){

    Aresta *p = primeiro;

    while(p != NULL){
        Aresta *t = p->getProx();
        delete p;
        p = t;
    }
}

int No::getNum(){
    
    return num;

}

void No::setNum(int i){
    
    num = i;
    
}

int No::getId(){

    return id;
}

void No::setId(int id){
    this->id = id;
}

No* No::getProx(){
    return prox;
}

void No::setProx(No* p){
    prox = p;
}

Aresta* No::getArestas(){
    return primeiro;
}

void No::setArestas(Aresta* arestas){
    this->primeiro = arestas;
}

void No::insereAresta(int vert, Aresta* a){

    Aresta* p = primeiro;

    if(primeiro == NULL){
        primeiro = a;
        a->setId(vert);
        a->setProx(NULL);
    }else{
        primeiro = a;
        a->setId(vert);
        a->setProx(p);
    }

    increaseDegree();
}

void No::insereArco(int vert, Aresta* a){

    Aresta* p = primeiro;

    if(primeiro == NULL){
        primeiro = a;
        a->setId(vert);
        a->setProx(NULL);
    }else{
        primeiro = a;
        a->setId(vert);
        a->setProx(p);
    }
}

void No::insereAresta(int vert, Aresta* a, int peso){

    Aresta* p = primeiro;

    if(primeiro == NULL){
        primeiro = a;
        a->setPeso(peso);
        a->setId(vert);
        a->setProx(NULL);
    }else{
        primeiro = a;
        a->setPeso(peso);
        a->setId(vert);
        a->setProx(p);
    }
}

void No::insereArco(int vert, Aresta* a, int peso){

    Aresta* p = primeiro;

    if(primeiro == NULL){
        primeiro = a;
        a->setPeso(peso);
        a->setId(vert);
        a->setProx(NULL);
    }else{
        primeiro = a;
        a->setPeso(peso);
        a->setId(vert);
        a->setProx(p);
    }

    increaseOutDegree();
}

void No::retiraAresta(int vert2)
{
    Aresta* p = primeiro;
    Aresta* aux = NULL;

    if(p == NULL){
        cout << "Aresta inexistente ! No " << id << "nao possui nenhuma aresta !" ;
    }


    while(p != NULL){
        if(p->getId() == vert2)
            break;
        aux = p;
        p = p->getProx();
    }

    if(aux == NULL){
        primeiro = primeiro->getProx();
        delete p;
    }else{
        aux->setProx(p->getProx());
        delete p;
    }

    decreaseDegree();
}

void No::retiraArco(int vert2)
{
    Aresta* p = primeiro;
    Aresta* aux = NULL;

    if(p == NULL){
        cout << "Arco inexistente ! No " << id << "nao possui nenhum arco !" ;
    }

    while(p != NULL){
        if(p->getId() == vert2)
            break;
        aux = p;
        p = p->getProx();
    }

    if(aux == NULL){
        primeiro = primeiro->getProx();
        delete p;
    }else{
        aux->setProx(p->getProx());
        delete p;
    }

    decreaseOutDegree();
}

void No::imprime(){

    Aresta *p = primeiro;

    while(p != NULL){
        cout << p->getId() << " ";
        p = p->getProx();
    }
}

int No::getDegree(){

    return degree;
}

int No::getInDegree()
{
    return inDegree;
}

int No::getOutDegree()
{
    return outDegree;
}

void No::increaseDegree()
{
    degree++;
}

void No::increaseInDegree()
{
    inDegree++;
}

void No::increaseOutDegree()
{
    outDegree++;
}

void No::decreaseDegree()
{
    degree--;
}

void No::decreaseInDegree()
{
    inDegree--;
}

void No::decreaseOutDegree()
{
    outDegree--;
}

