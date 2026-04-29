#ifndef GRAFO_S
#define GRAFO_S

typedef struct node{
    int vertice;
    struct node* adj;
}node;

typedef struct grafo{
    int Nvertices;
    node** ListaAdj;
}grafo;

node* CriaNo(int num);

grafo* CriaGrafo(int vertices);

void Arestas(grafo* grafo, int a, int b);

void PrintaGrafo(grafo* grafo, int** matrix);

int** CriaMatrix(int vertices);

void PrintaMatrix(grafo* grafo, int** matrix);

int Adjacentes(grafo* grafo, int a, int b);

void CaminhoDks(grafo* grafo, int a, int b, int** matrix);

int CalculaGrau(grafo* grafo, int a);

float Media(grafo* grafo);

void Isolado(grafo* grafo);

int Max(grafo* grafo);

int Min(grafo* grafo);

void DesconectArest(grafo* grafo);

void Agrupa(grafo* grafo, int a, int** matrix);

void Mata(grafo* grafo, int a, int** matrix);

void Recalcular(grafo* grafo, int** matrix);


#endif 