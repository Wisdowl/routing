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
