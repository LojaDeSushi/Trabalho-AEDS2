#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "struct.h"

int main(){

    int vertices = 0;
    scanf("%d", &vertices);
    int arestas = 0;
    scanf("%d", &arestas);

    grafo* grafo = CriaGrafo(vertices);
    int** matrix = CriaMatrix(vertices);

    for(int i = 0; i < arestas; i++){
        int a;
        int b;
        int peso;
        scanf("%d", &a);
        scanf("%d", &b);
        scanf("%d", &peso);

        Arestas(grafo, a, b);

        matrix[a][b] = peso;
        matrix[b][a] = peso;
    }

    printf("\nEbaa!! O grafo feito com sucesso! :D\nPossui %d nos e %d arestas\n", vertices, arestas);

    //pesos
    printf("\nMatrix de pesos:\n");
    PrintaMatrix(grafo, matrix);

    //topografia grafo
    PrintaGrafo(grafo, matrix);

    //caminho de a ate b
    for(int i = 0; i < vertices; i++){
        CaminhoDks(grafo, i, vertices - 1, matrix);
        printf("\n");
    }

    //grau de a
    printf("Grau de %d: ", 2);
    printf("%d\n", CalculaGrau(grafo, 2));

    //grau medio
    printf("Media de graus: %.2f\n", Media(grafo));

    //maior grau
    printf("O maior grau eh: %d\n", Max(grafo));

    
    //quantos enlaces para desconectar
    DesconectArest(grafo);

    Agrupa(grafo, 0, matrix);
    
    //Mata(grafo, 4, matrix);

    return 0;
}