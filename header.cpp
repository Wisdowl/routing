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
