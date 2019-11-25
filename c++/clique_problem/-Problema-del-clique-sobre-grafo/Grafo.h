#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <time.h>
using namespace std;

/*
 *	@file Grafo.h
 *
 *	Implementación de un Grafo.
 *
 *	Facultad de Informática
 *	Universidad Complutense de Madrid
 *
 *	(c) Álvaro Velasco García, 2017
 */

class Grafo {
public :

	/*	Subclase interna que representa la unidad minima del Grafo.
	 */
	class Vertice {
		public :

			class Arista {

				public:

					/*Atributos de la clase:*/

					/*Valor que posee esa arista.*/
					int _valoracion;
					/*Puntero al vertice que apunta la arista.*/
					Vertice* _destino;
					/*Valor que representa si esa arista fue descartada o no*/
					bool _descartada;
					/*Puntero a otra arista que es la inversa de la actual*/
					Arista* _homologa;

					/*	Para entender mejor la variable _homologa:
					 * 	Ejemplo 0 - 1.(El vertice con id 0 apunta al 1 y el 1 al 0)
					 *
					 * 	Al ser un grafo no dirigido esto se da por entendido,es decir que si 0 apunta a 1,1 apunta a cero.Pero
					 * 	en esta implementación,en la lista de aristas que posee cada vertice de este grafo de ejemplo,los dos tendrian una
					 *  arista cada uno,de modo que para saber que ambas aristas, son homologas(es decir,son la misma arista con la misma valoracion
					 *  pero distinto destino) utilizamos este puntero que apunta a su arista homologa.
					 *
					 */

					/* Constructores. */

					/*Contructor Basico.*/
					Arista(int valoracion, Vertice* destino,Arista* homologa):_valoracion(valoracion),_destino(destino),_descartada(false),_homologa(homologa){};

					/*Contructor Basico Auxiliar.Este se usa de manera auxiliar para generar de manera aleatoria grafos.*/
					Arista():_valoracion(0),_destino(NULL),_descartada(false),_homologa(NULL){};

			};

			/*Atributos de la clase:*/

			/*Cojunto de aristas que salen del vertice.*/
			vector<Arista> _aristas;

			/*Identificador unico que sirve para diferenciar un vertice de los demás.*/
			unsigned int _id;

			/*Valor que representa si esa arista fue descartada o no*/
			bool _descartado;

			/*Valor que representa cuantas aristas de ese vertice fueron descartadas.*/
			unsigned int _numAristasDescartadas;


			/* Constructores. */

			/*Contructor Basico.*/
			Vertice(int id):_aristas(vector<Arista>()),_id(id),_descartado(false),_numAristasDescartadas(0){};

			/*Metodos de la Clase*/

			/*	Operacion observadora-modificadora que actualiza el numero de descartes que a sufrido un vertice y revisa si el grado de este
			 * 	es suficientemente grande como para no descartarlo.
			 *	@param r Tamaño del clique buscado.
			 */
			void actualizaDescartes(unsigned int r){
				_numAristasDescartadas++;
				if(getGrado() < r-1){
					_descartado = true;
				}
			}

			/*	Operacion observadora que nos devuelve el grado "actual" del vertice.
			 */
			unsigned int getGrado(){
				return _aristas.size()-_numAristasDescartadas;
			}

	};
	/*Atributos de la clase:*/

	/* 	Vector de Vertices que es en si el grafo.*/
	vector<Vertice*> _grafo;

public:

	/*Metodos de la Clase*/


	/*	Operación observadora que escribe en un documento,los vertices pertenecientes a un grafo.
	 *	@param grafo Par de elementos,que su primer valor representa el grafo y el segundo el numero de vertices de ese grafo.
	 *	@param nombre Nombre del documento en donde se guardará la informacion de ese grafo.
	 *	@param tiempo Tiempo total tardado en encontrar la solucion.
	 *	@param n Numero de vertices revisados.
	 *
	 *	Ejemplo de formato -> 0:1(2),2(3),3(4)
	 *	El primer valor antes de los dos puntos,es el id del vertice del que se esta dando informacion.Los
	 *	valores que salen a continuacion ,sin enmarcar entre parentesis,son los id`s a los que es conexo el vertice en cuestion y
	 *	los valores entre parentesis a la derecha de estos representan el valor que tiene la arista que los une.
	 */

