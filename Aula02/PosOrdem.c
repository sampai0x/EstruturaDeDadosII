#include <stdio.h>

typedef struct _no {
    int dado;
    struct _no *pai;
    struct _no *esq;
    struct _no *dir;
}NO;

void PosOrdem(NO *tree){
    if(tree != NULL){
        PosOrdem(tree->esq);
        PosOrdem(tree->dir);
        printf("%d", tree->dado);
    }
}