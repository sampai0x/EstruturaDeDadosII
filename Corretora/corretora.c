#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// DefiniÃ§Ã£o da estrutura do nÃ³ da Ã¡rvore
typedef struct Papel {
    int id;
    char tipo_mercado[20];
    char produto[5];
    char emissor[20];
    float taxa_cdi;
    int dias_vencimento;
    float valor_papel;
    int quantidade_disponivel;
    struct Papel* esquerda;
    struct Papel* direita;
} Papel;

// FunÃ§Ã£o para criar um novo nÃ³ na Ã¡rvore
Papel* novoPapel(int id, char* tipo_mercado, char* produto, char* emissor, float taxa_cdi, int dias_vencimento, float valor_papel, int quantidade_disponivel) {
    Papel* novo = (Papel*) malloc(sizeof(Papel));
    novo->id = id;
    strcpy(novo->tipo_mercado, tipo_mercado);
    strcpy(novo->produto, produto);
    strcpy(novo->emissor, emissor);
    novo->taxa_cdi = taxa_cdi;
    novo->dias_vencimento = dias_vencimento;
    novo->valor_papel = valor_papel;
    novo->quantidade_disponivel = quantidade_disponivel;
    novo->esquerda = novo->direita = NULL;
    
    printf("Novo papel criado: ID = %d, Taxa CDI = %.2f\n", id, taxa_cdi); // VerificaÃ§Ã£o adicional
    return novo;
}

// FunÃ§Ã£o para inserir um novo papel na BST de acordo com a taxa CDI
Papel* inserirPorRentabilidade(Papel* raiz, Papel* novo) {
    if (raiz == NULL) {
        printf("Inserindo papel com ID %d como raiz\n", novo->id); // VerificaÃ§Ã£o adicional
        return novo;
    }
    
    if (novo->taxa_cdi > raiz->taxa_cdi) {
        printf("Inserindo papel com ID %d a direita de ID %d\n", novo->id, raiz->id); // VerificaÃ§Ã£o adicional
        raiz->direita = inserirPorRentabilidade(raiz->direita, novo);
    } else {
        printf("Inserindo papel com ID %d a esquerda de ID %d\n", novo->id, raiz->id); // VerificaÃ§Ã£o adicional
        raiz->esquerda = inserirPorRentabilidade(raiz->esquerda, novo);
    }
    return raiz;
}

// FunÃ§Ã£o para exibir os papÃ©is em ordem decrescente de rentabilidade
void exibirPapeisPorRentabilidade(Papel* raiz) {
    if (raiz != NULL) {
        exibirPapeisPorRentabilidade(raiz->direita);
        printf("ID: %d, Produto: %s, Taxa CDI: %.2f, Dias Vencimento: %d, Valor: %.2f, Quantidade: %d\n",
               raiz->id, raiz->produto, raiz->taxa_cdi, raiz->dias_vencimento, raiz->valor_papel, raiz->quantidade_disponivel);
        exibirPapeisPorRentabilidade(raiz->esquerda);
    }
}

// Função para comprar papéis de acordo com a rentabilidade
void comprarPapeis(Papel* raiz, float valor_investimento) {
    if (valor_investimento <= 0) {
        printf("Valor de investimento deve ser maior que zero.\n");
        return;
    }

    printf("Compra de papéis com valor total de: %.2f\n", valor_investimento);

    // Função auxiliar para comprar papéis
    void comprarPapeisRecursivo(Papel* node, float* valor_restante) {
        if (node == NULL || *valor_restante <= 0) {
            return;
        }

        // Primeiro, tentar comprar papéis da subárvore direita (maior taxa CDI)
        comprarPapeisRecursivo(node->direita, valor_restante);

        if (*valor_restante <= 0) {
            return;
        }

        // Comprar papéis do nó atual, se houver valor restante e papéis disponíveis
        if (node->quantidade_disponivel > 0 && node->valor_papel <= *valor_restante) {
            int quantidade_comprada = *valor_restante / node->valor_papel;
            if (quantidade_comprada > node->quantidade_disponivel) {
                quantidade_comprada = node->quantidade_disponivel;
            }
            
            float valor_comprado = quantidade_comprada * node->valor_papel;
            *valor_restante -= valor_comprado;
            node->quantidade_disponivel -= quantidade_comprada;
            
            printf("Comprado %d de ID: %d, Valor: %.2f cada, Total: %.2f\n",
                   quantidade_comprada, node->id, node->valor_papel, valor_comprado);
        }

        // Depois, tentar comprar papéis da subárvore esquerda (menor taxa CDI)
        comprarPapeisRecursivo(node->esquerda, valor_restante);
    }

    float valor_restante = valor_investimento;
    comprarPapeisRecursivo(raiz, &valor_restante);

    if (valor_restante > 0) {
        printf("Não foi possível investir todo o valor. Restante: %.2f\n", valor_restante);
    }
}

