#include "arvoreRB.h"
#include <iostream>
#include <stack>
using namespace std;

// Função para criar um novo nó na árvore Rubro-Negra
NoRB* criarNo(int valor) {
    NoRB* novoNo = new NoRB(); // Aloca memória para um novo nó
    novoNo->chave = valor; // Atribui o valor passado ao nó
    novoNo->cor = VERMELHO; // Nós são criados com a cor vermelha
    novoNo->esquerda = nullptr; // Inicializa o ponteiro da subárvore esquerda como nulo
    novoNo->direita = nullptr; // Inicializa o ponteiro da subárvore direita como nulo
    novoNo->pai = nullptr; // Inicializa o ponteiro para o pai como nulo
    return novoNo; // Retorna o novo nó criado
}

// Função para realizar uma rotação à esquerda
NoRB* rotacaoEsquerda(NoRB* raiz, NoRB* no) {
    cout << "Realizando rotacao a esquerda no no com chave: " << no->chave << endl;
    NoRB* direita = no->direita; // Pega o filho à direita do nó atual
    no->direita = direita->esquerda; // Move a subárvore esquerda do filho direito para o nó atual

    if (direita->esquerda != nullptr) {
        direita->esquerda->pai = no; // Atualiza o ponteiro pai da nova subárvore esquerda
    }

    direita->pai = no->pai; // Ajusta o ponteiro pai do nó rotacionado

    if (no->pai == nullptr) {
        raiz = direita; // Atualiza a raiz se o nó atual for a raiz
    } else if (no == no->pai->esquerda) {
        no->pai->esquerda = direita; // Atualiza o ponteiro do pai para o lado esquerdo
    } else {
        no->pai->direita = direita; // Atualiza o ponteiro do pai para o lado direito
    }

    direita->esquerda = no; // Move o nó atual para a posição de filho esquerdo
    no->pai = direita; // Atualiza o pai do nó atual
    return raiz; // Retorna a raiz atualizada
}

// Função auxiliar para realizar uma rotação à direita
NoRB* rotacaoDireita(NoRB* raiz, NoRB* no) {
    cout << "Realizando rotacao a direita no no com chave: " << no->chave << endl;
    NoRB* esquerda = no->esquerda; // Pega o filho à esquerda do nó atual
    no->esquerda = esquerda->direita; // Move a subárvore direita do filho esquerdo para o nó atual

    if (esquerda->direita != nullptr) {
        esquerda->direita->pai = no; // Atualiza o ponteiro pai da nova subárvore direita
    }

    esquerda->pai = no->pai; // Ajusta o ponteiro pai do nó rotacionado

    if (no->pai == nullptr) {
        raiz = esquerda; // Atualiza a raiz se o nó atual for a raiz
    } else if (no == no->pai->esquerda) {
        no->pai->esquerda = esquerda; // Atualiza o ponteiro do pai para o lado esquerdo
    } else {
        no->pai->direita = esquerda; // Atualiza o ponteiro do pai para o lado direito
    }

    esquerda->direita = no; // Move o nó atual para a posição de filho direito
    no->pai = esquerda; // Atualiza o pai do nó atual
    return raiz; // Retorna a raiz atualizada
}

// Função auxiliar para corrigir violações das propriedades da árvore 
NoRB* corrigirInsercao(NoRB* raiz, NoRB* no) {
    NoRB* pai = nullptr; // Inicializa o ponteiro para o pai do nó
    NoRB* avo = nullptr; // Inicializa o ponteiro para o avô do nó

    while (no != raiz && no->cor == VERMELHO && no->pai->cor == VERMELHO) {
        pai = no->pai; // Obtém o pai do nó atual
        avo = pai->pai; // Obtém o avô do nó atual

        // Caso 1: O pai está no lado esquerdo do avô
        if (pai == avo->esquerda) {
            NoRB* tio = avo->direita; // Obtém o tio do nó

            // Caso 1.1: O tio também é vermelho
            if (tio != nullptr && tio->cor == VERMELHO) {
                avo->cor = VERMELHO;
                pai->cor = PRETO;
                tio->cor = PRETO;
                no = avo;
            } else {
                // Caso 1.2: O nó está no lado direito 
                if (no == pai->direita) {
                    raiz = rotacaoEsquerda(raiz, pai);
                    no = pai;
                    pai = no->pai;
                }

                // Caso 1.3: Rotação direita necessária
                raiz = rotacaoDireita(raiz, avo);
                swap(pai->cor, avo->cor); // Troca as cores do pai e do avô
                no = pai;
            }
        } else { // Caso 2: O pai está no lado direito do avô
            NoRB* tio = avo->esquerda; // Obtém o tio do nó

            // Caso 2.1: O tio também é vermelho
            if (tio != nullptr && tio->cor == VERMELHO) {
                avo->cor = VERMELHO;
                pai->cor = PRETO;
                tio->cor = PRETO;
                no = avo;
            } else {
                // Caso 2.2: O nó está no lado esquerdo (rotação direita necessária)
                if (no == pai->esquerda) {
                    raiz = rotacaoDireita(raiz, pai);
                    no = pai;
                    pai = no->pai;
                }

                // Caso 2.3: Rotação esquerda necessária
                raiz = rotacaoEsquerda(raiz, avo);
                swap(pai->cor, avo->cor); // Troca as cores do pai e do avô
                no = pai;
            }
        }
    }

    raiz->cor = PRETO; // A raiz sempre será preta
    return raiz; // Retorna a raiz atualizada
}

