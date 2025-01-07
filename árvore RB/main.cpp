// Aluna: Manuela F. Balieiro de Araújo
#include "arvoreRB.h"
#include <iostream>

using namespace std;

int main() {
  NoRB *raiz = nullptr;
  int opcao, valor;

  while (true) {
    cout << "--- Menu Arvore RB ---" << endl;
    cout << "1. Inserir" << endl;
    cout << "2. Remover" << endl;
    cout << "3. Pesquisar" << endl;
    cout << "4. Exibir Árvore" << endl;
    cout << "5. Sair" << endl;
    cout << "Escolha uma opção: ";
    cin >> opcao;

    if (opcao == 5) { // Caso o usuário escolha a opção 5 para sair, encerra o programa
      cout << "Encerrando o programa..." << endl;
      break; // Encerra o loop while
    }

    switch (opcao) {
    case 1: {
      cout << "Digite o valor a ser inserido: ";
      cin >> valor;
      raiz = inserir(raiz, valor);
      cout << "Valor " << valor << " inserido na arvore com sucesso" << endl;
      break;
    }
    case 2: {
      cout << "Digite o valor a ser removido: ";
      cin >> valor;
      raiz = remover(raiz, valor);
      cout << "Valor " << valor << " removido da arvore com sucesso" << endl;
      break;
    }
    case 3: {
      cout << "Digite o valor a ser pesquisado: ";
      cin >> valor;
      NoRB *resultado = pesquisar(raiz, valor);
      if (resultado != nullptr) {
        cout << "Valor " << valor << " encontrado na arvore" << endl;
      } else {
        cout << "Valor " << valor << " nao encontrado na arvore" << endl;
      }
      break;
    }
    case 4: {
      cout << "Exibindo arvore Rubro-Negra: " << endl;
      mostrarArvore(raiz);
      break;
    }
    default:
      cout << "Opcao invalida. Tente novamente" << endl;
      break;
    }
  }

  return 0;
}
