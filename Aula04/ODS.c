#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1

typedef struct _No {
    char uf[3];
    float ano2015;
	float ano2016;
	float ano2017;
	float ano2018; 
	float ano2019;
    struct _No *esq;
	struct _No *dir;
	struct _No *pai;
} No;

// Função para inserir um novo nó na árvore
void inserirUF(No **raiz, No novo) {
    if (*raiz == NULL) {
        *raiz = (No*)malloc(sizeof(No));
        if (*raiz == NULL) {
            printf("Erro ao alocar memória.\n");
            exit(1);
        }
        **raiz = novo;
        (*raiz)->esq = NULL;
        (*raiz)->dir = NULL;
    } else if (strcmp(novo.uf, (*raiz)->uf) < 0) {
        inserirUF(&(*raiz)->esq, novo);
    } else if (strcmp(novo.uf, (*raiz)->uf) > 0) {
        inserirUF(&(*raiz)->dir, novo);
    }
}

// Função para exibir todos os nós da árvore (em ordem)
void exibirUFs(No *raiz) {
    if (raiz != NULL) {
        exibirUFs(raiz->esq);
        printf("%s: %.2f %.2f %.2f %.2f %.2f\n", raiz->uf, raiz->ano2015, raiz->ano2016, raiz->ano2017, raiz->ano2018, raiz->ano2019);
        exibirUFs(raiz->dir);
    }
}

// Função para buscar um nó com a UF especificada
No* pesquisarUF(No *raiz, char uf[]) {
    if (raiz == NULL) {
        return NULL;
    } else if (strcmp(uf, raiz->uf) == 0) {
        return raiz;
    } else if (strcmp(uf, raiz->uf) < 0) {
        return pesquisarUF(raiz->esq, uf);
    } else {
        return pesquisarUF(raiz->dir, uf);
    }
}

// Função auxiliar para encontrar o nó com o menor valor
No* encontrarMenor(No *raiz) {
    while (raiz && raiz->esq != NULL) {
        raiz = raiz->esq;
    }
    return raiz;
}

// Função para excluir um nó da árvore
void excluirUF(No **raiz, char uf[]) {
    if (*raiz == NULL) {
        return;
    }
    if (strcmp(uf, (*raiz)->uf) < 0) {
        excluirUF(&(*raiz)->esq, uf);
    } else if (strcmp(uf, (*raiz)->uf) > 0) {
        excluirUF(&(*raiz)->dir, uf);
    } else {
        No *temp = *raiz;
        if ((*raiz)->esq == NULL) {
            *raiz = (*raiz)->dir;
        } else if ((*raiz)->dir == NULL) {
            *raiz = (*raiz)->esq;
        } else {
            No *menor = encontrarMenor((*raiz)->dir);
            strcpy((*raiz)->uf, menor->uf);
            (*raiz)->ano2015 = menor->ano2015;
            (*raiz)->ano2016 = menor->ano2016;
            (*raiz)->ano2017 = menor->ano2017;
            (*raiz)->ano2018 = menor->ano2018;
            (*raiz)->ano2019 = menor->ano2019;
            excluirUF(&(*raiz)->dir, menor->uf);
        }
        free(temp);
    }
}

// Função para esvaziar a árvore
void esvaziarArvore(No **raiz) {
    if (*raiz != NULL) {
        esvaziarArvore(&(*raiz)->esq);
        esvaziarArvore(&(*raiz)->dir);
        free(*raiz);
        *raiz = NULL;
    }
}

// Função para calcular a média de um ano específico
float calcularMediaAno(No *raiz, int ano) {
    float soma = 0;
    int count = 0;

    void somaAno(No *no, int ano) {
        if (no == NULL) return;
        switch (ano) {
            case 2015: soma += no->ano2015; break;
            case 2016: soma += no->ano2016; break;
            case 2017: soma += no->ano2017; break;
            case 2018: soma += no->ano2018; break;
            case 2019: soma += no->ano2019; break;
            default: return;
        }
        count++;
        somaAno(no->esq, ano);
        somaAno(no->dir, ano);
    }

    somaAno(raiz, ano);

    if (count == 0) return 0;
    return soma / count;
}

// Função para carregar os dados do arquivo
void carregarDados(No **raiz) {
    FILE *file = fopen("A04ODS392.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    No novo;
    while (fscanf(file, "%2s %f %f %f %f %f",
                  novo.uf,
                  &novo.ano2015,
                  &novo.ano2016,
                  &novo.ano2017,
                  &novo.ano2018,
                  &novo.ano2019) == 6) {
        inserirUF(raiz, novo);
    }

    fclose(file);
}

int main() {
    No *arvore = NULL;
    char uf[3];
    int op, ano;

    while (TRUE) {
        printf("Menu:\n");
        printf("1. Carregar dados das UFs\n");
        printf("2. Exibir dados de todas as UFs\n");
        printf("3. Pesquisar e exibir dados de uma determinada UF\n");
        printf("4. Excluir uma UF\n");
        printf("5. Esvaziar a BST\n");
        printf("6. Calcular a média de taxas por ano\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                carregarDados(&arvore);
                break;
            case 2:
                exibirUFs(arvore);
                break;
            case 3:
                printf("Digite a UF: ");
                scanf("%s", uf);
                No *encontrado = pesquisarUF(arvore, uf);
                if (encontrado != NULL) {
                    printf("UF: %s, 2015: %.2f, 2016: %.2f, 2017: %.2f, 2018: %.2f, 2019: %.2f\n",
                           encontrado->uf, encontrado->ano2015, encontrado->ano2016,
                           encontrado->ano2017, encontrado->ano2018, encontrado->ano2019);
                } else {
                    printf("UF não encontrada.\n");
                }
                break;
            case 4:
                printf("Digite a UF para excluir: ");
                scanf("%s", uf);
                excluirUF(&arvore, uf);
                break;
            case 5:
                esvaziarArvore(&arvore);
                break;
            case 6:
                printf("Digite o ano: ");
                scanf("%d", &ano);
                float media = calcularMediaAno(arvore, ano);
                printf("Média no ano %d: %.2f\n", ano, media);
                break;
            case 0:
                esvaziarArvore(&arvore);
                exit(0);
            default:
                printf("Opção inválida.\n");
        }
    }

    return 0;
}