// Função para inserir um papel na árvore ordenada por vencimento
Papel* inserirPorVencimento(Papel* raiz, Papel* novo) {
    if (raiz == NULL) {
        return novo;
    }
    
    if (novo->dias_vencimento < raiz->dias_vencimento) {
        raiz->esquerda = inserirPorVencimento(raiz->esquerda, novo);
    } else {
        raiz->direita = inserirPorVencimento(raiz->direita, novo);
    }
    return raiz;
}

// Função para exibir os papéis em ordem de vencimento
void exibirPapeisPorVencimento(Papel* raiz) {
    if (raiz != NULL) {
        exibirPapeisPorVencimento(raiz->esquerda);
        if (raiz->quantidade_disponivel > 0) { // Exibir somente papéis disponíveis
            printf("ID: %d, Produto: %s, Taxa CDI: %.2f, Dias Vencimento: %d, Valor: %.2f, Quantidade: %d\n",
               raiz->id, raiz->produto, raiz->taxa_cdi, raiz->dias_vencimento, raiz->valor_papel, raiz->quantidade_disponivel);
        }
        exibirPapeisPorVencimento(raiz->direita);
    }
}

// Função para transferir papéis restantes para a nova árvore ordenada por vencimento
Papel* transferirPapeisRestantes(Papel* raiz_rentabilidade) {
    Papel* raiz_vencimento = NULL;

    // Função auxiliar para transferir papéis
    void transferirPapeisRecursivo(Papel* node) {
        if (node == NULL) {
            return;
        }

        // Transferir papéis da subárvore direita (maior taxa CDI)
        transferirPapeisRecursivo(node->direita);

        // Adicionar papéis restantes na nova árvore
        if (node->quantidade_disponivel > 0) {
            Papel* novo = novoPapel(node->id, node->tipo_mercado, node->produto, node->emissor, node->taxa_cdi, node->dias_vencimento, node->valor_papel, node->quantidade_disponivel);
            raiz_vencimento = inserirPorVencimento(raiz_vencimento, novo);
        }

        // Transferir papéis da subárvore esquerda (menor taxa CDI)
        transferirPapeisRecursivo(node->esquerda);
    }

    transferirPapeisRecursivo(raiz_rentabilidade);
    return raiz_vencimento;
}

// FunÃ§Ã£o para ler os dados do arquivo e popular a Ã¡rvore
Papel* lerArquivoEInserir(char* nome_arquivo, Papel* raiz) {
    FILE* file = fopen(nome_arquivo, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return raiz;
    } else {
        printf("Arquivo lido com sucesso!\n"); // VerificaÃ§Ã£o adicional
    }

    int id, dias_vencimento, quantidade_disponivel;
    float taxa_cdi, valor_papel;
    char tipo_mercado[20], produto[5], emissor[20];

    // Lendo o arquivo e inserindo na Ã¡rvore
    while (fscanf(file, "%d %s %s %s %f %d %f %d\n", &id, &tipo_mercado, &produto, &emissor, &taxa_cdi, &dias_vencimento, &valor_papel, &quantidade_disponivel) != EOF) {
        printf("Lido: %d %s %s %s %.2f %d %.2f %d\n", id, tipo_mercado, produto, emissor, taxa_cdi, dias_vencimento, valor_papel, quantidade_disponivel); // VerificaÃ§Ã£o adicional
        Papel* novo = novoPapel(id, tipo_mercado, produto, emissor, taxa_cdi, dias_vencimento, valor_papel, quantidade_disponivel);
        raiz = inserirPorRentabilidade(raiz, novo);
    }

    fclose(file);
    return raiz;
}

// FunÃ§Ã£o principal
int main() {
    Papel* raiz_rentabilidade = NULL;

    // Ler o arquivo e popular a Ã¡rvore (arquivo na mesma pasta)
    raiz_rentabilidade = lerArquivoEInserir("EDII_A06_Ex01_papeis.txt", raiz_rentabilidade);

    // Exibir os papeis em ordem decrescente de rentabilidade
    printf("Papeis em ordem decrescente de rentabilidade:\n");
    exibirPapeisPorRentabilidade(raiz_rentabilidade);
    
    // Valor de investimento
    float valor_investimento;
    printf("Digite o valor de investimento: ");
    scanf("%f", &valor_investimento);

    // Comprar papéis com base no valor de investimento
    comprarPapeis(raiz_rentabilidade, valor_investimento);
    
    // Transferir papéis restantes para a nova árvore ordenada por vencimento
    Papel* raiz_vencimento = transferirPapeisRestantes(raiz_rentabilidade);

    // Exibir os papéis em ordem de vencimento
    printf("Papeis restantes em ordem de vencimento:\n");
    exibirPapeisPorVencimento(raiz_vencimento);

    return 0;
}
