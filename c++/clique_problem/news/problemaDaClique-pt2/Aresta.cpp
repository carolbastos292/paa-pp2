#include "Aresta.h"

Aresta::Aresta(){}

Aresta::~Aresta(){}

int Aresta::getId()
{
    return id;
}
void Aresta::setId(int id)
{
    this-> id = id;
}
Aresta* Aresta::getProx()
{
    return prox;
}
void Aresta::setProx(Aresta* p)
{
    prox = p;
}
int Aresta::getPeso()
{
    return this->peso;
}
void Aresta::setPeso(int peso)
{
    this->peso = peso;
}
