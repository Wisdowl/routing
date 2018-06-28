#include "header.h"
#include "estruturaGrafos.cpp"
#include "buscasOrdenacoes.cpp"

using namespace std;

int main(){
	Grafo *g = new Grafo();
	Caminhos *A = NULL;
	int i, a, b, capacidade;
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

	imprimirGrafo(g);
	A=kCaminhos(g, 1, 3, 2);

	//printf("%f \n", buscaNode(g, 3)->dist);
	/*for(i=0;i<A->c->size();i++){
		for(a=0;a<A->c->at(i)->size();a++)
			printf("%d ", A->c->at(i)->at(a));
	}*/
	//ordenacaoTopologica(g);

}
