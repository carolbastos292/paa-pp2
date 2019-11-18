#include "Grafo.h"

int main() {

	string entrada = "Entrada";
	string salida = "Salida";
	double tiempo = 0;
	unsigned int n = 0;;
	Grafo g;
	g.generaAleatoriamente(10,8);
	g.escribe(make_pair(g._grafo,g._grafo.size()),entrada,tiempo,n);
	pair<vector<Grafo::Vertice*>,int> clique = g.hayClique(3,tiempo,n);
	g.escribe(clique,salida,tiempo,n);
	return 0;
}















