#include "../headers/bibliotecas.h"
#include <vector>

/*
Grupo: Eduardo Vieira 201665554AC
       Matheus Brinati 201665564C
       Vinicius Alves 201665558AC
*/

Grafo::Grafo()
{

}

Grafo::~Grafo()
{

}


void Grafo::adcionarNo(int id, float pesoNo)
{
    No no = No();
    no.setID(id);
    no.setPeso(pesoNo);
    listaNos.push_back(no);
}



void Grafo::showInfo(){
    int i=0;
    for (std::vector<No>::iterator it = listaNos.begin(); it != listaNos.end(); ++it) {
            cout << "No: " << it->getID() << endl;
			i++;

    }
    cout << "size: " << listaNos.size() << endl;

}

bool Grafo::noEstaNoGrafo(int index)
{
    for (std::vector<No>::iterator it = listaNos.begin(); it != listaNos.end(); ++it) {
        if( it->getID() == index ){
            return true;
        }
    }
    return false;
}

 void Grafo::writeFile(string path, int numClausulas, int numLiterais, int valorClique)
{
    ofstream f(path.c_str());
    int i, j, ordemGrafo, z, x;
    ordemGrafo = getOrdemGrafo();
    if(f.is_open())
    {
        f << "p cnf " << numLiterais << " " << numClausulas << endl;
        for (i = 1; i <= valorClique; i++)
        {
            for (j = 1; j <= ordemGrafo; j++)
                f <<((i-1)*ordemGrafo)+j <<" ";
            f << "0" << endl;
        }
        for (j = 1; j <= ordemGrafo; j++)
            for (i = 1; i <= valorClique; i++)
                for (x = i+1; x <= valorClique; x++)
                    {
                        f << (-1)*(((i-1)*ordemGrafo)+j) << " " << (-1)*(((x-1)*ordemGrafo)+j) << " 0" << endl;
                    }
        for (j = 1; j <= ordemGrafo; j++)
            for (z = j+1; z <= ordemGrafo; z++)
                if (!vizinho(j,z))
                    for (i = 1; i <= valorClique; i++)
                        for (x = i+1; x <= valorClique; x++)
                        {
                            f << (-1)*(((i-1)*ordemGrafo)+j) << " " << (-1)*(((x-1)*ordemGrafo)+z) << " 0" << endl;
                            f << (-1)*(((x-1)*ordemGrafo)+j) << " " << (-1)*(((i-1)*ordemGrafo)+z) << " 0" << endl;
                        }
    }
    else
    {
        cerr << "Couldn't open file!" << endl;
    }
}

void Grafo::readFile(char *path)
{
	int m;
	int count = 0;
	ifstream f;
	int id=0;
	int id_destino;
	f.open(path);
	if (f.is_open()) {
		f >> m;
        for(int j = 1;j<=m;j++ ){
            adcionarNo(j,0);
        }
		while (true) {
			double value;
			if(count > 2){
                count = 0;
			}
            if (!(f >> value)) {
                break;
            }
            else {
                if (count == 0) {
                    id = value;
                }
                else if (count == 1) {
                    id_destino = value;
                }
                else if( count == 2){
                    for (std::vector<No>::iterator it = listaNos.begin(); it != listaNos.end(); ++it) {
                            if( it->getID() == id )
                                    it->adicionaAresta(id_destino,false,value);
                            if( it->getID() == id_destino )
                                    it->adicionaAresta(id,false,value);
                    }
                }
                }
				count++;
		}
            cout << "Arquivo lido com sucesso" << endl;
    }
	else {
		cerr << "Couldn't open file!" << endl;
	}

}

int Grafo::getOrdemGrafo()
{
    return listaNos.size();
}

int Grafo::cliqueMaximaForcaBruta(){
    int n = getOrdemGrafo();
    vector<int> vi;
    vector<bool> v(n);
    bool naoClique = false; // se naoClique é falso é pq é Clique
    for (int e = n; e > 1; e--)
    {
        vi.clear();
        fill(v.begin(), v.end(), false);
        fill(v.begin(), v.begin() + e, true);
        do {
            vi.clear();
            for (int i = 0; i < n; ++i) {
                if (v[i]) {
                   vi.push_back (i+1);
                }
            }
            for (std::vector<int>::iterator it = vi.begin(); it != vi.end(); ++it){
                for(std::vector<int>::iterator it2 = it+1; it2 != vi.end(); ++it2){
                    if(!vizinho(*it,*it2)){
                        naoClique = true;
                        break;
                    }
            }
            if(naoClique){
                    break;
            }
        }
            if(!naoClique){
                return e;
            }
            else
                naoClique = false;
        } while (prev_permutation(v.begin(), v.end()));
    }
}

