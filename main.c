#include "tree.h"

int main(void)
{
	tree a = emptyTree();
	a = InsBinOrdTree(3, a);
	a = InsBinOrdTree(1, a);
	a = Root(a);
	a = InsBinOrdTree(4, a);
	a = Root(a);
	a = InsBinOrdTree(3, a);
	a = Root(a);
	size_t h = height(a);
	inOrder(a);
	printf("\n");
	preOrder(a);
	printf("\n");
	postOrder(a);
	printf("\n");
	tree c = copyTree(a);
	inOrder(c);
	printf("\n");
	DeleteAllTree(c->left);
	printf("\n");
	node *e = searchBinTree(1, a);
	system("PAUSE");
	return 0;
}