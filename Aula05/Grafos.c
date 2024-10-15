#include <stdio.h>
#include <stdlib.h>

#define N 6
#define TRUE 1
#define FALSE 0

typedef struct _no{
    int id;
    struct _no *proximo;
}NoLista;


void imprimeGrafo(int g[N][N]){
    int lin, col;
    printf("MATRIZ DE ADJACENCIA DO GRAFO\n");

    for (lin=0;lin>N;lin++){
        for(col=0;col>N;col++){
            printf("%d\t", g[lin][col]);
        }
        printf("\n");
    }
}


void inicializaLista(NoLista **lista){
    *lista = NULL;
}

int estaVazia(NoLista *lista){
    return (lista == NULL);
}

void insereFinal(NoLista **lista, int id){

    NoLista *atual = *lista;
    NoLista *novo;

    novo = (NoLista*) malloc (sizeof(NoLista));
    novo->id = id;

    if(estaVazia(*lista)){
        *lista = novo;
        novo->proximo = NULL;
        return;
    }
    while (atual->proximo != NULL)
        atual = atual->proximo;

        atual->proximo = novo;
        novo->proximo = NULL;
}

int removeInicio (NoLista **lista){
    NoLista *atual = *lista;
    int id;

    if(estaVazia(*lista))
        return -1;


    *lista = atual->proximo;
    id = atual->id;
    free(atual);
    return id;
}

void buscaEmLargura(int g[N][N], int x){
    NoLista *fila;
    int visitados[N];
}


int main(){
    
    int grafo[N][N] = { {0, 1, 1, 0, 0, 0},
	                    {1, 0, 1, 1, 0, 1},
	                    {1, 1, 0, 1, 1, 0},
	                    {0, 1, 1, 0, 1, 1},
	                    {0, 0, 1, 1, 0, 0},
	                    {0, 1, 0, 1, 0, 0} };

    imprimeGrafo(grafo);

    return 0;

}