	void escribe(const pair<vector<Vertice*>,int> grafo,string nombre,double tiempo,unsigned int n){

		ofstream doc(nombre.c_str());
		if(grafo.second > 0){
			if(nombre == "Salida"){
				doc << "Solucion:" << endl;
			}
			for (unsigned int indiceVertices = 0; indiceVertices < grafo.first.size(); indiceVertices++){
				doc << grafo.first.at(indiceVertices)->_id << ":";
				for (unsigned int indiceAristas = 0; indiceAristas < grafo.first.at(indiceVertices)->_aristas.size(); indiceAristas++){
					doc << grafo.first.at(indiceVertices)->_aristas.at(indiceAristas)._destino->_id;
					doc <<"("<< grafo.first.at(indiceVertices)->_aristas.at(indiceAristas)._valoracion<<"),";
				}
				doc << endl;
			}
		}else{
			doc << "No hay solucion" << endl;
		}
		if(nombre == "Salida"){
			doc << "Coste:" << grafo.second << endl;
			doc << endl << "Numero de vertices revisados: " << n << endl;
			doc << "Tiempo total de exploracion: " << tiempo << "s" << endl;
			doc << "Tiempo medio de exploracion por nodo: " << tiempo/(double)n << endl;
		}


		doc.close();
	}

	/*	Operación generadora que crea un grafo de manera aleatorio siguiendo 2 parametros.
	 *	@param tamanio Numero de nodos que contendra el grafo.
	 *	@param maxValoracion Cota maxima,sin incluir,que puede tomar la valoracion de una arista.
	 */
	void generaAleatoriamente(const int tamanio,const int maxValoracion){

		int probabilidad = 0;
		int valoracion = 0;
		int pDU;

		/*	Inicialmente,creamos todos los vertices que poosera el grafo,dando a cada uno un identificador i.
		 */
		for(int i = 0; i < tamanio;i++){
			_grafo.push_back(new Vertice(i));
		}

		/*	Recorremos el vector de grafo de modo que cada vez que un vertice es analizado se escoge un número
		 * 	al azar,que representa la probabilidad de union que posee ese vertice.Es decir,
		 * 	la probabilidad que tiene ese vertice de tener una union con los demás vertices del grafo.
		 *
		 *	Notese que,al ser no ser un multi-grafo,no puede haber dos aristas distintas entre dos vertices, de modo
		 *	que a medida que avanzamos,solo se comprueba se "lanza el dado" para ver si será conexo con vertices
		 *	aun no analizados.
		 */
		for (int indiceit = 0; indiceit < tamanio; indiceit++){
			pDU = (rand() % 100)+1;
			for (int indiceit2 = indiceit+1; indiceit2 < tamanio; indiceit2++){
				probabilidad = (rand() % 100)+1;
				if(probabilidad < pDU){
					valoracion = rand() % maxValoracion;
					Vertice::Arista* arista = new Vertice::Arista(valoracion,_grafo.at(indiceit2),NULL);
					Vertice::Arista* arista2 = new Vertice::Arista(valoracion,_grafo.at(indiceit),arista);
					arista->_homologa = &*arista2;
					_grafo.at(indiceit)->_aristas.push_back(*arista);
					_grafo.at(indiceit2)->_aristas.push_back(*arista2);
				}
			}
		}

	}

