#include <stdio.h> 
#include <stdlib.h>

// Codificar a estrutura dos nós da BST
typedef struct _no{
	int id;
	struct _no *esq;
	struct _no *dir;
	struct _no *pai;
} No;

// Rotina para inicializar a BST
void inicializar(No **raiz){ //raiz da arvore ou de uma subárvore
	*raiz = NULL;
}

// Rotina que testa se a BST está vazia
int estaVazia(No *raiz){
	if(raiz == NULL){
		return 1;
	}
	
	return 0;
}

// Rotinas de caminhamento na BST
// Pré-ordem
void preOrdem(No *raiz){
	if(!estaVazia(raiz)){
		printf("%d ", raiz->id);
		preOrdem(raiz->esq);
		preOrdem(raiz->dir);
	}
}

// Pós-ordem
void posOrdem(No *raiz){
	if(!estaVazia(raiz)){
		posOrdem(raiz->esq);
		posOrdem(raiz->dir);
		printf("%d ", raiz->id);
	}
}

// Em-ordem
void emOrdem(No *raiz){
	if(!estaVazia(raiz)){
		emOrdem(raiz->esq);
		printf("%d ", raiz->id);
		emOrdem(raiz->dir);
	}
}

// Rotina de busca (pesquisa) na BST
No* pesquisar(No *raiz, int chavePesquisa){
	No *atual = raiz;

    while (atual != NULL) {
        if (chavePesquisa == atual->id) {
            return atual; // Valor encontrado
        } else if (chavePesquisa < atual->id) {
            atual = atual->esq; // Procurar na subárvore esquerda
        } else {
            atual = atual->dir; // Procurar na subárvore direita
        }
    }

    return NULL; // Valor não encontrado
	
}

// Rotina de inserção na BST
void inserir(No **raiz, int chave){
	No *novo;
	No *aux;
	No *papai;
	
	/* alocar memória para o novo noh */
	novo = (No *) malloc(sizeof(No));
	novo->id = chave;
	novo->esq = NULL;
	novo->dir = NULL;
	novo->pai = NULL;
	
	/* testar se a árvore está vazia ou não */
	if(estaVazia(*raiz)){
		*raiz = novo;
		return;
	}
	
	/* se a árvore conter nós caminhar na árvore até achar a posição correta do nó a ser incluído */
	aux = *raiz;
	while(aux != NULL){ // vai até encontrar uma subárvore vazia
		papai = aux;
		
		if(chave < aux->id){
			aux = aux->esq;
		}else if(chave > aux->id){
			aux = aux->dir;
		}else{ // trata se a chave for igual ao id do nó
			printf("Nao eh possivel inserir noh de chave duplicada\n");
			return;
		}
		
	} //encerra a rotina de caminhar na árvore
	
	if(chave < papai->id){
		papai->esq = novo;
	}else{
		papai->dir = novo;
	}
	
	novo->pai = papai;
	
}

// Rotina de apoio para remoção em BST
// trabalhar com a subárvore esquerda ou com a subárvore direita
No* achaMaior(No *raiz){
	No *atual = raiz;
	
	if(!estaVazia(raiz)){
		while(atual->dir != NULL){
			atual = atual->dir;
		}
	}
	
	return atual;
}

// Rotina de remoção
// 3 casos (folha, 1 filho, 2 filhos)
int remover(No **raiz, int chave){
	No *atual;
	No *maior;
	int valor;
	
	if(estaVazia(*raiz) == 1){
		return 1;
	}
	
	atual = pesquisar(*raiz, chave); //busca o endereço do nó a ser removido
	/*se o nó não for encontrado*/
	if(atual == NULL){
		printf("Noh %d nao encontrado\n", chave);
		return 0;
	}
	
	/* CASO 1: remover um noh folha */
	if(atual->esq == NULL && atual->dir == NULL){
		/* se o nó a ser removido é a raiz */
		if(atual->pai == NULL){
			inicializar(raiz);
			free(atual);
			return 1;
		}
		
		/* nó a ser removido não é a raiz */
		if(chave < atual->pai->id){
			atual->pai->esq = NULL;
		}else{
			atual->pai->dir = NULL;
		}
		
		free(atual);
		return 1;
	}//encerra o caso 1 de remoção
	
	/* CASO 2: remover um nó com um filho */
	if((atual->esq != NULL && atual->dir == NULL) || (atual->dir != NULL && atual->esq == NULL)){
		
		/* caso o nó atual for a raiz da árvore */
		if(atual->pai == NULL){
			/* se o filho está na subárvore esquerda da raiz */
			if(atual->esq != NULL){
				*raiz = atual->esq;
			}else{ /* o flho está na subárvore direita da raiz */
				*raiz = atual->dir;
			}
		}
		
		/* caso o nó atual não for a raiz */
		else{
			/* caso o nó atual for o filho da esquerda do pai */
			if(atual == atual->pai->esq){
				
				/* caso o filho do atual estiver na subárvore esquerda */
				if(atual->esq != NULL){
					atual->pai->esq = atual->esq;
					atual->esq->pai = atual->pai;
				}else{ //caso o filho do atual estiver na subárvore direita
					atual->pai->esq = atual->dir;
					atual->dir->pai = atual->pai;
				}
			}//encerra o if do atual filho a esquerda
			
			/* caso o nó atual for filho a direita do pai */
			else if(atual == atual->pai->dir){
				/* caso o filho do atual estiver na subárvore esquerda */
				if(atual->esq != NULL){
					atual->pai->dir = atual->esq;
					atual->esq->pai = atual->pai;
				}else{ //caso o filho do atual estiver na subárvore direita
					atual->pai->dir = atual->dir;
					atual->dir->pai = atual->pai;
				}
			}//fim do if(atual == atual->pai->dir)
			
		}// fim do else atual != raiz
		
		free(atual);
			return 1;
			
		
	}// fim do caso 2
	
	/* CASO 3: remover um nó com dois filhos */
	if(atual->esq != NULL && atual->dir != NULL){
		/* achar o maior elemento da subárvore esquerda */
		maior = achaMaior(atual->esq);
		
		/* trocar os dados do maior elemento encontrado com os dados do nó a ser removido */
		valor = maior->id;
		
		remover(raiz, maior->id);
		
		/* substituir dados do maior elemento para o elemento atual */
		atual->id = valor;
	}// fim do caso 3
	
}// fim da rotina de remoção



