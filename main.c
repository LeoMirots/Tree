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
	if (moveUp(left(c), Root(c)) == c)
		printf("Bella Roba, moveUp funzia;");
	tree prova_destroy = copyTree(a);
	inOrder(c);
	printf("\n");
	DeleteAllTree(c->left);
	printf("\n");
	node *e = searchBinTree(1, a);
	Search_and_Destroy(1, a);
	inOrder(a);
	printf("\n");
	InsBinOrdTree(4, a);
	a = Search_and_Destroy(3, a);
	inOrder(a);
	printf("\n");
	prova_destroy = Search_and_Destroy(1, prova_destroy);
	inOrder(prova_destroy);
	printf("\n");
	prova_destroy = Search_and_Destroy(3, prova_destroy);
	inOrder(prova_destroy);
	printf("\n");
	prova_destroy = Search_and_Destroy(3, prova_destroy);
	inOrder(prova_destroy);
	printf("\n");
	prova_destroy = Search_and_Destroy(4, prova_destroy);
	system("PAUSE");
	return 0;
}