	/*	Operación modificadora que "desconecta" dos vertices entre si.
	 *  @param a Puntero a la arista que se desea marcar como no valida.
	 *  @param r Tamaño del clique que se esta buscando.
	 *
	 * 	Digo "desconecta" entre comillas porque en realidad no se produce esa desconexion,rigurosamente hablando,
	 * 	lo que se hace realmente es marcar esa arista entre ambos como no valida.
	 *
	 *	Además se llama al metodo actualzaDesccartes,que aumenta el numero de veces que fue descartado ese vertice y
	 *	comprueba que,el grado que tenga dicho vertice sea mayor o igual al tamaño del clique que buscamos menos 1.
	 */

	void desconecta(Grafo::Vertice::Arista* a,int r){

		if(!a->_descartada){
			a->_descartada = true;
			a->_destino->actualizaDescartes(r);
		}


		if(!a->_homologa->_descartada){
			a->_homologa->_descartada = true;
			a->_homologa->_destino->actualizaDescartes(r);
		}
	}

	/*	Operación modificadora-observadora que busca el clique de menor valoracion de tamaño r.
	 *  @param r Tamaño del clique que se esta buscando.
	 *  @return pair<vector<Vertice*>,int> devuelve contenido en un par,el grafo que cumple con las condiciones de clique de tamaño r y su coste.
	 *
	 */

	pair<vector<Vertice*>,int> hayClique(const unsigned int r,double &segundos,unsigned int &n){

		vector<Grafo::Vertice*> potenciales;
		vector<Grafo::Vertice*> vecinos;
		unsigned int avances = 0;

		vector<Grafo::Vertice*> solucionActual;
		unsigned int costeActual = 0;

		vector<Grafo::Vertice*> mejorSolucion;
		unsigned int mejorCosteTotal = 0;

		bool encontroSolucion = false;

		clock_t t_ini,t_fin;

		/*	Antes de comenzar la busqueda,revisamos que los vertices del grafo cumplan una condicion minima:
		 *	Si un vertice forma parte de un clique,dicho vertice debe tener como minimo un grado r menos 1.
		 */
		potenciales = faseDeEliminacion(_grafo,r-1);

		/*	Para que haya un clique de tamaño r,debe haber al menos r vertices que cumplan la anterior condicion
		 * 	que dije,por ende,si no hay suficientes vertices que la cumplan,ya sabemos de antemano que no habrá
		 * 	un clique de tamaño r.
		 */
		if(potenciales.size() < r){
			make_pair(potenciales,0);
		}

		unsigned int indicePot = 0;
		unsigned int numVertDesct = 0;
		/*	Analizamos los vertices del grafo buscando cliques de tamaño r mientras aun queden suficientes vertices para
		 *  formar un clique de tamaño r.
		 */

		while(indicePot < potenciales.size() && potenciales.size() - 1 - numVertDesct > r){
			/* Guardamos todos los vecinos del vertice actual que aun no hayan sido descartados o que la arista entre ellos y el vertice actual
			 * no haya sido descartada.
			 */

			avances = 0;

			/*	Por cada vertice, anazilamos los "vecinos"(vertices conexos a el) y revisamos que estos que ninguno de estos "vecinos"
			 *  no haya sido descartado por insuficiencia de grado o si la arista que exisitia entre el vertice y su "vecino" no fuera descartada.
			 */
			vecinos = preparaVuelta(potenciales.at(indicePot),avances);

			/*	Recorremos la lista de "vecinos" mientras el vertice a revisar no sea descartado.
			 */
			t_ini = clock();
			while(vecinos.size() >= r-1 && !potenciales.at(indicePot)->_descartado){

				solucionActual.clear();
				costeActual = 0;
				encontroSolucion = false;

				/*	Buscamos si con los "vecinos" del vertice pudo conformar un clique y lo devolvemos.
				 *
				 *	Esta funcion se encargara de que se devuelva el menor clique de todos los posibles en los que el vertice actual
				 *	y el primero de sus "vecinos" puedan formar parte.
				 */
				solucionActual = analizaVecinos(vecinos,r,encontroSolucion,potenciales.at(indicePot),costeActual);

				/*	Revisamos si encontro una solucion:
				 *
				 *	-Si la encontró comprobará si esa solución tiene un mejor coste que la mejorSolucion:
				 *
				 *		-Si el coste es mejor que la mejor solcion o si fue la primera en encontrarse,la guardamos.
				 *
				 *		-Si no,descartamos esa solución.
				 *
				 *	-Si no la encontró,descartará el primero de los "vecinos" y probara con los restantes.
				 */
				if(encontroSolucion){
					/*	Una vez encontrado un clique,pepara dicho clique para que,las aristas que se pueda,sean descartados y los vertices,que se puedan
					 *  sean descartados.
					 */
					costeActual += preparaClique(solucionActual,potenciales.at(indicePot),r);
					if((costeActual < mejorCosteTotal || mejorCosteTotal == 0)){
						mejorSolucion = solucionActual;
						mejorCosteTotal = costeActual;
					}
				}

				/*	Comprobamos que los "vecinos" sigan cumpliendo la condicion grado(vertice) >= r-1 y que la arista entre el vertice actual
				 *  y ese "vecino" no haya sido descartada.
				 *
				 *  En este paso,descartamos al "vecino" con el cual se comprobo si existia cliqque.
				 */
				vecinos = faseDeEliminacion(vecinos,r-1);
				avances++;
				vecinos = preparaVuelta(potenciales.at(indicePot),avances);

			}

			/*	Una vez llegados a este punto,hemos comprobado todos los posibles cliques en los que el vertice(potenciales.at(indicePot)
			 *  podria haber pertenecido.Por tanto,podemos descartar todas sus aristas.
			 */
			for(unsigned int i = 0; i < potenciales.at(indicePot)->_aristas.size();i++){
				desconecta(&potenciales.at(indicePot)->_aristas.at(i),r);
			}
			numVertDesct++;
			indicePot++;
			t_fin = clock();
			n++;
			segundos += (double)(t_fin - t_ini)/ CLOCKS_PER_SEC;
		}


		if(mejorCosteTotal == 0){
			return make_pair(potenciales,0);
		}else{
			return make_pair(mejorSolucion,mejorCosteTotal);
		}

	}

