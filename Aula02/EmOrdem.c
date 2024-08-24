#include <stdio.h>

typedef struct _no {
    int dado;
    struct _no *pai;
    struct _no *esq;
    struct _no *dir;
}NO;

void emOrdem(NO *tree){
    if(tree != NULL){
        emOrdem(tree->esq);
        printf("%d", tree->dado);
        emOrdem(tree->dir);
    }
}