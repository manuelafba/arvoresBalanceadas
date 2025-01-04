#include "arvoreAVL.h"
#include <cstdlib>
#include <iostream>

// Função auxiliar para retornar o maior valor entre dois inteiros
int maiorValor(int a, int b) {
    if (a > b){
        return a; // Retorna 'a' se 'a' for maior que 'b'
    } else {
        return b; // Caso contrário, retorna 'b'
    }
}

int alturaArvore(TreeNode* no) {
    if (no == NULL) {
        return 0;  // Se o nó for nulo, a altura é zero
    } else {
        return no->altura;  // Caso contrário, retorna a altura armazenada no nó
    }
}

TreeNode* criaNo(int chave) {
    TreeNode* novoNo = (TreeNode*)malloc(sizeof(TreeNode));  // Aloca memória dinamicamente para um novo nó
    if (novoNo != NULL) {
        novoNo->chave = chave; // Define a chave do novo nó
        novoNo->esquerda = NULL; // Inicializa o ponteiro esquerdo como NULL
        novoNo->direita = NULL; // Inicializa o ponteiro direito como NULL
        novoNo->altura = 1; // A altura inicial de um nó recém-criado é 1
    }
    return novoNo; // Retorna o ponteiro para o novo nó
}

int fatorBalanceamento(TreeNode* no) {
    if (no == NULL) {
        return 0; // Se o nó for nulo, o fator de balanceamento é zero
    } else {
        return alturaArvore(no->esquerda) - alturaArvore(no->direita); // Calcula a diferença entre as alturas das subárvores
    }
}

TreeNode* rotacaoDireita(TreeNode* noDesbalanceado) {
    cout << "Realizando rotacao a direita no no com chave: " << noDesbalanceado->chave << endl;
    TreeNode* subarvoreEsquerda = noDesbalanceado->esquerda; // Obtém a subárvore esquerda do nó desbalanceado
    TreeNode* subarvoreDireita = subarvoreEsquerda->direita; // Obtém a subárvore direita do filho esquerdo

    subarvoreEsquerda->direita = noDesbalanceado; // O nó desbalanceado se torna o filho direito da subárvore esquerda
    noDesbalanceado->esquerda = subarvoreDireita; // Ajusta a subárvore direita

    // Atualiza as alturas dos nós
    noDesbalanceado->altura = maiorValor(alturaArvore(noDesbalanceado->esquerda), alturaArvore(noDesbalanceado->direita)) + 1;
    subarvoreEsquerda->altura = maiorValor(alturaArvore(subarvoreEsquerda->esquerda), alturaArvore(subarvoreEsquerda->direita)) + 1;

    return subarvoreEsquerda; // Retorna a nova raiz da subárvore
}

TreeNode* rotacaoEsquerda(TreeNode* noDesbalanceado) {
    cout << "Realizando rotacao a esquerda no no com chave: " << noDesbalanceado->chave << endl;
    TreeNode* subarvoreDireita = noDesbalanceado->direita; // Obtém a subárvore direita do nó desbalanceado
    TreeNode* subarvoreEsquerda = subarvoreDireita->esquerda; // Obtém a subárvore esquerda do filho direito

    subarvoreDireita->esquerda = noDesbalanceado; // O nó desbalanceado se torna o filho esquerdo da subárvore direita
    noDesbalanceado->direita = subarvoreEsquerda; // Ajusta a subárvore esquerda

    // Atualiza as alturas dos nós 
    noDesbalanceado->altura = maiorValor(alturaArvore(noDesbalanceado->esquerda), alturaArvore(noDesbalanceado->direita)) + 1;
    subarvoreDireita->altura = maiorValor(alturaArvore(subarvoreDireita->esquerda), alturaArvore(subarvoreDireita->direita)) + 1;

    return subarvoreDireita; // Retorna a nova raiz da subárvore
}

TreeNode* insere(TreeNode* no, int chave) {
    if (no == NULL) {
        return criaNo(chave); // Se o nó for nulo, cria um novo nó com a chave
    }

    if (chave < no->chave) {
        no->esquerda = insere(no->esquerda, chave); // Insere a chave na subárvore esquerda
    } else if (chave > no->chave) {
        no->direita = insere(no->direita, chave); // Insere a chave na subárvore direita
    } else {
        return no; // Chaves duplicadas não são permitidas, então retorna o nó inalterado
    }

    // Atualiza a altura do nó atual
    no->altura = maiorValor(alturaArvore(no->esquerda), alturaArvore(no->direita)) + 1;

    // Calcula o fator de balanceamento para verificar se o nó está desbalanceado
    int balance = fatorBalanceamento(no);

    // Rotação à direita simples
    if (balance > 1 && chave < no->esquerda->chave) {
        return rotacaoDireita(no);
    }

    // Rotação à esquerda simples
    if (balance < -1 && chave > no->direita->chave) {
        return rotacaoEsquerda(no);
    }

    // Rotação dupla à esquerda e depois à direita
    if (balance > 1 && chave > no->esquerda->chave) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }

    // Rotação dupla à direita e depois à esquerda
    if (balance < -1 && chave < no->direita->chave) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }

    return no; // Retorna o nó atualizado
}

TreeNode* pesquisa(TreeNode* no, int chave) {
    // Se a árvore está vazia ou o nó atual for o que estamos buscando
    if (no == NULL || no->chave == chave) {
        return no;
    }

    // Se a chave for menor, procura na subárvore esquerda
    if (chave < no->chave) {
        return pesquisa(no->esquerda, chave);
    }
    
    // Se a chave for maior, procura na subárvore direita
    return pesquisa(no->direita, chave);
}

void exibirArvore(TreeNode* no) {
    if (no != NULL) {
        exibirArvore(no->esquerda); // Exibe a subárvore esquerda
        cout << no->chave << " "; // Exibe a chave do nó atual
        exibirArvore(no->direita); // Exibe a subárvore direita
    }
}

void liberaArvore(TreeNode* no) {
    if (no != NULL) {
        liberaArvore(no->esquerda); // Libera a subárvore esquerda
        liberaArvore(no->direita); // Libera a subárvore direita
        free(no); // Libera a memória do nó atual
    }
}
