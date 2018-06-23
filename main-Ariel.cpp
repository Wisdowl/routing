#include "header.h"
#include "EstruturaGrafos.cpp"
#include "Buscas-Ordenacoes.cpp"

using namespace std;

int main(){
	Grafo *g = new Grafo();
	deque<Node*> *caminhos = new deque<Node*>;
	Caminhos *A = NULL;
	//int i, a, b, capacidade;
	float cust;
	/*for(i=0;i<114;i++){
		scanf("%d %d %d %f", &a, &b, &capacidade, &cust);
		addArcoPonderado(g, a, b, cust);


	}*/

	addArcoPonderado(g, 0, 1, 12);
	addArcoPonderado(g, 1, 0, 12);

	addArcoPonderado(g, 1, 2, 20);
	addArcoPonderado(g, 2, 1, 20);

	addArcoPonderado(g, 2, 0, 10);
	addArcoPonderado(g, 0, 2, 10);

	addArcoPonderado(g, 2, 3, 30);
	addArcoPonderado(g, 3, 2, 30);

  	float avgDist = 0.0;
  	float avgPath = 0.0;
	int source = 0;


	//EXECUTA DIJKSTRA PARA TODAS OS NODOS;
	for(source = 0; source < g->vertices.size() ; source++){ ////
		Node* node_source = NULL;
		dijkstra(g, source); //EXECUTA DIJKSTRA PARA UM NODO EXISTENTE;
		node_source = buscaNode(g, source);

		//ANALISANDO OS ADJACENTES.;
		for(int i = 0; i < g->vertices.size(); i++){

			if(i != source){

				avgDist += g->vertices.at(i)->dist; //ARMAZENA A DISTANCIA TOTAL ATE OUTRO NODO "i";
				cout << g->vertices.at(i)->dist << endl;
				caminhos = achaRota(g, source, i); //ACHA ROTA PARA TODOS ADJACENTES;
				cout << caminhos->size() << endl;
				avgPath += caminhos->size(); //ARMAZENA O TAMANHO DO CAMINHO (EM # DE NODOS);

			}
		}

		avgPath /= g->vertices.size(); //CALCULA A MEDIA DO TAMANHO DO CAMINHO (# DE NODOS) DE "source" para "i";
		cout << "Media do tamanho do caminho p/ a fonte " << source << ": " << avgPath << endl;
		avgPath = 0;

		avgDist /= g->vertices.size(); //CALCULA A MEDIA
		cout << "Media do tamanho da distancia p/ a fonte " << source << ": " << avgDist << endl;
		avgDist = 0;

	}

	//imprimirGrafo(g);
	//A=kCaminhos(g, 1, 3, 2);


	//dijkstra(g, 1);
	//printf("%f \n", buscaNode(g, 3)->dist);
	/*for(i=0;i<A->c->size();i++){
		for(a=0;a<A->c->at(i)->size();a++)
			printf("%d ", A->c->at(i)->at(a));
	}*/
	//ordenacaoTopologica(g);

}