/* ********************************************* */
/* ******* MAIN PARA TESTES DAS ROTINAS  ******* */
/* ********************************************* */

/* ------------------------------------------------ */
int main() {

    No *arvore;    // declaração do ponteiro que aponta para a raiz da árvore
    No *aux;
	int ret;
	
    inicializar(&arvore);   // atribuir nulo para a raiz

    /* -------------------------------------------- */
    /* TESTE DE INSERCAO                            */
    /* -------------------------------------------- */
    inserir(&arvore, 50);
    inserir(&arvore, 40);
    inserir(&arvore, 30);
    inserir(&arvore, 60);
    inserir(&arvore, 45);
    inserir(&arvore, 30);
    inserir(&arvore, 14);
    inserir(&arvore, 65);
    inserir(&arvore, 78);
    inserir(&arvore, 55);
    inserir(&arvore, 52);


    /* -------------------------------------------- */
    /* TESTE DE IMPRESSAO                   */
    /* -------------------------------------------- */
    printf("\nPRE: ");
    preOrdem(arvore);
    printf("\n");

    printf("POS: ");
    posOrdem(arvore);
    printf("\n");
    
    printf("EM : ");
    emOrdem(arvore);
    printf("\n");


    /* -------------------------------------------- */
    /* TESTE DE PESQUISA                            */
    /* -------------------------------------------- */
    printf("\nBusca pelo Noh 52");
    if ((aux = pesquisar(arvore, 52)) != NULL)
        printf(" -> %d encontrado!\n", aux->id);
    else
        printf(" -> Noh NAO encontrado!\n");

    printf("Busca pelo Noh 53");
    if ((aux = pesquisar(arvore, 53)) != NULL)
        printf(" -> %d encontrado!\n", aux->id);
    else
        printf(" -> Noh NAO encontrado!\n");


    /* -------------------------------------------- */
    /* TESTE DE REMOCAO                             */
    /* -------------------------------------------- */
    
    /* remove Noh folha */
    printf("\nStatus: ");
    emOrdem(arvore);
    printf("\nRemover noh folha (45)\n");
    ret = remover(&arvore, 45);
    printf("Result: ");
    emOrdem(arvore);
    printf("\n");

    /* remove Noh com um filho na subesquerda */
    printf("\nStatus: ");
    emOrdem(arvore);
    printf("\nRemover noh com um filho na subesquerda (40)\n");
    ret = remover(&arvore, 40);
    printf("Result: ");
    emOrdem(arvore);
    printf("\n");

    /* remove Noh com um filho na subdireita */
    printf("\nStatus: ");
    emOrdem(arvore);
    printf("\nRemover noh com um filho na subdireita (65)\n");
    ret = remover(&arvore, 65);
    printf("Result: ");
    emOrdem(arvore);
    printf("\n");

    /* remove Noh com dois filhos */
    printf("\nStatus: ");
    emOrdem(arvore);
    printf("\nRemover noh com dois filhos (50)\n");
    ret = remover(&arvore, 50);
    printf("Result: ");
    emOrdem(arvore);
    printf("\n");

    /* remove Noh nao existente */
    printf("\nStatus: ");
    emOrdem(arvore);
    printf("\nRemover noh que nao existe (47)\n");
    ret = remover(&arvore, 47);
    printf("Result: ");
    emOrdem(arvore);
    printf("\n");

    return 0;

} /* fim do main */
