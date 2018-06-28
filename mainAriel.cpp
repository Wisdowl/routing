#include "header.h"
#include "estruturaGrafos.cpp"
#include "buscasOrdenacoes.cpp"

using namespace std;

int main(){

	Grafo *g = new Grafo();
	deque<Node*> *caminhos = new deque<Node*>;
	int i, a, b, capacidade;
	float custo;

	for(i = 0; i < 114; i++){
		scanf("%d %d %d %f", &a, &b, &capacidade, &custo);
		addArcoPonderado(g, a, b, custo);
	}

	//dijkstraMedia(g);
	//dijkstraMediaNAO_ADJ(g, caminhos);
	//Node* node_source = g->vertices.adj->at(0);
	//cout << node_source << endl;
	/*addArcoPonderado(g, 0, 1, 12);
	addArcoPonderado(g, 1, 0, 12);

	addArcoPonderado(g, 1, 2, 20);
	addArcoPonderado(g, 2, 1, 20);

	addArcoPonderado(g, 2, 0, 10);
	addArcoPonderado(g, 0, 2, 10);

	addArcoPonderado(g, 2, 3, 30);
	addArcoPonderado(g, 3, 2, 30);*/


	return 0;
}
