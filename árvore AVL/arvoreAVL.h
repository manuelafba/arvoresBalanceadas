#include <iostream>
#include <cstdlib>

using namespace std;

typedef struct Node TreeNode;

struct Node {
    int chave;
    TreeNode *esquerda;
    TreeNode *direita;
    int altura; 
};

typedef TreeNode* AVLTree;