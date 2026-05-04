#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "struct.h"
#include <Windows.h>

int main(){

    printf("Coloque as infos necessarias para a criacao do grafo: vertices e arestas e depois os pares com os pesos:\n");

    int vertices = 0;
    scanf("%d", &vertices);
    int arestas = 0;
    scanf("%d", &arestas);

    grafo* grafo = CriaGrafo(vertices);
    int** matrix = CriaMatrix(vertices);
    
    CriArestas(grafo, matrix, arestas);

    int* criticos = NodesCritcos(grafo);

    printf("\nEbaa!! O grafo feito com sucesso! :D\nPossui %d nos e %d arestas\n", vertices, arestas);

    Pergunta(grafo, matrix, criticos);

    return 0;
}
