#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include<deque>
#include<stack>

#define INT_MAX 999999

using namespace std;

struct node{
	int recur;
	int index;
	int visited;
	float dist;//DISTANCIA MINIMA ENTRE A ORIGEM ATE OS PONTOS
	int prev;//ANTERIOR
	vector<float> *custo;
	vector<struct node*> *adj;
};
typedef struct node Node;

struct grafo{
		int m;
		vector<Node*> vertices;
};

typedef struct grafo Grafo;

struct caminhos{

	deque< deque<int>* > *c;
	deque<float> *custos;
	int tam;


};typedef struct caminhos Caminhos;


Grafo* criaGrafo(){

	Grafo *g = (Grafo*) malloc (sizeof(Grafo));
	g->m = 0;

	return g; 

}

int existeNode(Grafo *g, int index){

	for(int i = 0; i < g->vertices.size(); i++){
		if(g->vertices[i]->index == index) return 1;
	}

	return 0;

}

Node* addNode(Grafo *g, int index){

	if(!existeNode(g, index)){
		Node *n = (Node*) malloc(sizeof(Node));
		n->index = index;
		n->recur = 0;
		n->dist = -1;
		n->prev = -1;
		n->visited = 0;
		n->custo = new vector<float>;
		n->adj = new vector<Node*>;
		g->vertices.push_back(n);
		return n;
	}

	return NULL;
	
}



Node* buscaNode(Grafo* g, int index){

	int i = 0;

	for(i = 0; i < g->vertices.size(); i++){
		if(g->vertices[i]->index == index) {
			return g->vertices[i];
		}
	}

	return NULL;

}


void removeNode(Grafo *g, int index){

	int i = 0;

	vector<Node*>::iterator it;

	for(it = g->vertices.begin(); it != g->vertices.end(); it++){
		if((*it)->index == index) {
			g->vertices.erase(it);
			break;
		}
	}
}

void addArcoPonderado(Grafo *g, int i, int j, float custo){
	
	Node *node_i = buscaNode(g, i);
	Node *node_j = buscaNode(g, j);

	if(node_i == NULL){
		node_i = addNode(g, i);
	}
	if(node_j == NULL){
		node_j = addNode(g, j);
	}

	node_i->adj->push_back(node_j);
	//node_j->adj->push_back(node_i);
	node_i->custo->push_back(custo);
	//node_j->custo->push_back(custo);
	
	g->m += 1;

}

float getCusto(Grafo *g, int i, int j){
	int k;
	Node *node_i = buscaNode(g,i);
	
	for(k=0; k < node_i->adj->size(); k++){
		if(node_i->adj->at(k)->index == j){
			return node_i->custo->at(k);
		}
	}
	return -1;
}



void addArco(Grafo *g, int i, int j){
	
	Node *node_i = buscaNode(g, i);
	Node *node_j = buscaNode(g, j);

	if(node_i == NULL){
		node_i = addNode(g, i);
	}
	if(node_j == NULL){
		node_j = addNode(g, j);
	}

	node_i->adj->push_back(node_j);

	g->m += 1;

}

void addAresta(Grafo *g, int i, int j){
	
	addArco(g, i, j);
	addArco(g, j, i);

}

vector<Node*>* verticesAdj(Grafo *g, int i){
	
	Node* node = buscaNode(g, i);
	if (node != NULL){
		return node->adj;
	}else{
		return NULL;
	}

}

void imprimirLista(vector<Node*> *lista){

	for(int i = 0; i < lista->size(); i++){
		printf("%d ", lista->at(i)->index);
	}

	printf("\n");

}

void imprimirGrafo(Grafo *g){


	for(int i = 0; i < g->vertices.size(); i++){
		printf("Node %d: ", g->vertices.at(i)->index);
		printf("\n   Adj: ");
		imprimirLista(g->vertices.at(i)->adj);
	}

}

void removeArco(Grafo *g, int i, int j){
	
	Node *node_i = buscaNode(g, i);
	
	vector<Node*>::iterator it;
	vector<float>::iterator it2;

	for(it = node_i->adj->begin(), it2 = node_i->custo->begin(); it != node_i->adj->end(); it++, it2++){

		if((*it)->index == j) {
			node_i->adj->erase(it);
			node_i->custo->erase(it2);
			break;
		}

	}

	g->m -= 1;

}