	/*	Operación observadora que comprueba si dos vertices son conexos.
	 *  @param v1 Vertice a revisar si es conexo con v2.
	 *	@param v2 Vertice a revisar si es conexo con v1.
	 *	@return Grafo::Vertice::Arista* Arista que estamos buscando.
	 *
	 *	Esta comrpobacion llamará a busca que finalmente dará la respuesta a la pregunta.
	 *	Este programa intermediario,sirve para analizar cual de los dos vertices tiene una lista de "vecinos"
	 *	de menor tamaño para asi agilizar la posterior busqueda.
	 */

	Grafo::Vertice::Arista* sonConexos(Vertice* v1, Vertice* v2){

		if(v1->getGrado() < v2->getGrado()){;
			return busca(&v1->_aristas,v2->_id);
		}else{
			return busca(&v2->_aristas,v1->_id);
		}
	}

	/*	Operación observadora que comprueba si un cierto id de un vertice se encuentra entre los destinos de unas ciertas aristas.
	 *  @param aristas Aristas en donde se realiza la busqueda del id.
	 *	@param id Identificador del vertice que se busca.
	 *	@return Grafo::Vertice::Arista* Arista que estamos buscando.
	 *
	 *	Es una busqueda binaria del id.
	 *	Aprovecho que las listas de vecinos de todos los vertices estan siempre ordenadas de menor a mayor.
	 */

	Grafo::Vertice::Arista* busca(vector<Vertice::Arista>* aristas,const unsigned int id) {

		int izq = 0;
		int der = aristas->size()-1;
		int medio;
		while (izq <= der) {
			medio = (izq + der) / 2;
			if (aristas->at(medio)._destino->_id == id){
				return &aristas->at(medio);
			}else if (aristas->at(medio)._destino->_id > id){
				der = medio - 1;
			}else{
				izq = medio + 1;
			}
		}

		return NULL;
	}

