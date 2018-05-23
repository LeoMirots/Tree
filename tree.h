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

//PRIMITIVE
bool empty(tree t);
tree emptyTree(void);
element root(tree t);
tree left(tree t);
tree right(tree t);
tree consTree(element e, tree left, tree right);
void showEl(char a);

//ESPLORAZIONE
void preOrder(tree);
void inOrder(tree);
void postOrder(tree);

//NOT-PRIMITIVE
bool memberTree(element e, tree t);
bool memberTreeOrd(element e, tree t);
tree copy(tree t);
tree insBinOrdTree(element e, tree t);
tree deleteElement(tree t, element e);


#endif // !TREE_H