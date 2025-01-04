// Aluna: Manuela Formigosa Balieiro de Araújo
#include <iostream>
#include "arvoreAVL.h"
using namespace std;

int main() {
    TreeNode* raiz = NULL; // Inicializa a raiz como nula
    int opcao = 0;         // Variável para armazenar a opção do menu

    while (true) { // Laço principal
        // Exibição do menu
        cout << "--- Menu ---" << endl;
        cout << "1. Inserir elemento" << endl;
        cout << "2. Remover elemento"; << endl;
        cout << "3. Pesquisar elemento"; << endl;
        cout << "4. Sair"; << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        if (opcao == 4) { // Caso o usuário escolha a opção 4 para sair, encerra o programa
            cout << "Encerrando o programa...";
            break;
        }

        switch (opcao) {
            case 1: {
                int valor;
                cout << "Digite o valor a ser inserido: ";
                cin >> valor;
                raiz = inserir(raiz, valor); // Insere o elemento na árvore
                cout << "Valor " << valor << " inserido na arvore com sucesso" << endl;
                break;
            }
            case 2: {
                int valor;
                cout << "Digite o valor a ser removido: ";
                cin >> valor;
                raiz = remover(raiz, valor); // Remove o elemento da árvore
                cout << "Valor " << valor << " removido da arvore com sucesso" << endl;
                break;
            }
            case 3: {
                int valor;
                cout << "Digite o valor a ser pesquisado: ";
                cin >> valor;
                if (pesquisar(raiz, valor)) {
                    cout << "Valor " << valor << " encontrado na arvore" << endl;
                } else {
                    cout << "Valor " << valor << " nao encontrado" << endl;
                }
                break;
            }
            default:
                cout << "Opcao invalida. Tente novamente" << endl;
                break;
        }
    }

    return 0;
}
