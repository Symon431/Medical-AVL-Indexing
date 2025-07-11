#include <stdio.h>
#include <stdlib.h>

#include "avltree.h"

#define FALSE 0
#define TRUE 1

AVLTree InsertPatients(float, AVLTree, AVLTree);

AVLTree loadPatients(char *fileName);

void InfoPatients(AVLTree, float);

AVLTree youngestPatient(AVLTree);

void DisplayPatients(AVLTree);

int dateToInteger(char *);

void Menu();

int main(int argv, char *argc[]) {
    if (argv != 2) {
        printf("Invalid number of arguments.\n");
        exit(1);
    }

    AVLTree TREE;
    TREE = loadPatients(argc[1]);




    int command;
    do {
        Menu();
        scanf("%d", &command);

        switch (command) {
            case 1: {
                DisplayPatients(TREE);
                break;
            }
            case 2: {
                float Bmi;
                printf("Enter the patients BMI:\n");
                scanf("%f", &Bmi);
                InfoPatients(TREE, Bmi);
                break;
            }
            case 3: {
                AVLTree youngest;
                youngest = youngestPatient(TREE);
                if (youngest == NULL)
                    printf("The tree is empty.\n");
                else
                    printf("%s %s is the youngest patient.\n", youngest->Name, youngest->surname);
                break;
            }

            case 4: {
                printf("\n");
                exit(1);
            }
            default: {
                printf("Invalid choice.\n");
                break;
            }
        }
    } while (command != 4);


    return 0;
}


AVLTree InsertPatients(float BMI, AVLTree root, AVLTree newNode) {

    if (root == NULL) {
        root = newNode;

    } else if (BMI < root->BMI) {
        root->left = InsertPatients(BMI, root->left, newNode);

        if (AVLTreeHeight(root->left) - AVLTreeHeight(root->right) == 2)
            if (BMI < root->left->BMI)
                root = SingleRotateWithLeft(root);
            else
                root = DoubleRotateWithRight(root);
    } else if (BMI > root->BMI) {
        root->right = InsertPatients(BMI, root->right, newNode);
        if (AVLTreeHeight(root->right) - AVLTreeHeight(root->left) == 2)
            if (BMI > root->right->BMI)
                root = SingleRotateWithRight(root);
            else
                root = DoubleRotateWithLeft(root);
    } else {
        AVLTree temp;
        temp = root;

        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;/* If there are 2 or more nodes with the same BMI, they will form a linked list */
    }

    root->height = Max(AVLTreeHeight(root->left), AVLTreeHeight(root->right)) + 1;

    return root;
}

void DisplayPatients(AVLTree t) {

    if (t != NULL) {
        DisplayPatients(t->left);

        AVLTree temp;
        temp = t;
        while (temp != NULL) {
            printf("%s %s %s %.1f %d %.1f\n", temp->Name, temp->surname, temp->DateOfBirth, temp->heightPat, temp->weight, temp->BMI);
            temp = temp->next;
        }
        DisplayPatients(t->right);
    }

}




AVLTree loadPatients(char *fileName) {
    FILE *filein;
    filein = fopen(fileName, "r");

    if (filein == NULL) {
        printf("The file could not be read.\n");
        exit(1);
    }


    AVLTree T;
    T = CreateTree();


    char buffer[100];
    while (fgets(buffer, sizeof(buffer), filein) != NULL) {

        AVLTree newNode = (AVLTree) malloc(sizeof(struct Node));
        if (newNode == NULL) {
            printf("New node could not be allocated memory.\n");
            exit(1);
        }

        sscanf(buffer, "%49[^;];%49[^;];%49[^;];%f;%d;%f", newNode->Name, newNode->surname, newNode->DateOfBirth,
               &newNode->heightPat, &newNode->weight, &newNode->BMI);

        newNode->height = 0;
        newNode->left = newNode->right = newNode->next = NULL;

        T = InsertPatients(newNode->BMI, T, newNode);
    }

    fclose(filein);
    return T;
}

void InfoPatients(AVLTree T, float BMI) {

    AVLTree temp;

    while (T != NULL) {
        if (BMI < T->BMI)
            T = T->left;
        else if (BMI > T->BMI)
            T = T->right;
        else {
            temp = T;
            while (temp != NULL) {
                printf("%s %s %s %.1f %d %.1f\n", temp->Name, temp->surname, temp->DateOfBirth, temp->heightPat,
                       temp->weight, temp->BMI);
                temp = temp->next;
            }
            return;
        }
    }
    printf("There is not an available patient who has a BMI of %.2f\n", BMI);
    /*The time complexity of the function is O(log n) since each comparison made halves the space available.
     * We could store patients with the same BMI in their AVL Tree.*/
}


// Function is used to convert date  to YYYYMMDD integer
int dateToInteger(char *date) {
    int Day, Month, Year;
    sscanf(date, "%2d/%2d/%4d", &Day, &Month, &Year);
    return Year * 10000 + Month * 100 + Day;  // This gives YYYYMMDD format so that the comparisons will be in integers rather than characters
}

AVLTree youngestPatient(AVLTree T) {
    if (T == NULL)
        return NULL;

    AVLTree youngest = T;
    int youngestDate = dateToInteger(youngest->DateOfBirth);


    AVLTree leftYoungest = youngestPatient(T->left);
    AVLTree rightYoungest = youngestPatient(T->right);


    if (leftYoungest != NULL) {
        int leftDate = dateToInteger(leftYoungest->DateOfBirth);
        if (leftDate > youngestDate) {
            youngest = leftYoungest;
            youngestDate = leftDate;
        }
    }

    if (rightYoungest != NULL) {
        int rightDate = dateToInteger(rightYoungest->DateOfBirth);
        if (rightDate > youngestDate) {
            youngest = rightYoungest;
            youngestDate = rightDate;
        }
    }

    AVLTree temp = youngest->next;
    while (temp != NULL) {
        int Date_temp = dateToInteger(temp->DateOfBirth);
        if (Date_temp > youngestDate) {
            youngest = temp;
            youngestDate = Date_temp;
        }
        temp = temp->next;
    }

    return youngest;
    /*the time complexity for the function is O(n), all the nodes in the tree are visited to find the youngest patient.*/
}


void Menu() {
    printf("\n-------Menu-------\n"
           "(1)Display the full index of patients\n"
           "(2)Display the details of the patients\n"
           "(3)Display the youngest patient\n"
           "(4)Exit\n"
           "Enter your option:\n");
}