bool Grafo::formaClique(vector<No>nosNaSolucao, No noCandidato)
{
     for(vector <No>::iterator n = nosNaSolucao.begin(); n != nosNaSolucao.end() ; n++)
            if(!vizinho(n->getID(),noCandidato.getID())){
                return false;
            }
     return true;

}

bool Grafo::verificaSolucao(vector<No> nosNaSolucao)
{
    for (std::vector<No>::iterator it = nosNaSolucao.begin(); it != nosNaSolucao.end(); ++it){
            for(std::vector<No>::iterator it2 = it+1; it2 != nosNaSolucao.end(); ++it2){
                if(!vizinho(it->getID(),it2->getID())){
                    return false;
                }
            }
    }
   return true;
}






void Grafo::removeAresta(int id1,int id2)
{
    if(noEstaNoGrafo(id1) && noEstaNoGrafo(id2)){
        if(vizinho(id1,id2)){
        for (std::vector<No>::iterator it = listaNos.begin(); it != listaNos.end(); ++it) {
             if( it->getID() == id1 )
                    it->removeAresta(id2,false);
             if( it->getID() == id2)
                    it->adicionaAresta(id1,false);
        }
           }

    } else {
         cout << "Nao e possivel remover aresta devido aos nos nao existirem" << endl;
    }

}

void Grafo::adicionaAresta(int id1, int id2, float peso)
{
    if(noEstaNoGrafo(id1) && noEstaNoGrafo(id2)){
        for (std::vector<No>::iterator it = listaNos.begin(); it != listaNos.end(); ++it) {
             if( it->getID() == id1 )
                    it->adicionaAresta(id2,false,peso);
             if( it->getID() == id2)
                    it->adicionaAresta(id1,false,peso);
        }
    } else {
        cout << "Nao e possivel adcionar aresta devido aos nos nao existirem" << endl;
    }
}

bool Grafo::vizinho(int id1, int id2)
{
    for (std::vector<No>::iterator it = listaNos.begin(); it != listaNos.end(); ++it){
        if(it->getID() == id1 ){
            return it->eVizinho(id2);
        }
        if(it->getID() == id2 ){
            return it->eVizinho(id1);
        }
    }


}

void Grafo::reduzSat(int valorClique)
{
    int ordemGrafo = getOrdemGrafo();
    int i,j,x,z,numLiterais;
    int numClausulas = 0;
    numLiterais = ordemGrafo*valorClique;
    for (i = 1; i <= valorClique; i++)
    {
        for (j = 1; j <= ordemGrafo; j++)
            cout <<((i-1)*ordemGrafo)+j <<" ";
        cout << "0" << endl;
        numClausulas++;
    }
    for (j = 1; j <= ordemGrafo; j++)
        for (i = 1; i <= valorClique; i++)
            for (x = i+1; x <= valorClique; x++)
            {
                cout << (-1)*(((i-1)*ordemGrafo)+j) << " " << (-1)*(((x-1)*ordemGrafo)+j) << " 0" << endl;
                numClausulas++;
            }
    for (j = 1; j <= ordemGrafo; j++)
        for (z = j+1; z <= ordemGrafo; z++)
            if (!vizinho(j,z))
                for (i = 1; i <= valorClique; i++)
                    for (x = i+1; x <= valorClique; x++)
                    {
                        cout << (-1)*(((i-1)*ordemGrafo)+j) << " " << (-1)*(((x-1)*ordemGrafo)+z) << " 0" << endl;
                        numClausulas++;
                        cout << (-1)*(((x-1)*ordemGrafo)+j) << " " << (-1)*(((i-1)*ordemGrafo)+z) << " 0" << endl;
                        numClausulas++;
                    }
    cout << numClausulas << " " << numLiterais;
    writeFile(output.c_str(), numClausulas, numLiterais, valorClique);

}
