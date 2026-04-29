#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "struct.h"

#define MAX 100

node* CriaNo(int num){
    //Cria um node
    node* Novo = malloc(sizeof(node));
    Novo->vertice = num;
    Novo->adj = NULL;
    return Novo;
}

grafo* CriaGrafo(int vertices){
    //Cria grafo
    grafo* Grafo = malloc(sizeof(grafo));
    Grafo->Nvertices = vertices;
    Grafo->ListaAdj = malloc(vertices* sizeof(node*)); //Lista de adjacentes
    for(int i = 0; i < vertices; i++){
        Grafo->ListaAdj[i] = NULL;
    }
    return Grafo;
}

void Arestas(grafo* grafo, int a, int b){
    //Cria as arestas
    if(a != b){ //se forem iguais iria duplicado
        node* NovoNo = CriaNo(b);
        NovoNo->adj = grafo->ListaAdj[a];
        grafo->ListaAdj[a] = NovoNo;

        NovoNo = CriaNo(a);
        NovoNo->adj = grafo->ListaAdj[b];
        grafo->ListaAdj[b] = NovoNo;
    }

    else{
        node* NovoNo = CriaNo(b);
        NovoNo->adj = grafo->ListaAdj[a];
        grafo->ListaAdj[b] = NovoNo;
    }
}

void PrintaGrafo(grafo* grafo, int**matrix){
    for(int j = 0; j < grafo->Nvertices; j++){
        node* temp = grafo->ListaAdj[j];
        
        printf("\nO vertice %d liga em :", j);
        
        while(temp){ //enquanto tem adjacentes printa
            if(temp->vertice || matrix[j][(temp->vertice)] != 0){
                printf(" %d (%d) |", temp->vertice, matrix[j][(temp->vertice)]);
                temp = temp->adj;
            }
        }
        if(j+1 == grafo->Nvertices){
            printf(" >>> Node base <<<");
        }
        printf("\n");
    }
    printf("\n");
}

int** CriaMatrix(int vertices){
    //matrix para armazenar os pesos
    int** matrix = malloc(sizeof(int*)* vertices);
    for(int i = 0; i < vertices; i++){
        matrix[i] = calloc(vertices, sizeof(int));
    }
    return matrix;
}

