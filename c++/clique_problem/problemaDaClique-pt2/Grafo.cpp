#include "Grafo.h"
#include <iostream>
using namespace std;

Grafo::Grafo()
{
    numVertices = 0;
    numArestas = 0;
    numArcos = 0;
    ehDirecionado = false;
    primeiro = NULL;
}

Grafo::~Grafo()
{
    No *p = primeiro;

    while(p != NULL){
        No *t = p->getProx();
        delete p;
        p = t;
    }
}

///Manipulacao Matriz de Adjacencia
void Grafo::preencheMatrizAdj(){
    adj = new MatrizLin(numVertices);
    No* p;
    int l,c;
    for(int i=0; i<numVertices; i++){
        l=buscaId(i);
        for(int j=0; j<numVertices; j++){
            c=buscaId(j);
            if(c!=(-1) && l!=(-1)){
                if(buscaAresta(c, l)==NULL)
                    adj->set(i, j, 0);
                else
                    adj->set(i, j, 1);
            }
        }
    }
}

/// Algoritmos de Impressao

void Grafo::imprimeVertices(){
    No *p = primeiro;
    while(p != NULL){
        cout << p->getId() << "( "<<p->getNum()<< " )"<< "  , ";
        p = p->getProx();
    }
    cout<<endl;
}

void Grafo::imprimeArestas(){
    No *p = primeiro;
    cout << "LISTA DE ADJACENCIAS : " << endl;

    while(p != NULL){
        cout << "[" << p->getId() << "]";

        if(p->getArestas() != NULL)
            p->imprime();
            else
                cout << "---";
        cout << endl;
        p = p->getProx();
    }
}

/// Algoritmos de Insercao

void Grafo::insereVertice(int id){
    No *p = new No();
    No *t = primeiro;
    p->setId(id);
    p->setNum(numVertices);
    if(!buscaNo(id)){
        if(t == NULL){
            primeiro = p;
            p->setProx(NULL);
            }else{
                while(t->getProx() != NULL)
                    t = t->getProx();
                    t->setProx(p);
                    p->setProx(NULL);
            }

        numVertices++;

    }
}

void Grafo::insereAresta(int no1, int no2){

    if(!ehDirecionado){

        No* p = buscaNo(no1);
        No* t = buscaNo(no2);
        Aresta* a = new Aresta();
        Aresta* b = new Aresta();

        if(no1 == no2)
            cout << "Nao eh possivel criar self-loops ! vertices (" << no1 << "," << no2 << ")" << endl;
            else{
                if(buscaAresta(no1, no2) == NULL){
                    if(p != NULL && t != NULL){
                        p->insereAresta(no2, a);
                        t->insereAresta(no1, b);
                        p->increaseDegree();
                        t->increaseDegree();
                        numArestas++;
                    }else
                        cout << "\nVertices nao encontrados !" << endl;
                }else
                    cout << "Aresta ja existente entre os vertices " << no1 << " e " << no2 << " ! " << endl;
            }
    }else
            cout << "Nao eh possivel inserir uma aresta em um grafo direcionado, apenas um arco !" << endl;
}

void Grafo::insereArco(int no1, int no2, int peso){

    if(ehDirecionado){

        No* p = buscaNo(no1);
        No* t = buscaNo(no2);
        Aresta* a = new Aresta();

        if(no1 == no2)
            cout << "Nao eh possivel criar self-loops ! vertices (" << no1 << "," << no2 << ")" << endl;
            else{
                if(buscaAresta(no1, no2) == NULL){
                    if(p != NULL && t != NULL){
                            p->insereAresta(no2, a, peso);
                        t->increaseInDegree();
                        numArcos++;
                    }else
                        cout << "\nVertices nao encontrados !" << endl;
                }else
                    cout << "Arco ja existente entre os vertices " << no1 << " e " << no2 << " ! " << endl;
            }
    }else
        cout << "Nao eh possivel inserir uma arco em um grafo nao direcionado, apenas uma aresta !" << endl;
}

void Grafo::insereAresta(int vet1,int vet2,int peso){
    if(!ehDirecionado){

        No* p = buscaNo(vet1);
        No* t = buscaNo(vet2);
        Aresta* a = new Aresta();
        Aresta* b = new Aresta();

        if(vet1 == vet2){

            cout << "Impossivel criar self-loops ! Vertices (" << vet1 << "," << vet2 << ")" << endl;
        }else{
            if(buscaAresta(vet1, vet2) == NULL){
                if(p != NULL && t != NULL){
                    p->insereAresta(vet2, a,peso);
                    t->insereAresta(vet1, b,peso);
                    p->increaseDegree();
                    t->increaseDegree();
                    numArestas++;
                }
              }
            }
    }else
        cout << "Nao eh possivel inserir uma aresta em um grafo direcionado, apenas um arco" << endl;
}