// Função principal para inserir um nó na árvore
NoRB* inserir(NoRB* raiz, int valor) {
    NoRB* novoNo = criarNo(valor); // Cria um novo nó com o valor fornecido

    if (raiz == nullptr) { // Árvore vazia
        novoNo->cor = PRETO; // A raiz sempre deve ser preta
        return novoNo; // Retorna o novo nó como raiz
    }

    NoRB* atual = raiz; // Inicializa o ponteiro para percorrer a árvore
    NoRB* pai = nullptr;

    // Percorre a árvore para encontrar a posição correta de inserção
    while (atual != nullptr) {
        pai = atual;

        if (valor < atual->chave) {
            atual = atual->esquerda; // Move para a subárvore esquerda
        } else if (valor > atual->chave) {
            atual = atual->direita; // Move para a subárvore direita
        } else {
            return raiz; // Valor já existe, nenhuma inserção é feita
        }
    }

    // Conecta o novo nó ao seu pai
    novoNo->pai = pai;
    if (valor < pai->chave) {
        pai->esquerda = novoNo;
    } else {
        pai->direita = novoNo;
    }

    // Corrige possíveis violações das propriedades da árvore Rubro-Negra
    return corrigirInsercao(raiz, novoNo);
}

// Função auxiliar para encontrar o nó com o menor valor em uma subárvore
NoRB* minimo(NoRB* no) {
    while (no->esquerda != nullptr) {
        no = no->esquerda;
    }
    return no;
}

// Função auxiliar para remover um nó da árvore
NoRB* remover(NoRB* raiz, int valor) {
    NoRB* no = raiz;
    NoRB* substituto;
    NoRB* filho;

    // Localiza o nó a ser removido
    while (no != nullptr && no->chave != valor) {
        if (valor < no->chave)
            no = no->esquerda;
        else
            no = no->direita;
    }

    if (no == nullptr) {
        cout << "Valor não encontrado na árvore!" << endl;
        return raiz; // Valor não encontrado
    }

    // Caso 1: O nó tem dois filhos
    if (no->esquerda != nullptr && no->direita != nullptr) {
        substituto = minimo(no->direita); // Encontra o nó substituto 
        no->chave = substituto->chave; // Substitui o valor do nó a ser removido
        no = substituto; // Remove o nó substituto
    }

    // Caso 2: O nó tem no máximo um filho
    if (no->esquerda != nullptr) {
        filho = no->esquerda;
    } else {
        filho = no->direita;
    }

    if (filho != nullptr) {
        filho->pai = no->pai; // Atualiza o ponteiro pai do filho
    }

    if (no->pai == nullptr) {
        raiz = filho; // Caso especial, se o nó removido for a raiz
    } else if (no == no->pai->esquerda) {
        no->pai->esquerda = filho;
    } else {
        no->pai->direita = filho;
    }

    if (no->cor == PRETO) {
        // Se o nó removido for preto, corrige a árvore
        raiz = corrigirRemocao(raiz, filho);
    }

    delete no; // Libera a memória do nó removido
    return raiz;
}

