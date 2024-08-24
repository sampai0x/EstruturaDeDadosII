No* pesquisar(No *raiz, int chavePesquisa) {
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