	/*	Operación observadora-modificadora que dado un vertice, revisa si sus vecinos no fueron descartados o si la arista
	 * 	que existe entre ellos no fue descartada.
	 *  @param actual Vertice del cual revisaremos sus vecinos.
	 *	@param avances Marcador que indica por cual de los vertices debemos comenzar a revisar.
	 *	@return vector<Vertice*> Lista de vertices que cumplen las condiciones.
	 *
	 *	La naturaleza de este ultimo parametro se debe a la necesidad de que,al realizar la busqueda del clique,
	 *	no itere de manera infinita.En el documento anexo a este,viene explicado mejor y con dibujos.
	 *
	 */

	vector<Vertice*> preparaVuelta(Vertice* actual,unsigned int &avances){

		vector<Grafo::Vertice*> vecinos;
		for(unsigned int i = avances; i < actual->_aristas.size();i++){

			if(!actual->_aristas.at(i)._descartada &&
			   !actual->_aristas.at(i)._destino->_descartado){
				vecinos.push_back(actual->_aristas.at(i)._destino);
			}else{
				avances++;
			}

		}
		return vecinos;
	}

	/*	Operación modificadora que dado una lista de vertices,revisa que todos estos cumplan la condicion grado(vertice) >= r-1.
	 *  @param vertices Lista de vertices a revisar.
	 *	@param r Tamaño del clique buscado.
	 *	@return vector<Vertice*> Lista de vertices que cumplen las condiciones.
	 *
	 *	Si un vertice no cumple con la condicion minima,podemos descartar todas sus aristas y descartalo a el tambien.
	 *
	 *	Si algun vertice fue descartado,habria que volver a revisar todos los vertices no descartados otra vez ya que
	 *	podria ser que la eliminacion de uno,probocara la eliminacion de otro que posteriormente se considero que tenia suficiente grado.
	 */

	vector<Vertice*> faseDeEliminacion(vector<Vertice*> &vertices,const unsigned int r){

		vector<Grafo::Vertice*> potenciales;
		bool unoFueDescartado = false;

		for(unsigned int i = 0; i < vertices.size();i++){
			if(vertices.at(i)->getGrado() >= r){
				potenciales.push_back(vertices.at(i));
			}else{
				vertices.at(i)->_descartado = true;
				for(unsigned int a = 0;a < vertices.at(i)->_aristas.size();a++){
					desconecta(&vertices.at(i)->_aristas.at(a),r);
				}
				unoFueDescartado = true;

			}
		}
		if(unoFueDescartado && potenciales.size() > r){
			return faseDeEliminacion(potenciales, r);
		}
		return potenciales;
	}

	/*	Operación observadora que comienza la busqueda del clique dados dos vertices.
	 * 	1º-> Vertice actual.
	 * 	2º-> Primer vecino valido del vertice actual.
	 *  @param vertices Lista de vertices a revisar.
	 *	@param r Tamaño del clique buscado.
	 *	@return vector<Vertice*> Lista de vertices que conforman un clique.
	 *
	 *	Si un vertice no cumple con la condicion minima,podemos descartar todas sus aristas y descartalo a el tambien.
	 *
	 *	Si algun vertice fue descartado,habria que volver a revisar todos los vertices no descartados otra vez ya que
	 *	podria ser que la eliminacion de uno,probocara la eliminacion de otro que posteriormente se considero que tenia suficiente grado.
	 */