void removeAresta(Grafo* g, int i, int j){

	removeArco(g, i, j);
	removeArco(g, j, i);

}

//PRIMEIRA PARTE DO CÓDIGO DA AULA DO DIA 22/01/2018 - BFS(BUSCA EM LARGURA)

int bsf(Grafo *g, int s, int t){ //ONDE S EH O NO INICIAL
	
	deque<Node*> fila;
	Node *aux;
	int i;
	
	for(i=0; i < g->vertices.size(); i++){
		g->vertices.at(i)->visited = 0;
	}

	aux = buscaNode(g, s);
	
	if(aux == NULL) return -1;
	fila.push_back(aux);//PEGA O ULTIMO ELEMENTO DA FILA
	
	while(!fila.empty()){
		aux = fila.front();//PEGA O PRIMEIRO ELEMENTO DA FILA
		fila.pop_front();
		aux->visited = 1;

		if (aux->index == t)return 1;
		//ITERANDO SOBRE OS ADJ E ADICIONANDO NA FILA		
		for(i=0; i< aux->adj->size(); i++){
			if(aux->adj->at(i)->visited == 0){
				fila.push_back(aux->adj->at(i));
			}		
		}		
				
				
			
	}
	return 0;
}

//FAZENDO A BUSCA POR PROFUNDIDADE
int dfs(Grafo *g, int s, int t){ //ONDE S EH O NO INICIAL
	
	stack<Node*> stack;
	Node *aux;
	int i;
	
	for(i=0; i < g->vertices.size(); i++){
		g->vertices.at(i)->visited = 0;
	}

	aux = buscaNode(g, s);
	
	if(aux == NULL) return -1;
	stack.push(aux);
	
	while(!stack.empty()){
		aux = stack.top();
		stack.pop();
		aux->visited = 1;

		if (aux->index == t)return 1;
		//ITERANDO SOBRE OS ADJ E ADICIONANDO NA FILA		
		for(i=0; i< aux->adj->size(); i++){
			if(aux->adj->at(i)->visited == 0){
				stack.push(aux->adj->at(i));
			}		
		}		
				
				
			
	}
	return 0;
}
//PROFUNDIDADE - VERSÃO RECURSIVA 
void dfsRec(Grafo* g, int s, int t){
	int i;
	Node *aux = buscaNode(g,s);
	aux->visited = 1;
	if(aux->index != t){
		for(i=0; i < aux->adj->size(); i++){
			if(aux->adj->at(i)->visited == 0){
				dfsRec(g, aux->adj->at(i)->index, t);
			}
		}
	}
}

//PROFUNDIDADE - VERSÃO RECURSIVA - Aula 23/01
int temCicloUtil(Grafo* g, Node *aux){
	int i;
	
	
	aux->recur = 1; //VERTICE AINDA NAO EXPLOROU TODOS OS FILHOS
	aux->visited = 1;

	for(i=0; i < aux->adj->size(); i++){
		if(aux->adj->at(i)->recur == 1){
			return 1;	
		}else{
			temCicloUtil(g, aux->adj->at(i));
		 }
	}
	aux->recur = 0; //VERTICE EXPLOROU TODOS OS FILHOS
	return 0;
}

int temCiclo(Grafo *g){
	int i;
	//ZERANDO A ESTRUTURA AUXILIAR (QUE VERIFICA SE O VÉRTICE ESTÁ OU NÃO NA RECURSÃO)
	for(i=0; i < g->vertices.size();i++){
		g->vertices.at(i)->recur = 0;
	}	
	//CHAMA A FUNÇÃO PARA VERIFICAR CICLIO A PARTIR DE CADA VÉRTICE DO GRAFO.
	for(i=0; i < g->vertices.size();i++){
		if(temCicloUtil(g, g->vertices.at(i))) return 1;
	}
	return 0;
		
}

