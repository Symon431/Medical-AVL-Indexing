#include "avltree.h"
#include <stdlib.h>


AVLTree CreateTree(void) {
    return NULL;
}

AVLTree MakeEmptyTree(AVLTree t) {
    if (t != NULL) {
        MakeEmptyTree(t->left);
        MakeEmptyTree(t->right);
        free(t);
    }
    return NULL;
}

int AVLTreeHeight(AVLTree t) {
    if (t == NULL)
        return -1;
    else
        return t->height;
}

AVLTree SingleRotateWithLeft(AVLTree k2) {
    AVLTree k1;
    k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;

    k1->height = Max(AVLTreeHeight(k1->left), AVLTreeHeight(k1->right)) + 1;
    return k1;
}

AVLTree SingleRotateWithRight(AVLTree k1) {
    AVLTree k2;
    k2 = k1->left;
    k1->left = k2->right;
    k2->right = k1;

    k2->height = Max(AVLTreeHeight(k2->left), AVLTreeHeight(k2->right)) + 1;
    return k2;
}

AVLTree DoubleRotateWithLeft(AVLTree k3) {
    k3->right = SingleRotateWithRight(k3->right);
    k3 = SingleRotateWithLeft(k3);

    k3->height = Max(AVLTreeHeight(k3->right), AVLTreeHeight(k3->left)) + 1;
    return k3;
}

AVLTree DoubleRotateWithRight(AVLTree k3) {
    k3->left = SingleRotateWithLeft(k3->left);
    k3 = SingleRotateWithRight(k3);
    k3->height = Max(AVLTreeHeight(k3->right), AVLTreeHeight(k3->left)) + 1;
    return k3;
}

int Max(int x, int y) {
    if (x >= y)
        return x;
    else
        return y;
}
