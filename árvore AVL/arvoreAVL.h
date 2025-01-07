#ifndef ARVOREAVL_H
#define ARVOREAVL_H

typedef struct Node TreeNode;

struct Node {
    int chave;
    TreeNode *esquerda;
    TreeNode *direita;
    int altura; 
};

typedef TreeNode* AVLTree;

// Cabeçalhos das funções
int maiorValor(int a, int b);
int alturaArvore(TreeNode* no);
TreeNode* criaNo(int chave);
int fatorBalanceamento(TreeNode* no);
TreeNode* rotacaoDireita(TreeNode* noDesbalanceado);
TreeNode* rotacaoEsquerda(TreeNode* noDesbalanceado);
TreeNode* insere(TreeNode* no, int chave);
TreeNode* pesquisa(TreeNode* no, int chave);
TreeNode* remover(TreeNode* raiz, int chave);
void mostrararvore(TreeNode* raiz);

#endif // ARVOREAVL_H
