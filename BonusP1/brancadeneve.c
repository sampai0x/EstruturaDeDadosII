#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAMANHO_MAXIMO_PALAVRA 300


typedef struct NoAVL {
    char palavra[TAMANHO_MAXIMO_PALAVRA];
    int altura;
    struct NoAVL* esquerda;
    struct NoAVL* direita;
} NoAVL;

NoAVL* criarNo(char* palavra) {
    NoAVL* no = (NoAVL*)malloc(sizeof(NoAVL));
    if (no == NULL) {
        printf("Erro de alocação de memória.\n");
        exit(1);
    }
    strcpy(no->palavra, palavra);
    no->altura = 1;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

int obterAltura(NoAVL* no) {
    if (no) {
        return no->altura;
    } else {
        return 0;
    }
}

int maximo(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}


NoAVL* rotacaoDireita(NoAVL* y) {
    NoAVL* x = y->esquerda;
    NoAVL* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = maximo(obterAltura(y->esquerda), obterAltura(y->direita)) + 1;
    x->altura = maximo(obterAltura(x->esquerda), obterAltura(x->direita)) + 1;

    return x;
}

NoAVL* rotacaoEsquerda(NoAVL* x) {
    NoAVL* y = x->direita;
    NoAVL* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = maximo(obterAltura(x->esquerda), obterAltura(x->direita)) + 1;
    y->altura = maximo(obterAltura(y->esquerda), obterAltura(y->direita)) + 1;

    return y;
}

NoAVL* inserir(NoAVL* no, char* palavra) {
    if (!no) {
        return criarNo(palavra);
    }

    int comparacao = strcmp(palavra, no->palavra);
    if (comparacao < 0) {
        no->esquerda = inserir(no->esquerda, palavra);
    } else if (comparacao > 0) {
        no->direita = inserir(no->direita, palavra);
    } else {
        return no; 
    }

    no->altura = 1 + maximo(obterAltura(no->esquerda), obterAltura(no->direita));

    int balanceamento = obterAltura(no->esquerda) - obterAltura(no->direita);

    if (balanceamento > 1 && strcmp(palavra, no->esquerda->palavra) < 0) {
        return rotacaoDireita(no);
    }
    if (balanceamento < -1 && strcmp(palavra, no->direita->palavra) > 0) {
        return rotacaoEsquerda(no);
    }
    if (balanceamento > 1 && strcmp(palavra, no->esquerda->palavra) > 0) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }
    if (balanceamento < -1 && strcmp(palavra, no->direita->palavra) < 0) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }

    return no;
}

void emOrdem(NoAVL* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);
        printf("%s\n", raiz->palavra);
        emOrdem(raiz->direita);
    }
}

void paraMinusculo(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = (char)tolower((unsigned char)str[i]);
    }
}

int ehLetra(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int main() {
    NoAVL* raiz = NULL;
    char linha[300];

    printf("Digite o texto (deixe a linha vazia para finalizar):\n");

    while (1) {
        fgets(linha, sizeof(linha), stdin);

        linha[strcspn(linha, "\n")] = 0;

        if (strlen(linha) == 0) {
            break;
        }

        int tamanho = strlen(linha);
        char palavra[TAMANHO_MAXIMO_PALAVRA];
        int indicePalavra = 0;

        for (int i = 0; i <= tamanho; i++) {
            if (ehLetra(linha[i])) {
                palavra[indicePalavra++] = linha[i];
            } else {
                if (indicePalavra > 0) {
                    palavra[indicePalavra] = '\0';
                    paraMinusculo(palavra);  
                    raiz = inserir(raiz, palavra);  
                    indicePalavra = 0;
                }
            }
        }
    }

    printf("\nPalavras em ordem alfabética:\n");
    emOrdem(raiz);

    return 0;
}