	vector<Vertice*> analizaVecinos(vector<Vertice*> &vecinos,const unsigned int r,bool &encontroSolucion,Vertice* actual,unsigned int &coste){

		vector<Vertice*> vecinosConexos;
		vector<Vertice*> solucion;
		Vertice::Arista* a;
		Vertice* volcador;
		unsigned int numVolcados = 0;
		unsigned int auxCoste = 0;
		int sumaFinal = 0;
		Vertice::Arista* ultimaAristaValida;

		/*	Miramos a cuantos vertices pertenecientes a la lista de vecinos del vertice 1,es conexos el vertice nº 2.
		 */
		for(unsigned int i = 1;i < vecinos.size();i++){
			a = sonConexos(vecinos.at(0),vecinos.at(i));
			if(a != NULL){
				vecinosConexos.push_back(vecinos.at(i));
				ultimaAristaValida = a;
				if(i+2 < r){
					coste += a->_valoracion;
				}
			}
		}

		/*	Si el vertice nº 2 es suficientemente conexo a los vecinos del vertice principal.Habria dos opciones:
		 */
		if(vecinosConexos.size() >= r-2){

			solucion.push_back(vecinos.at(0));

			/*	1ª Hay mas de un posible clique,hay que ver cual tiene menor coste.
			 */
			if(vecinosConexos.size()+2 > r){

				while(numVolcados < vecinosConexos.size() && solucion.size() < r-2){
					solucion.push_back(vecinosConexos.at(numVolcados));
					numVolcados++;
				}

				if(numVolcados > 0){
					vecinosConexos = quitaVecinos(vecinosConexos,numVolcados);
				}
				volcador = compitenQuicles(actual,solucion,vecinosConexos,auxCoste);

				if(volcador != NULL){
					solucion.push_back(volcador);
					coste += auxCoste;
					encontroSolucion = true;
					return solucion;
				}


			}else if(vecinosConexos.size()+2 == r){
				/*	2ª Ya hemos llegado al numero optimo de soluciones.Si los elementos de vecinosConexos son conexos entre si,habra un clique.
				 */
				sumaFinal = comprobacionFinal(vecinosConexos);

				if(sumaFinal != -1){
					sumaFinal += ultimaAristaValida->_valoracion;
					encontroSolucion = true;
					for(unsigned int a = 0; a < vecinosConexos.size();a++){
						solucion.push_back(vecinosConexos.at(a));
					}
					coste += sumaFinal;
				}
				sumaFinal = 0;
			}

		}

		return solucion;
	}


	/*	Operación observadora complementaria a "analizaVecinos" que revisa si todos los elementos de una lista de vecinos son conexos entre si.
	 *  @param vecinosConexos Lista de vertices a analizar.
	 *  @return int Suma de las valoraciones de las aristas entre los elementos del vector recibido.
	 *
	 *	Esta operación es utilizada en el caso de que haya los vertices justos(es decir == r) para conformar un clique.
	 *	De modo que si alguno no es conexo entre si,no se podra conformar un clique.
	 */

	int comprobacionFinal(const vector<Vertice*> vecinosConexos){

		bool noLogroClique = false;
		unsigned int i = 0;
		unsigned int a = i;
		unsigned int suma = 0;
		Vertice::Arista* arista;

		while(i < vecinosConexos.size() && !noLogroClique){

			a = i+1;
			while(a < vecinosConexos.size() && !noLogroClique){

				arista = sonConexos(vecinosConexos.at(i),vecinosConexos.at(a));
				if(arista != NULL){
					suma += arista->_valoracion;
				}else{
					noLogroClique = true;
				}


				a++;
			}
			i++;
		}

		if(!noLogroClique){
			return suma;
		}else{
			return -1;
		}
	}

	/*	Operación observadora complementaria a "analizaVecinos" que,por cada elemento de una lista de vertices,analiza si este es conexo a todos
	 *  los pertenecientes a la solucion.
	 *  @param actual Vertice principal al cual todos los demás vertices que se mencionen son conexos a el.
	 *  @param solucionActual Lista de vertices de tamaño r-1 que podrián llegar a formar parte de un clique entre ellos.
	 *  @param vecinosConexos Lista de vertices que son candidatos a terminar de completar el clique si son conexos a todos los elementos de solucionActual.
	 *	@param auxCoste Coste acumulado de todas las aristas que formarn el posible clique.
	 *	@return Vertice* Lista de vertices que conforman un clique.
	 *
	 *	Esta operación es utilizada en el caso de que haya mas vertices de los justos(es decir > r) para conformar un clique.
	 *	De modo que vamos analizandos los candidatos a formar clique y vemos si cumplen las condiciones minimas necesarias y de entre los que lo cumplan,
	 *	elegimos la que tenga un coste menor.
	 */

