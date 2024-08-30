#include <stdio.h> 
#include <stdlib.h>

#define TRUE 1
#define QDEUF 27

/* ------------------------------------------------ */
typedef struct _No{
    char uf[3];
    float ano2015;
    float ano2016;
    float ano2017;
    float ano2018;
    float ano2019;
    struct _No *pai;
    struct _No *esq;
    struct _No *dir;
} No;

void inicializar (No **raiz){
	*raiz = NULL;
}

int estaVazia(No *raiz){
	if(raiz == NULL){
		return 1;
	}
	
	return 0;
}

void emOrdem(No *raiz){
	if(!estaVazia(raiz)){
		emOrdem(raiz->esq);
		printf("%d", raiz->id);
		emOrdem(raiz->dir);
	}
}




int main(){

    No *arvore;    // declaração do ponteiro que aponta para a raiz da árvore
    No *aux;
	No temp;

    FILE *arq;

	int op, ano;
	float media;
	char uf[3];
	
    inicializar(&arvore);   // atribuir nulo para a raiz

	while(TRUE){
		printf("Menu\n");
		printf("1 - Carregar dados das UFs\n");
		printf("2 - Exibir dados de todas as UFs\n");
		printf("3 - Exibir dados de uma UF\n");
		printf("4 - Excluir uma UF\n");
		printf("5 - Esvaziar a BST\n");
		printf("6 - Calcular a media brasileira em um ano especifico\n");
		printf("0 - Sair\n");
	
		printf("\nEscolha uma opcao: ");
		scanf("%d", &op);

		switch(op){
		
		case 1:
			arq = fopen("A04ODS392.txt", "r");	
			if (arq == NULL) {
		       printf("Problemas na abertura do arquivo A04ODS392.txt\n");
		 	   exit(0);	   
			}
				
			while(fscanf(arq, "%s %f %f %f %f %f", temp.uf, &temp.ano2015, &temp.ano2016, &temp.ano2017, &temp.ano2018, &temp.ano2019) == 6)
			    inserirUF(&arvore, temp);
		
						
			fclose(arq); // fecha arquivo A04ODS392.txt
			break;
				
		case 2: 
			break;
		
		case 3:
			break;
		
		case 4: 
			break;
			
		case 5: 
			break;

		case 6:
			break;
						
		case 0: 
			exit (1);
			
		default:
			printf("Opcao invalida\n"); 
		
		} // fim do switch 
		
	} // fim do while 
	
    return 0;

} // fim do main 