void caminhoMinimo(Grafo *g, int s){ //ONDE S EH O NO INICIAL
	
	deque<Node*> fila;
	Node *aux;
	int i;
	
	for(i=0; i < g->vertices.size(); i++){
		g->vertices.at(i)->visited = 0;
		g->vertices.at(i)->prev = -1;
		g->vertices.at(i)->dist = 0;
	}

	aux = buscaNode(g, s);
	
	if(aux == NULL) return;

	fila.push_back(aux);//PEGA O ULTIMO ELEMENTO DA FILA
	
	while(!fila.empty()){
		aux = fila.front();//PEGA O PRIMEIRO ELEMENTO DA FILA
		fila.pop_front();
		aux->visited = 1;

		//ITERANDO SOBRE OS ADJ E ADICIONANDO NA FILA		
		for(i=0; i< aux->adj->size(); i++){
			if(aux->adj->at(i)->visited == 0){
				aux->adj->at(i)->dist = aux->dist + 1;
				aux->adj->at(i)->prev = aux->prev;
				fila.push_back(aux->adj->at(i));
			}		
		}		
						
	}
}

void posOrdemGrafo(Grafo *g, int s, stack<int> *stack){
//VERTICE S = 0;
	int i;
	Node *aux = buscaNode(g, s);
	aux->visited = 1;
	
	for(i=0; i< aux->adj->size(); i++){
		if(aux->adj->at(i)->visited == 0){
			posOrdemGrafo(g, aux->adj->at(i)->index, stack);
		}
	}
	stack->push(s);	
}

Grafo* transporGrafo(Grafo *g){
	int i, j;
	Grafo *grafoTranposto = new Grafo;
	
	for(i=0; i < g->vertices.size(); i++){
		for(j=0; j < g->vertices.at(i)->adj->size(); j++){
			//CRIA OS VÉRTICES INVERTIDOS
			addArco(grafoTranposto, g->vertices.at(i)->adj->at(j)->index, g->vertices.at(i)->index);
		}
	}
	return grafoTranposto;	

}

void dfsRec2(Grafo* g, int s, vector<int> *vertices){
	int i;
	Node *aux = buscaNode(g,s);
	aux->visited = 1;
	vertices->push_back(s);
	
		for(i=0; i < aux->adj->size(); i++){
			if(aux->adj->at(i)->visited == 0){
				dfsRec2(g, aux->adj->at(i)->index, vertices);
			}
		}
}



void componentesConexos(Grafo *g, int s){
	
	Grafo *grafoTransposto;
	int indiceNo, i, j;
	Node *nodeAtual;

	vector<vector<int>*> componentesConexos;
	//ORDEM EM QUE EH PRECISO APLICAR A BUSCA EM PROFUNDIDADE
	stack<int> *posOrdemPilha = new stack<int>;
	posOrdemGrafo (g, s, posOrdemPilha);
	
	//CRIA O GRAFO TRANSPOSTO
	grafoTransposto = transporGrafo(g);
	
	while(!posOrdemPilha->empty()){
		indiceNo = posOrdemPilha->top();
		posOrdemPilha->pop();
	
		nodeAtual = buscaNode(grafoTransposto, indiceNo);

		if(nodeAtual->visited == 0){
			vector<int> *vertices = new vector<int>;
			dfsRec2(grafoTransposto, indiceNo, vertices);	
			componentesConexos.push_back(vertices);
		}
	} 	
	for(i=0; i<componentesConexos.size(); i++){
		printf("Componente %d: \n", i);
		for(j=0; j<componentesConexos.at(i)->size(); j++){
			printf(" %d", componentesConexos.at(i)->at(j));
		}
		printf("\n");
	}
}

void ordenacaoTopologicaUtil(Grafo *g, Node *aux, stack<int> *pilha){

	int i;

	if(aux->visited == 0){
		aux->visited = 1;	
		for(i=0; i< aux->adj->size(); i++){
			if(aux->adj->at(i)->visited == 0){
				ordenacaoTopologicaUtil(g, aux->adj->at(i), pilha);
			}
		}
		pilha->push(aux->index);	
	}
}