	Vertice* compitenQuicles(Vertice* actual,const vector<Vertice*> solucionActual,const vector<Vertice*> vecinosConexos,
			                 unsigned int &auxCoste){

		unsigned int coste = 0;
		unsigned int mejorCoste = 0;
		Vertice::Arista* arista;
		Vertice* mejorVertice;
		bool encontroSolucion = false;
		bool noCumple = false;


		for(unsigned int i = 0; i < vecinosConexos.size();i++){

			coste += sonConexos(actual,vecinosConexos.at(i))->_valoracion;
			noCumple = false;
			for(unsigned int a = 0; a < solucionActual.size() && !noCumple;a++){

				arista = sonConexos(vecinosConexos.at(i),solucionActual.at(a));
				if(arista != NULL){
					coste += arista->_valoracion;
				}else{
					noCumple = true;
				}
			}

			if((coste < mejorCoste || mejorCoste == 0) && !noCumple){
				encontroSolucion = true;
				auxCoste = coste;
				mejorCoste = coste;
				mejorVertice = vecinosConexos.at(i);
			}

			coste = 0;

		}

		if(encontroSolucion){
			return mejorVertice;
		}else{
			return NULL;
		}
	}

	/*	Operación modificadora complementaria a "analizaVecinos" que quita elementos de una lista de veinos a partir de un cierto valor.
	 *  @param vecinosConexos Lista de vertices a analizar.
	 *  @return vector<Vertice*> Lista actualizada.
	 *
	 *	Esta operación es utilizada en el caso de que haya los vertices justos(es decir == r) para conformar un clique.
	 *	De modo que si alguno no es conexo entre si,no se podra conformar un clique.
	 */

	vector<Vertice*> quitaVecinos(vector<Vertice*> vecinos,unsigned int numVolcados){

		vector<Vertice*> vecinosNuevos;
		for(unsigned int i = numVolcados; i < vecinos.size();i++){
			vecinosNuevos.push_back(vecinos.at(i));
		}
		return vecinosNuevos;
	}

	/*	Operación observadora que:
	 * 	1º Suma los costes de las aristas entre el vertice actual y los que forman parte del clique.
	 *	2º Quita las aristas pertinentes que ya no sean necesarias al haber formado el clique.
	 *	3º Añade el vertice actual al cllique.
	 *  @param solucion Lista de vertices a analizar.
	 *  @return int suma de los valores de las aristas de los vertices pertenecientes al clique y el vertice actual.
	 *
	 *	Esta operación es utilizada en el caso de que haya los vertices justos(es decir == r) para conformar un clique.
	 *	De modo que si alguno no es conexo entre si,no se podra conformar un clique.
	 */
	int preparaClique(vector<Grafo::Vertice*> &solucion,Vertice* &actual,unsigned int r){

		unsigned int i = 0;
		unsigned int suma = 0;
		unsigned int conexiones = 0;
		//1º
		while(i < solucion.size()){
			suma += sonConexos(solucion.at(i),actual)->_valoracion;
			i++;
		}



		//2º
		for(unsigned int i = 0; i < solucion.size();i++){
			conexiones = 0;
			/*	Solo puedes desconectar un vertice si el grado "interno" es menor que r-1.
			 *  El grado interno es el numero aristas que posee dicho vertice conexas a los vecinos del actual.
			 */
			for(unsigned int a = 0; a < actual->_aristas.size();a++){

				if(sonConexos(actual->_aristas.at(a)._destino,solucion.at(i)) != NULL){
					conexiones++;
				}
			}

			/*	Si ese vertice no tiene suficientes aristas internas como para formar otro clique,lo desconectamos del actual.
			 */
			if(conexiones < r-1){
				desconecta(sonConexos(solucion.at(i),actual),r);
			}
		}

		//3º
		solucion.push_back(actual);

		return suma;
	}


};