// Função para corrigir a árvore após uma remoção
ArvoreRB corrigirRemocao(ArvoreRB raiz, NoRB* no) {
    while (no != raiz && (no == NULL || no->cor == PRETO)) {
        if (no == no->pai->esquerda) { // O nó está no lado esquerdo do pai
            NoRB* irmao = no->pai->direita; // Obtém o irmão do nó

            if (irmao->cor == VERMELHO) { // Caso 1: Irmão é vermelho
                cout << "Corrigindo caso 1 (irmão vermelho)" << endl;
                irmao->cor = PRETO; // Irmão se torna preto
                no->pai->cor = VERMELHO; // Pai se torna vermelho
                raiz = rotacaoEsquerda(raiz, no->pai); // Rotação à esquerda no pai
                irmao = no->pai->direita; // Atualiza o irmão
            }

            if ((irmao->esquerda == NULL || irmao->esquerda->cor == PRETO) &&
                (irmao->direita == NULL || irmao->direita->cor == PRETO)) { // Caso 2: Ambos os filhos do irmão são pretos
                cout << "Corrigindo caso 2 (filhos pretos)" << endl;
                irmao->cor = VERMELHO; // Irmão se torna vermelho
                no = no->pai; // Sobe para o pai
            } else {
                if (irmao->direita == NULL || irmao->direita->cor == PRETO) { // Caso 3: Filho direito do irmão é preto
                    cout << "Corrigindo caso 3 (filho direito preto)" << endl;
                    if (irmao->esquerda != NULL) {
                        irmao->esquerda->cor = PRETO; // Filho esquerdo se torna preto
                    }
                    irmao->cor = VERMELHO; // Irmão se torna vermelho
                    raiz = rotacaoDireita(raiz, irmao); // Rotação à direita no irmão
                    irmao = no->pai->direita; // Atualiza o irmão
                }

                // Caso 4: Filho direito do irmão é vermelho
                cout << "Corrigindo caso 4 (filho direito vermelho)" << endl;
                irmao->cor = no->pai->cor; // Irmão assume a cor do pai
                no->pai->cor = PRETO; // Pai se torna preto
                if (irmao->direita != NULL) {
                    irmao->direita->cor = PRETO; // Filho direito do irmão se torna preto
                }
                raiz = rotacaoEsquerda(raiz, no->pai); // Rotação à esquerda no pai
                no = raiz; // O nó se torna a raiz
            }
        } else { // Lógica similar para o lado direito
            NoRB* irmao = no->pai->esquerda;

            if (irmao->cor == VERMELHO) {
                irmao->cor = PRETO;
                no->pai->cor = VERMELHO;
                raiz = rotacaoDireita(raiz, no->pai);
                irmao = no->pai->esquerda;
            }

            if ((irmao->direita == NULL || irmao->direita->cor == PRETO) &&
                (irmao->esquerda == NULL || irmao->esquerda->cor == PRETO)) {
                irmao->cor = VERMELHO;
                no = no->pai;
            } else {
                if (irmao->esquerda == NULL || irmao->esquerda->cor == PRETO) {
                    if (irmao->direita != NULL) {
                        irmao->direita->cor = PRETO;
                    }
                    irmao->cor = VERMELHO;
                    raiz = rotacaoEsquerda(raiz, irmao);
                    irmao = no->pai->esquerda;
                }

                irmao->cor = no->pai->cor;
                no->pai->cor = PRETO;
                if (irmao->esquerda != NULL) {
                    irmao->esquerda->cor = PRETO;
                }
                raiz = rotacaoDireita(raiz, no->pai);
                no = raiz;
            }
        }
    }

    if (no != NULL) {
        no->cor = PRETO; // O nó se torna preto ao final da correção
    }

    return raiz;
}

    // Função para pesquisar um valor na árvore
NoRB* pesquisar(NoRB* raiz, int valor) {
    NoRB* atual = raiz;  // Começa a busca a partir da raiz

    // Enquanto o nó atual não for nulo, percorre a árvore
    while (atual != nullptr) {
        if (valor < atual->chave) {
            atual = atual->esquerda; // Se o valor for menor, vai para a subárvore esquerda
        } else if (valor > atual->chave) {
            atual = atual->direita; // Se o valor for maior, vai para a subárvore direita
        } else {
            return atual; // Se encontrou o valor, retorna o nó
        }
    }

    // Se o valor não foi encontrado, retorna nulo
    return nullptr;
}

void mostrarArvore(NoRB* raiz) {
    // Pilha para armazenar os nós à medida que percorremos a árvore
    stack<NoRB*> pilhaGlobal;
    pilhaGlobal.push(raiz);
    int nVazios = 32;  // Controla a quantidade de espaços em cada nível da árvore
    bool linhaVazia = false;
    cout << endl;

    // Enquanto a árvore não estiver completamente exibida (quando todos os nós forem visitados)
    while (!linhaVazia) {
        stack<NoRB*> pilhaLocal;
        linhaVazia = true;

        // Espacos para formatar a árvore
        for (int j = 0; j < nVazios; j++) {
            cout << ' ';
        }

        // Processa os nós de cada nível da árvore
        while (!pilhaGlobal.empty()) {
            NoRB* temp = pilhaGlobal.top();
            pilhaGlobal.pop();

            if (temp != nullptr) {
                // Exibe o valor e a cor do nó
                cout << temp->chave << "(" << (temp->cor == VERMELHO ? "Vermelho" : "Preto") << ")";
                // Adiciona os filhos à pilha local
                pilhaLocal.push(temp->esquerda);
                pilhaLocal.push(temp->direita);

                // Verifica se há filhos para continuar percorrendo
                if (temp->esquerda != nullptr || temp->direita != nullptr) {
                    linhaVazia = false;
                }
            } else {
                // No nulo (não existe nó)
                cout << "--";
                pilhaLocal.push(nullptr);
                pilhaLocal.push(nullptr);
            }

            // Controla os espaços entre os nós
            for (int j = 0; j < nVazios * 2 - 2; j++) {
                cout << ' ';
            }
        }
        cout << endl;
        nVazios = nVazios / 2;

        // Transferir os nós da pilha local para a pilha global
        while (!pilhaLocal.empty()) {
            pilhaGlobal.push(pilhaLocal.top());
            pilhaLocal.pop();
        }
    }
    cout << endl;
}