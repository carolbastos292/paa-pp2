#ifndef LISTAENCAD_H
#define LISTAENCAD_H
#include <iostream>
#include "Aresta.h"

class ListaEncad
{
    public:
        ListaEncad();
        ~ListaEncad();
        void insereFinal(int id);
        bool busca(int id);
        void imprime();
        void retira(int id);;
    private:
        Aresta* primeiro;

};

#endif // LISTAENCAD_H