void PrintaMatrix(grafo* grafo, int** matrix){
    int vertices = grafo->Nvertices;
    for(int i = 0; i < vertices; i++){
        for(int j = 0; j < vertices; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int Adjacentes(grafo* grafo, int a, int b){
    //verifica se dois nodes sao adjacentes
    int peso = 0;
    node* temp = grafo->ListaAdj[a];
    while(temp){
        if(temp->vertice == b){
        //o que fazer com o peso em PROCESSO
            return 1;
            break;
        }
        temp = temp->adj;
    }
}

void CaminhoDks(grafo* grafo, int a, int b, int** matrix){
    int vertices = grafo->Nvertices;
    int ant[MAX]; //antecessores
    int caminho[MAX]; //vertices já vistitados
    int dist[MAX]; //custo
    int v, i, min;
    
    for(int i = 0; i < vertices; i++){ //inicialização
        if(matrix[a][i] != 0){
            ant[i] = a;
            dist[i] = matrix[a][i];
        }
        else{
            ant[i] = -1;
            dist[i] = 100000;
        }
        caminho[i] = 0;
    }
    caminho[a] = 1;
    dist[a] = 0;

    do{
        min = 100000;
        v = -1;

        for(int i = 0; i < vertices; i++){
            if(!caminho[i] && dist[i] < min){
                min = dist[i];
                v = i;
            }
        }

        if(v == -1){
            break;
        }

        caminho[v] = 1;
        for(i = 0; i < vertices; i++){
            if(!caminho[i] && matrix[v][i] > 0){
                if(dist[v] + matrix[v][i] < dist[i]){
                    dist[i] = dist[v] + matrix[v][i]; 
                    ant[i] = v;
                }
            }
        }

    }while(v != b);

    if(min == 100000){
        if(a == b){
            printf("%d eh o mesmo no que %d\n", a, b);
        }
        else{
            printf("Nao tem caminho entre %d e %d\n", a, b);
        }
    }
    else{
        printf("O caminho entre %d e %d na ordem inversa \n", a, b);
        i = b;
        while(i != -1){
            printf("%d ", i);
            if(ant[i] != -1){
                printf("<- ");
            }
            i = ant[i];
        }
        printf("\nO custo foi de %d \n", dist[b]);
    }
}

int CalculaGrau(grafo* grafo, int a){
    int vertices = grafo->Nvertices;
    int grau = 0;
    node* temp = grafo->ListaAdj[a];
    for(int i = 0; i < vertices; i++){
        while(temp){
            if(temp->vertice || temp->vertice == 0){
                grau++;
            }
            temp = temp->adj;
        }
    }
    return grau;
}

float Media(grafo* grafo){
    int vertices = grafo->Nvertices;
    float soma = 0;
    for(int i = 0; i < vertices; i++){
        soma += CalculaGrau(grafo, i);
    }
    float mediaT = soma/vertices;
    return mediaT;
}

void Isolado(grafo* grafo){
    int vertices = grafo->Nvertices;
    int isolado[MAX];
    int v = 0;
    printf("\nOs nodes isolados: ");
    for(int i = 0; i < vertices; i++){
        if(CalculaGrau(grafo, i) == 0){
            isolado[v] = i;
            printf("%d | ", isolado[i]);
        }
        v++;
    }
}

int Max(grafo* grafo){
    int vertices = grafo->Nvertices;
    int max = 0;
    int node = 0;
    for(int i = 0; i < vertices; i++){
        int grau = CalculaGrau(grafo, i);
        if(grau > max){
            max = grau;
            node = i;
        }
    }
    return max;
}

int Min(grafo* grafo){
    int vertices = grafo->Nvertices;
    int min = MAX;
    for(int i = 0; i < vertices; i++){
        int grau = CalculaGrau(grafo, i);
        if(grau < min){
            min = grau;
        }
    }
    return min;
}

void DesconectArest(grafo* grafo){
    int vertices = grafo->Nvertices;
    if(Min(grafo) == 0){
        printf("O grafo ja ta desconectado pelos: ");
        Isolado(grafo);
        printf("\n");
    }
    else{
        printf("\nO numero de enlaces para desconectar a rede eh de %d\n", Min(grafo));
    }
}

void Agrupa(grafo* grafo, int a, int** matrix){
    if(CalculaGrau(grafo, a) == 0){
        printf("\nO %d nao possui adjacentes\n", a);
        return;
    }
    printf("\nOs vizinhos de %d sao:", a);
    int meio[MAX];
    int v = 0;
    for(int i = 0; i < grafo->Nvertices; i++){
        if(matrix[a][i] != 0){
            meio[v] = i;
            printf(" %d |", meio[v]);
            v++;
        }
    }
    printf("\n");
    float cont = 0;
    float vdd = 0;
    for(int i = 0; i < v; i++){
        for(int j = 0; j < v; j++){
            if(i != j && i < j){
                if(Adjacentes(grafo, meio[i], meio[j]) == 1){
                    printf("%d e %d sao adjacentes\n", meio[i], meio[j]);
                    vdd++;
                }
                else{
                    printf("%d e %d nao sao adjacentes\n", meio[i], meio[j]);
                }
                cont++;
            }
        }   
    }
    float cc = vdd/cont;
    printf("o CC de %d eh %.2f\n", a, cc);
}

void Mata(grafo* grafo, int a, int** matrix){
    int vertices = grafo->Nvertices;
    if(a > grafo->Nvertices || a < 0 || !grafo){
        printf("node invalido!\n");
        return;
    }

    node* atual;
    node* antigo;

    for(int i = 0; i < vertices; i++){
        // remove as aparições de a nas listas
        atual = grafo->ListaAdj[i];
        antigo = NULL;

        while(atual){
            if(atual->vertice == a){
                if(antigo == NULL){
                    grafo->ListaAdj[i] = atual->adj;
                }
                else{
                    antigo->adj = atual->adj;
                }
                node* temp = atual;
                atual = atual->adj;
                free(temp);
            }
            else{
                antigo = atual;
                atual = atual->adj;
            }
        }
    }

    //remove a lista de a
    atual = grafo->ListaAdj[a];
    while(atual){
        node* temp = atual;
        atual = atual->adj;
        free(temp);
    }

    //move as listas
    for(int i = a ; i < vertices - 1; i++){
        grafo->ListaAdj[i] = grafo->ListaAdj[i+1];
    }

    //ajusta os indices
    for(int i = 0; i < vertices - 1; i++){
        atual = grafo->ListaAdj[i];
        while(atual){
            if(atual->vertice > a){
                atual->vertice--;
            }
            atual = atual->adj;
        }
    }

    grafo->Nvertices--; //diminui n vertices

    node** temp = realloc(grafo->ListaAdj, grafo->Nvertices * sizeof(node*)); //realocar memoria
    if(temp){
        grafo->ListaAdj = temp;
    }

    //matrix
    //zera os pesos
    for(int i = 0; i < vertices - 1; i++){
        matrix[a][i] = 0;
        matrix[i][a] = 0;
    }

    //move a matrix na horizontal e na vertical
    for(int i = a; i < vertices - 1; i++){
        for(int j = 0; j < vertices; j++){
            matrix[i][j] = matrix[i+1][j];
        }
    }
    for(int i = 0; i < vertices - 1; i++){
        for(int j = a; j < vertices - 1; j++){
            matrix[i][j] = matrix[i][j+1];
        }
    }


    printf("\nO node %d foi removido\n", a);
    Recalcular(grafo, matrix);

}

void Recalcular(grafo* grafo, int** matrix){
    printf("\nDESEJA RECALCULAR TUDO PARA O NOVO GRAFO? 1 (sim) ou 2 (nao): \n");
    int resp = 0;
    scanf("%d", &resp);
    if(resp == 1){
        PrintaMatrix(grafo, matrix);
        PrintaGrafo(grafo, matrix);
        CaminhoDks(grafo, 0, grafo->Nvertices - 1, matrix);
        printf("\nGrau de %d: ", 4);
        printf("%d\n", CalculaGrau(grafo, 4));
        printf("Media de graus: %.2f\n", Media(grafo));
        printf("O maior grau eh: %d\n", Max(grafo));
        DesconectArest(grafo);
    }
    else{
        printf("\nOk! :D\n");
    }
}