void ordenacaoTopologica(Grafo *g){
	
	int i;
	stack<int> *pilha = new stack<int>;

	//ZERA A ESTRUTURA
	for(i=0; i<g->vertices.size(); i++){
		g->vertices.at(i)->visited = 0;
	}
	//CHAMA A FUNCAO PARA TODOS OS VERTICES DO GRAFO
	for(i=0; i< g->vertices.size(); i++){
		ordenacaoTopologicaUtil(g, g->vertices.at(i), pilha);
	}
	while(!pilha->empty()){
		printf("%d \n", pilha->top());
		pilha->pop();
	}
}

Node* obterMenorEstimativaDistancia(vector<Node*> *verticesNaoVisitados){

	int i;
	float menorDist = INT_MAX;
	Node *menorNode;
	vector<Node*>::iterator it;

	//OBTENHO A MENOR ESTIMATIVA DE DISTANCIA ENTRE OS NÓS NAO VISITADOS
	for(i=0; i < verticesNaoVisitados->size(); i++){
		if(verticesNaoVisitados->at(i)->dist < menorDist){		// como aqui testamos qual o menor se todos são intmax?
			menorDist = verticesNaoVisitados->at(i)->dist;
			menorNode = verticesNaoVisitados->at(i);
		}
	}
	for(it = verticesNaoVisitados->begin(); it != verticesNaoVisitados->end(); it++){
		if((*it)->dist == menorDist){
			verticesNaoVisitados->erase(it);
			break;
		}
	}
	return menorNode;
}

void dijkstra(Grafo *g, int s){
	int i;
	Node *noAtual;
	Node *noAdj;
	//LISTA CONTENDO TODOS OS VERTICES DO GRAFO
	vector<Node*> *verticesNaoVisitados = new vector<Node*>;
	
	//INICIALIZAÇÃO DE ACORDO COM O ALGORITMO
	for(i=0; i < g->vertices.size(); i++){
		if(g->vertices.at(i)->index == s){
			g->vertices.at(i)->dist = 0;	
		}else{
				g->vertices.at(i)->dist = INT_MAX;	//se aqui colocamos todas as dist como int max
		}
		
		if(g->vertices.at(i)->visited!=1){
		g->vertices.at(i)->prev = -1;
		
		verticesNaoVisitados->push_back(g->vertices.at(i));	// e aqui colocamos esses vertices no não visitados
	}
	}
	//ENQUANTO A LISTA DE VÉRTICES NAO VISITADOS NAO FOR VAZIA
	while(!verticesNaoVisitados->empty()){
		//OBTENHO O MENOR
		noAtual = obterMenorEstimativaDistancia(verticesNaoVisitados);
		
	

		//ATUALIZA A ESTIMATIVA DE DISTANCIA PARA TODOS OS ADJ
		for (i=0; i < noAtual->adj->size(); i++){

			noAdj = noAtual->adj->at(i);
			
			if(noAdj->dist > noAtual->dist
											+ getCusto(g, noAtual->index, noAdj->index)){
				noAdj->dist = noAtual->dist
											+ getCusto(g, noAtual->index, noAdj->index);
				
				noAdj->prev = noAtual->index;
			}
		}
	}
}

Caminhos* criaCaminhos(){
	Caminhos *A = (Caminhos*) malloc (sizeof(Caminhos));
	A->c = new deque< deque<int>* >; 
	A->custos = new deque<float>;
	return A;


}
	
