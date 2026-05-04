#ifndef GRAFO_S
#define GRAFO_S

#define MAX 100

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

void CriArestas(grafo* grafo, int** matrix, int arestas);

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

void BuscArticula(grafo* grafo, int a, int pai);

int Conexo(grafo* grafo, int conte);

int Completo(grafo* grafo);

int* NodesCritcos(grafo* grafo);

void DesconectNode(grafo* grafo, int* criticos);

void PrintaCriticos(grafo* grafo, int* criticos);

void Agrupa(grafo* grafo, int a, int** matrix);

void Mata(grafo* grafo, int a, int** matrix, int* criticos);

void Recalcular(grafo* grafo, int** matrix, int* criticos);

int Menu();

void Pergunta(grafo* grafo, int** matrix, int* criticos);

#endif 
