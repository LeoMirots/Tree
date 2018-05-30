#ifndef TREE_H
#define TREE_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef  int  element;			//DEFINIZIONE ELEMENT

typedef struct  treeElement {
	element value;
	struct treeElement  *left, *right;
} node;

typedef  node *tree;


void showEl(element e);
bool IsEqual(element a, element b);

//PRIMITIVE
bool empty(tree t);
tree emptyTree(void);
element root(tree t);
tree left(tree t);
tree right(tree t);
tree consTree(element e, tree left, tree right);

//ESPLORAZIONE
void preOrder(tree);
void inOrder(tree);
void postOrder(tree);

//NOT-PRIMITIVE
bool detectTreeOrd(element e, tree t);
tree copy(tree t);
tree insertBinOrdTree(element e, tree t);
bool detectTree(element e, tree t);
tree search(element e, tree t);
tree search_and_destroy(element e, tree t);
tree ConstVettAnticipato(int* vett, int* next);
tree ConstInputAnticipato(void);

#endif // !TREE_H