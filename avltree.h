//
// Created by labuser on 12/29/2024.
//

#ifndef AVL_ASSIGNMENT_AVLTREE_H
#define AVL_ASSIGNMENT_AVLTREE_H



typedef struct Node *AVLTree;
struct Node {
    char Name[50];
    char surname[50];
    char DateOfBirth[50];
    float heightPat;/*patients height*/
    int weight;
    float BMI;
    AVLTree left;
    AVLTree right;
    AVLTree next;/*points to another node if it has the same BMI values*/
    int height;
};

AVLTree CreateTree(void);

AVLTree MakeEmptyTree(AVLTree);

AVLTree SingleRotateWithLeft(AVLTree);

AVLTree SingleRotateWithRight(AVLTree);

AVLTree DoubleRotateWithLeft(AVLTree);

AVLTree DoubleRotateWithRight(AVLTree);

int AVLTreeHeight(AVLTree);

int Max(int, int);





#endif //AVL_ASSIGNMENT_AVLTREE_H