void Grafo::removeNo(int no){
    No* p = primeiro;
    No* aux = NULL;

    if(p == NULL || buscaNo(no) == NULL){
        cout << "Vertice inexistente ! " << endl;
    }
        else{

            while(p != NULL){
                if(buscaAresta(p->getId(), no) != NULL)
                    p->retiraAresta(no);
                p = p->getProx();
            }

            p = primeiro;

            while(p != NULL){
                if(p->getId() == no)
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
        }
}

void Grafo::removeAresta(int no1, int no2) {
	if (!ehDirecionado) {
		No* p = buscaNo(no1);
		No* t = buscaNo(no2);
		if (p == NULL || t == NULL)
			cout << "Vertices inexistente!" << endl;
		else if (no1 == no2)
			cout << "Grafo simples, n�o existe self-loops" << endl;
		else if (buscaAresta(no1, no2) != NULL) {
			p->retiraAresta(no2);
			p->decreaseDegree();
			t->retiraAresta(no1);
			t->decreaseDegree();
			numArestas--;
		}
		else {
			cout << "aresta desejada nao existe" << endl;
		}
	}
}


void Grafo::removeArco(int no1, int no2) {
	if (ehDirecionado) {
		if (no1 == no2)
			cout << "Digrafo simples - nao existe self loops" << endl;
		else {
			No* p = buscaNo(no1);
			No* t = buscaNo(no2);
			if (t == NULL || p == NULL)
				cout << "Um dos vertices inserido nao foi econtrado!" << endl;
			else {
				if (buscaAresta(no1, no2) != NULL) {
					p->retiraAresta(no2);
					t->decreaseOutDegree();
					p->decreaseInDegree();
				}
			}
		}
	}
}


/// Algoritmos de Buscas

No* Grafo::buscaNo(int id) {
    No* p = primeiro;

    while(p != NULL){
        if( p->getId() == id)
            return p;
        p = p->getProx();
    }

    return p;
}

int Grafo::buscaId(int num){
        
    No* p = primeiro;

    while(p != NULL){
        cout<<endl;
        if(p->getNum() == num){
            return p->getId();
        }
        p = p->getProx();
    }
    
    return -1;
}

Aresta* Grafo::buscaAresta(int vet1,int vet2)
{
    No* p = buscaNo(vet1);
    Aresta* aux = p->getArestas();

    if(p != NULL && aux != NULL){

        while(aux != NULL){
            if(aux->getId() == vet2)
                return aux;
            aux = aux->getProx();
        }
    }

    return aux;
}


/// Grau do Grafo

int Grafo::getVerticeDegree(int id){

    No* p = buscaNo(id);
    int degree;

    if(p == NULL){
        cout << "Vertice inexistente !(" << id << ")" << endl;
        return -1;
    }else{
        degree = p->getDegree();
        return degree;
    }
}

int Grafo::getVerticeInDegree(int id){

    No* p = buscaNo(id);
    int inDegree;

    if(p == NULL){
        cout << "Vertice inexistente !(" << id << ")" << endl;
        return -1;
    }else{
            inDegree = p->getInDegree();
            return inDegree;
    }
}

int Grafo::getVerticeOutDegree(int id){

    No* p = buscaNo(id);
    int outDegree;

    if(p == NULL){
        cout << "Vertice inexistente !(" << id << ")" << endl;
        return -1;
    }else{
            outDegree = p->getOutDegree();
            return outDegree;
    }
}

int Grafo::grauDoGrafo(){

    int aux;
    No* p = primeiro;
    if(p != NULL){
        aux = p->getDegree();
        while(p != NULL){
            if(p->getDegree() >= aux)
                aux = p->getDegree();
            p = p->getProx();
        }
        return aux;
    }else
        return -1;
}

void Grafo::complementaGrafo(){
    if(ehDirecionado == false){
        No*
        for(int i = 0; i<numVertices; i++){
            for(int j = 0; j<numVertices; j++){
                if(adj->get(i,j) == 0){
                    adj->set(i,j,1);
                    
                }
                else if(adj->get(i,j)==1)
                    adj->set(i,j,0);
            }
        }
    }
    
}
///Grafo complementar


/////Busca em PROFUNDIDADE
//
//void Grafo::deepFirstSearch(){//Duvida em relacao ao vetor
//
//    No* p = primeiro;
//    int vetorMarcacao[10000];
//
//    while(p != NULL){
//        vetorMarcacao[p->getId()] = 0;
//        p = p->getProx();
//    }
//
//    p = primeiro;
//
//    while(p != NULL){
//        if(vetorMarcacao[p->getId()] == 0)
//            dfs(p, vetorMarcacao);
//        p = p->getProx();
//    }
//}
//
//void Grafo::dfs(No* p, int* vetorMarcacao){
//
//    Aresta* a = p->getArestas();
//
//    vetorMarcacao[p->getId()] = 1;
//    cout << p->getId() << ",";
//    while(a != NULL){
//        if(a != NULL && vetorMarcacao[a->getId()] == 0)
//            dfs(buscaNo(a->getId()), vetorMarcacao);
//        a = a->getProx();
//    }
//}
//
////Busca em largura
//void Grafo::breadthFirstSearch(){
//
//    Fila fila;
//
//    No* p = primeiro;
//
//    int vetorDeMarcacao[10000];
//
//    while(p != NULL){
//        vetorDeMarcacao[p->getId()] = 0;
//        p = p->getProx();
//    }
//
//    vetorDeMarcacao[primeiro->getId()] = 1;
//
//    fila.enfileira(primeiro->getId());
//
//    while(!fila.vazia()){
//        No* v = buscaNo(fila.desenfileira());
//        Aresta* a = v->getArestas();
//        cout << v->getId() << ",";
//        while(a != NULL){
//            if(vetorDeMarcacao[a->getId()] == 0){
//                vetorDeMarcacao[a->getId()] = 1;
//                fila.enfileira(a->getId());
//            }
//
//            a = a->getProx();
//        }
//    }
//}