Caminhos* kCaminhos(Grafo *g, int s, int t, int K){
	
	int k, i, j, l, cont, ind, custin;
	float menor;
	Caminhos *A = criaCaminhos();
	Caminhos *B = criaCaminhos();
	deque<int> *caminho = new deque<int>;
	deque<int> *rootPath = new deque<int>;
	Node *p;
	Node *spurNode;
	deque< deque<int>* >::iterator it;
	deque<float>::iterator it2;
	dijkstra(g, s);
	
	for(j=0; j <g->vertices.size(); j++)
	g->vertices.at(j)->visited=0;
	

	p=buscaNode(g, t);
	
	cont=0;
	do{
		
		caminho->push_front(p->index);
		//printf("%d a \n", p->index);
		p=buscaNode(g, p->prev);
		cont++;
	}while(p->index!=s);
	caminho->push_front(p->index);
	
	A->c->push_front(caminho);
	
	for(i=0;i<A->c->size();i++){
		for(j=0;j<A->c->at(i)->size();j++){
			printf("%d ", A->c->at(i)->at(j));
		}printf("\n");
	
	
	}printf("\n");
	
	
	k=1;
	while(k<K){
	
		i=0;
		while(i < (A->c->at(k-1)->size())-2){
			
			spurNode=buscaNode(g, A->c->at(k-1)->at(i));
			
			rootPath->push_back(A->c->at(k-1)->at(0));
			
			rootPath->push_back(A->c->at(k-1)->at(i));
			
			for(j=0;j<A->c->size();j++){
				if(rootPath->at(0)==A->c->at(j)->at(0) && rootPath->at(1)==A->c->at(j)->at(i)){
					p=buscaNode(g, i+1);
					for(j=0;j<p->adj->size();j++){
						if(p->adj->at(j)->index==i+1)
							custin=p->custo->at(j);
					}
					removeArco(g, i, i+1);
				}
			}
			
			if(rootPath->at(0)!=spurNode->index){
				p=buscaNode(g, rootPath->at(0));
				p->visited=1;
			
			}
			if(rootPath->at(1)!=spurNode->index){
				p=buscaNode(g, rootPath->at(1));
				p->visited=1;
			}
			

			dijkstra(g, spurNode->index);
			//printf("%d b\n", spurNode->index);
			caminho->clear();
			p=buscaNode(g, t);
			
			caminho->push_front(p->index);
			while(p->prev!=-1){
				
				//printf("%d c\n", p->index);
				//printf("%d d\n", p->prev);
				p=buscaNode(g, p->prev);
				caminho->push_front(p->index);
				
			}
			
			caminho->push_front(rootPath->at(1));
			caminho->push_front(rootPath->at(0));
			
			B->c->push_back(caminho);
			B->custos->push_back(buscaNode(g, t)->dist);
			
			if(rootPath->at(0)!=spurNode->index){
				p=buscaNode(g, rootPath->at(0));
				p->visited=0;
			
			}
			if(rootPath->at(1)!=spurNode->index){
				p=buscaNode(g, rootPath->at(1));
				p->visited=0;
			}
			
			for(j=0;j<A->c->size();j++){
				if(rootPath->at(0)==A->c->at(j)->at(0) && rootPath->at(1)==A->c->at(j)->at(i)){
					addArcoPonderado(g, i, i+1, custin);
					
					
					}
				}
			i+=1;
			rootPath->clear();
			}
		
		if(B->c->empty()) break;
		
		menor=999999;
		ind=0;
		
		for(j=0; j<B->custos->size();j++){
			if(B->custos->at(j)<menor){
				menor=B->custos->at(j);
				ind=j;
			}
		}
		A->c->push_back(B->c->at(ind));
		A->custos->push_back(menor);
		//it=ind;
		//B->c->erase(ind);
		//it2=ind;
		//B->custos->erase(it2);
		/*for(it = B->c->begin(), it2 = B->custos->begin(), t=0; it != B->c->end(); it++, it2++, l++){

			if(l == ind) {
				B->c->erase(it);
				B->custos->erase(it2);
				break;
			}

		}*/
		B->c->clear();
		B->custos->clear();
	k++;
	}
	return A;
	}

	

int main(){
	
	Grafo *g = new Grafo();
	Caminhos *A;
	int i, a, b, capacidade, j;
	float cust;
	for(i=0;i<114;i++){
		scanf("%d %d %d %f", &a, &b, &capacidade, &cust);
		addArcoPonderado(g, a, b, cust);
	
	
	}
	//addArcoPonderado(g, 0, 1, 1);
	//addArcoPonderado(g, 1, 3, 1);
	//addArcoPonderado(g, 2, 3, 2);
	//addArcoPonderado(g, 1, 2, 1);
	
	imprimirGrafo(g);
	A=kCaminhos(g, 2, 4, 2);
	
	for(i=0;i<A->c->size();i++){
		for(j=0;j<A->c->at(i)->size();j++){
			printf("%d ", A->c->at(i)->at(j));
		}printf("\n");
	
	
	}printf("\n");
	//dijkstra(g, 0);
	
	
	//ordenacaoTopologica(g);	
	
}
