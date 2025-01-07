#ifndef ARVORE_RB_H
#define ARVORE_RB_H

#include <iostream>

// Enumeração para as cores do nó
enum Cor { VERMELHO, PRETO };

// Estrutura do nó da árvore Rubro-Negra
struct NoRB {
    int chave;
    Cor cor;
    NoRB* esquerda;
    NoRB* direita;
    NoRB* pai;
};

// Define a árvore como um ponteiro para o nó raiz
typedef NoRB* ArvoreRB;

// Declarações das funções
NoRB* criarNo(int valor);
ArvoreRB rotacaoEsquerda(ArvoreRB raiz, NoRB* noAtual);
ArvoreRB rotacaoDireita(ArvoreRB raiz, NoRB* noAtual);
ArvoreRB corrigirInsercao(ArvoreRB raiz, NoRB* novoNo);
ArvoreRB inserir(ArvoreRB raiz, int valor);
ArvoreRB remover(ArvoreRB raiz, int valor);
ArvoreRB corrigirRemocao(ArvoreRB raiz, NoRB* no);
void mostrarArvore(NoRB* raiz);
NoRB* pesquisar(NoRB* raiz, int valor);

#endif // ARVORE_RB_H
