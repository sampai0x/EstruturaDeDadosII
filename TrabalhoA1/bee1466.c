//Cauã Pirateli Bertin - RA: 114600. BEEID: 804067
//Claudevan Moreira da Costa Junior - RA: 115478. BEEID: 804018
//Emerson Osvaldo Menegatti Junior - RA: 112301. BEEID: 872881
//Pedro Henrique Pereira Pinto - RA: 115879. BEEID: 821863 
//Pedro Lucas Sampaio - RA: 115919. BEEID: 813025

#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

typedef struct noArv{
	int numero;
	struct noArv *direita;
	struct noArv *esquerda;
} noArv;

int imprimirNivelArvore(noArv *);
noArv* push(noArv *, int );

int qtsNos;

int main (){
	int i, num, qtsNum;
	int qtsCasos, caso;

	scanf("%u", &qtsCasos);

	caso = 0;
	while (qtsCasos--){
		scanf("%u", &qtsNum);

		qtsNos = 0;
		noArv *no = NULL;
		for (i = 0; i < qtsNum; ++i){

			scanf("%u", &num);
			no = push(no, num);
			++qtsNos;

        }
		printf("Case %u:\n", ++caso);
		imprimirNivelArvore(no);
		printf("\n\n");
	}
}

noArv* push(noArv *no, int numero){
	if (!no){

		no = (noArv *) malloc(sizeof(noArv));
		no->numero = numero;
		no->esquerda = no->direita = NULL;

	}
	else if (no->numero > numero)
		no->esquerda = push(no->esquerda, numero);
	else
		no->direita = push(no->direita, numero);
	return no;
}

int imprimirNivelArvore(noArv *no){
    noArv *fila;
    unsigned i, f;
    int flag = 0;  

    fila = (noArv *) malloc(qtsNos * sizeof(noArv));
    fila[0] = *no;
    i = 0; f = 1;

    while (f > i){
        *no = fila[i++];
        if (!flag) {
            printf("%u", no->numero);
            flag = 1; 
        } else {
            printf(" %u", no->numero);
        }

        if (no->esquerda)
            fila[f++] = *no->esquerda;
        if (no->direita)
            fila[f++] = *no->direita;
    }
    free(fila);
}
