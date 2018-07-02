using namespace std;

Grafo* criaGrafo(){

	Grafo *g = (Grafo*) malloc(sizeof(Grafo));
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
	node_i->custo->push_back(custo);

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


Node* obterMenorEstimativaDistancia(vector<Node*> *verticesNaoVisitados){

	int i;
	float menorDist = INT_MAX;
	Node *menorNode;
	vector<Node*>::iterator it;

	//OBTENHO A MENOR ESTIMATIVA DE DISTANCIA ENTRE OS NÓS NAO VISITADOS
	for(i=0; i < verticesNaoVisitados->size(); i++){
		if(verticesNaoVisitados->at(i)->dist < menorDist){
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
				g->vertices.at(i)->dist = INT_MAX; //aqui colocamos todas as dist como int max
		}
		g->vertices.at(i)->prev = -1;

		verticesNaoVisitados->push_back(g->vertices.at(i)); //e aqui colocamos esses vertices no não visitados
	}


	//ENQUANTO A LISTA DE VÉRTICES NAO VISITADOS NAO FOR VAZIA
	while(!verticesNaoVisitados->empty()){
		//OBTENHO O MENOR

		noAtual = obterMenorEstimativaDistancia(verticesNaoVisitados);

		noAtual->visited = 1;

		//ATUALIZA A ESTIMATIVA DE DISTANCIA PARA TODOS OS ADJ
		for (i=0; i < noAtual->adj->size(); i++){

			noAdj = noAtual->adj->at(i);

			if(noAdj->dist > noAtual->dist + getCusto(g, noAtual->index, noAdj->index)){
				noAdj->dist = noAtual->dist + getCusto(g, noAtual->index, noAdj->index);
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
	p=buscaNode(g, t);

	cont=0;
	do{
		caminho->push_front(p->index);
		p=buscaNode(g, p->prev);
		cont++;
	}while(p->index!=s);

	A->c->push_front(caminho);

	k=1;
	while(k<K){

		i=0;
		while(i<cont-2){
			spurNode=buscaNode(g, A->c->at(k-1)->at(i));
			rootPath->at(0)=A->c->at(k-1)->at(0);
			rootPath->at(1)=A->c->at(k-1)->at(i);

			for(j=0;j<A->c->size();j++){
				if(rootPath->at(0)==A->c->at(j)->at(0) && rootPath->at(1)==A->c->at(j)->at(i)){
					p=buscaNode(g, i);
					for(j=0;j<p->adj->size();j++){
						if(p->adj->at(i)->index==i+1)
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
			caminho->clear();
			p=buscaNode(g, t);


			do{
				caminho->push_front(p->index);
				p=buscaNode(g, p->prev);
			}while(p->index!=s);

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
			}

		if(B->c->empty()) break;

		menor=9999999;
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
		for(it = B->c->begin(), it2 = B->custos->begin(), t=0; it != B->c->end(); it++, it2++, l++){

		if(l == ind) {
			B->c->erase(it);
			B->custos->erase(it2);
			break;
		}

	}

	}
	return A;
}


//GERA A ROTA PARA DOIS NODOS QUAISQUER;
deque<Node*> * achaRota(Grafo* g, int i, int j){

	deque<Node*> *caminho = new deque<Node*>;
	Node* node_i = buscaNode(g, i); //VERITIFCA SE OS NODOS EXISTEM;
	Node* node_j = buscaNode(g, j); //VERIFICA SE OS NODOS EXISTEM;
	Node* node_prev;

	if(node_i != NULL && node_j != NULL){

	//SE AMBOS EXISTIREM...
	//FAÇA...
	  node_prev = buscaNode(g, node_j->prev); //PEGA O NODO ANTERIOR;
		while(node_prev != NULL){
			caminho->push_front(node_prev); //COLOCA O ANTERIOR NO CAMINHO;
			node_prev = buscaNode(g, node_prev->prev);
		}
		caminho->push_back(node_j);

	}
	else{
		printf("ROTA INVALIDA!\n");
		return NULL;
	}
	return caminho;
}


//EXECUTA DIJKSTRA PARA TODAS OS NODOS;
void dijkstraMedia(Grafo* g, deque<Node*> *caminhos){

	float avgDist = 0.0;
	float avgPath = 0.0;
	int source = g->vertices.front()->index;

	for(source; source < g->vertices.size(); source++){
		Node* node_source = NULL;
		dijkstra(g, source); //EXECUTA DIJKSTRA PARA UM NODO EXISTENTE;

		//ANALISANDO OS ADJACENTES.;
		for(int i = 0; i < g->vertices.size(); i++){

			if(i != source){

				avgDist += g->vertices.at(i)->dist; //ARMAZENA A DISTANCIA TOTAL ATE OUTRO NODO "i";
				caminhos = achaRota(g, source, i); //ACHA ROTA PARA TODOS ADJACENTES;
				avgPath += caminhos->size(); //ARMAZENA O TAMANHO DO CAMINHO (EM # DE NODOS);

			}
		}

		avgPath /= g->vertices.size(); //CALCULA A MEDIA DO TAMANHO DO CAMINHO (# DE NODOS) DE "source" para "i";
		cout << "(Adjacentes) Media do tamanho do caminho p/ a fonte " << source << ": " << avgPath << endl;
		avgPath = 0;

		avgDist /= g->vertices.size(); //CALCULA A MEDIA
		cout << "(Adjacentes) Media do tamanho da distancia p/ a fonte " << source << ": " << avgDist << endl;
		avgDist = 0;
	}
}

void dijkstraMediaNAO_ADJ(Grafo* g, deque<Node*> *caminhos){

	float avgDist = 0.0;
	float avgPath = 0.0;
	int source = g->vertices.front()->index;

	for(source; source < g->vertices.size(); source++){

		Node* node_source = NULL;
		dijkstra(g, source);

		for(int i = 0; i < g->vertices.size(); i++){
			if(i != source){
				for(int j = 0; i < g->vertices.adj->size(); j++){
					if(i != node_source->adj->at(i)->index){
						avgDist += g->vertices.at(i)->dist; //ARMAZENA A DISTANCIA TOTAL ATE OUTRO NODO "i";
						caminhos = achaRota(g, source, i); //ACHA ROTA PARA TODOS ADJACENTES;
						avgPath += caminhos->size(); //ARMAZENA O TAMANHO DO CAMINHO (EM # DE NODOS);
					}
				}

			}
		}

		avgPath /= g->vertices.size(); //CALCULA A MEDIA DO TAMANHO DO CAMINHO (# DE NODOS) DE "source" para "i";
		cout << "(NAO Adjacentes) Media do tamanho do caminho p/ a fonte " << source << ": " << avgPath << endl;
		avgPath = 0;

		avgDist /= g->vertices.size(); //CALCULA A MEDIA
		cout << "(NAO Adjacentes) Media do tamanho da distancia p/ a fonte " << source << ": " << avgDist << endl;
		avgDist = 0;

	}



}
