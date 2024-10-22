#include <stdio.h>
#include <stdlib.h> 

/* ********************************************* */
/* *** estrutura da lista e tamanho do grafo *** */
/* ********************************************* */

#define N 6
#define TRUE 1
#define FALSE 0

typedef struct _no {
	int id;
	struct _no *proximo;
} NoLista;

/* ********************************************* */
/* ***          funcoes auxiliares           *** */
/* ********************************************* */

void imprimeGrafo(int g[N][N]){
	int lin, col;
	printf("MATRIZ DE ADJACENCIA DO GRAFO\n");
	
	for(lin=0; lin<N; lin++){
		for(col=0; col<N; col++){
			printf("%d\t", g[lin][col]);
		}
		printf("\n");	
	}

} // fim da rotina que imprime o grafo




/* inicializa a lista ------------------------------------------------- */
void inicializaLista (NoLista **lista) {
    
    *lista = NULL;

} /* fim de inicializaLista */

/* verifica se a lista esta vazia ------------------------------------- */
int estaVazia (NoLista *lista) {

    return (lista == NULL);

} /* fim de estaVazia */

/* adiciona um elemento no final da lista ----------------------------- */
void insereFinal (NoLista **lista, int id) {

    NoLista *atual = *lista;
    NoLista *novo;
    
    novo = (NoLista*) malloc (sizeof(NoLista));
    novo->id = id;

    if (estaVazia(*lista)) {
        *lista = novo;
        novo->proximo = NULL;
        return;
    }

    while (atual->proximo != NULL)
        atual = atual->proximo;

    atual->proximo = novo;
    novo->proximo = NULL;

} /* fim de insereFinal */

/* remove o elemento do inicio da lista ------------------------------- */
int removeInicio (NoLista **lista) {

    NoLista *atual = *lista;
    int id;

    if (estaVazia(*lista))
        return -1;

    *lista = atual->proximo;
    id = atual->id;
    free(atual);
    return id;

} /* fim de removeInicio */



/* ********************************************* */
/* ***          funcoes principais           *** */
/* ********************************************* */
void buscaEmLargura(int g[N][N], int x){
	NoLista *fila;
	int visitados[N];  
	int v, w;  
	        
	int i;
	
	inicializaLista(&fila);

	for (i=0; i<N; i++)
		visitados[i] = FALSE; 	


	visitados[x] = TRUE;
	printf("\nPercurso da busca em largura: %d ", x);

	insereFinal (&fila, x);
	while(!estaVazia(fila)){
		
		v = removeInicio(&fila);
		
		for(w=0; w<N; w++){
			if( (g[v][w]==TRUE) && (visitados[w]==FALSE) ){
				
				visitados[w] =  TRUE;
				printf("%d ", w);	
				
				insereFinal(&fila, w);
			}
		} 	
		
	} 

} 

void buscaP(int g[N][N], int v, int visitados[N]);

void buscaEmProfundidade(int g[N][N], int x) {
    int visitados[N];
    int i;

    for (i = 0; i < N; i++) {
        visitados[i] = FALSE;
    }
    printf("\nPercurso da busca em profundidade: ");
    buscaP(g, x, visitados);

}

void buscaP(int g[N][N], int v, int visitados[N]) {
    int w;
    visitados[v] = TRUE;

    printf("%d ", v);

    for(w = 0; w < N; w++) {
        if((g[v][w] == TRUE) && (visitados[w] == FALSE)) {
            buscaP(g, w, visitados);
        }
    }
}


int main(){

    // FAZER N = 5
	int grafo[N][N] = { {0, 1, 0, 0, 1},
						{1, 0, 1, 1, 1},
						{0, 1, 0, 1, 0},
						{0, 1, 1, 0, 1},
						{1, 1, 0, 1, 0}	};
 
    /* // FAZER N = 6
	int grafo[N][N] = { {0, 1, 1, 0, 0, 0},
	                    {1, 0, 1, 1, 0, 1},
	                    {1, 1, 0, 1, 1, 0},
	                    {0, 1, 1, 0, 1, 1},
	                    {0, 0, 1, 1, 0, 0},
	                    {0, 1, 0, 1, 0, 0} };


    // FAZER N = 10
/*	int grafo[N][N] = { {0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
	                    {1, 0, 1, 0, 1, 0, 1, 0, 0, 0},
	                    {1, 1, 0, 0, 1, 1, 0, 0, 0, 0},
	                    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
	                    {0, 1, 1, 0, 0, 1, 1, 0, 0, 0},
	                    {0, 0, 1, 1, 1, 0, 0, 1, 0, 0},
						{0, 1, 0, 0, 1, 0, 0, 1, 0, 1},
						{0, 0, 0, 0, 0, 1, 1, 0, 1, 0},
						{0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
						{0, 0, 0, 0, 0, 0, 1, 0, 1, 0} };
*/

    // FAZER N = 8
/*	int grafo[N][N] = { {0, 1, 1, 1, 0, 0, 0, 0},
	                    {0, 0, 0, 0, 0, 0, 0, 0},
	                    {0, 1, 0, 0, 1, 0, 1, 0},
	                    {1, 0, 0, 0, 1, 0, 0, 0},
	                    {0, 0, 0, 0, 0, 0, 0, 1},
	                    {0, 1, 0, 0, 0, 0, 0, 0},
						{0, 0, 0, 1, 0, 1, 0, 1},
						{0, 0, 0, 0, 0, 0, 0, 0} };
*/

	                  
	imprimeGrafo(grafo);
	
	buscaEmLargura(grafo, 2);
	
	printf("\n\n");
	
	buscaEmProfundidade(grafo, 2);	
	
	return 0;
	
}

