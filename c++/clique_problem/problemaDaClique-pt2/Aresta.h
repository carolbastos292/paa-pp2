#ifndef ARESTA_H
#define ARESTA_H


class Aresta
{
    public:
        Aresta();
        ~Aresta();
        int getId();
        void setId(int id);
        Aresta* getProx();
        void setProx(Aresta* p);
        int getPeso();
        void setPeso(int peso);

    private:
        int id;
        int peso;
        Aresta* prox;

};

#endif // ARESTA_H
