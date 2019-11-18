#include <iostream>
#include <fstream>
#include <cstring>
#include "Grafo.h"

using namespace std;

void imprimirMenu()
{

    cout << "==================== - MENU - ====================" << endl
         << "[A] para caminhamento em largura." << endl
         << "[B] para acaminhamento em profundidade." << endl
         << "[C] para componentes fortemente conexas." << endl
         << "[D] para ordenacao topologica." << endl
         << "[E] para Dijkstra." << endl
         << "[F] para Floyd." << endl
         << "[G] para Prim." << endl
         << "[H] para Kruskal." << endl
         << "[0] para finalizar o programa." << endl
         << "==================================================" << endl;

         char controle;

         while(controle != '0')
    {
        cout << "Digite a operacao: ";
        cin >> controle;

        switch (controle)
        {
		case 'a': case 'A':

            break;

		case 'b': case 'B':

            break;

		case 'c': case 'C':

            break;

		case 'd': case 'D':

            break;

		case 'e': case 'E':

            break;
		case 'f': case 'F':

            break;
		case 'g': case 'G':

            break;
		case 'h': case 'H':

            break;
        }
    }
}

Grafo* lerArquivo(char *nomeArquivo, Grafo* grafo)
{
    FILE* arquivo; //ponteiro para o txt
    char ch;
    int linhas = 0;
    int numVertices, vet1,vet2,peso;
    int flag = 0;

    arquivo = fopen(nomeArquivo, "r"); //abre e le arquivo

    if(arquivo == NULL){
        cout<< "Arquivo nao encontrado" << endl;
        return NULL;
    }else{

        while((ch = fgetc(arquivo))!= EOF){ //ch recebe cada caracter do arquivo, ate ele acabar
            if((ch == '\n'))
                linhas++;//a cada \n o arquivo contabiliza mais uma linha
        }
        cout<< "Numero de linhas : " << linhas << endl;

        rewind(arquivo); //volta para o inicio do arquivo
        
        while((ch = fgetc(arquivo))!= '\n'){} //pula a primeira linha do arquivo

        while((ch = fgetc(arquivo)) != '\n'){
            if(isspace(ch))
                flag++; // conta a quantidade de espacos vazios presentes na 2a linha do arquivo
        }
    }
    
    rewind(arquivo); //volta pro inicio do artigo

    bool ehDirecionado = false;
    cout<< "Adicionando vertices e arestas" << endl;

    for(int i=1;i<=linhas;i++){
    ///Linha 1 do arquivo sempre inclui o numero total de vertices, portanto ao le-la add o num de vertices
        if(i == 1){
            fscanf(arquivo, "%d\n", &numVertices);
            cout<< "numVertice: " << numVertices << endl;
        }
        ///Caso nao estejamos lendo a linha 1 do arquivo, deve-se inserir os vertices
        else{
            if(flag == 1){//Se flag == 1, grafo nao ponderado

                if(i == 2)
                    cout<<"Grafo nao ponderado" <<endl;
                
                if(fscanf(arquivo,"%d %d\n",&vet1,&vet2)!=EOF){   //le o indice do vet1, vet2 e cria uma aresta
                    cout<<"Lido do arquivo: "<<vet1<<" e "<< vet2<<endl;
                    grafo->insereVertice(vet1);
                    grafo->insereVertice(vet2);
                    if(ehDirecionado)
                        grafo->insereArco(vet1, vet2, 0);
                    else
                        grafo->insereAresta(vet1, vet2);
                }
            }else{
                if(fscanf(arquivo, "%d %d %d\n", &vet1, &vet2, &peso) != EOF){
                    printf("%d %d %d\n", vet1, vet2, peso);
                    grafo->insereVertice(vet1);             // insere o vertice correspondente no arquivo.
                    grafo->insereVertice(vet2);             // insere o vertice correspondente no arquivo.
                    if(!ehDirecionado)
                        grafo->insereAresta(vet1, vet2, peso); // insere a aresta correspondente no arquivo ou o arco
                        else
                            grafo->insereArco(vet1, vet2, peso);
                }
            }
        }
    }
    fclose(arquivo);
    return grafo;
}
int main()
{
    Grafo* grafo = new Grafo(); //cria grafo a ser preenchido
    lerArquivo("teste1.txt",grafo); //manipula arquivo txt
    cout<<"Imprimindo Vertices: "<<endl;
    grafo->imprimeVertices();
    cout<<"Imprimindo Arestas: "<<endl;
    grafo->imprimeArestas();
    cout<<"Matriz de Adj: "<<endl;
    grafo->preencheMatrizAdj();
    cout<< grafo->getVerticeDegree(10)<<endl;
    return 0;
}
