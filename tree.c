#include "tree.h"

tree Root(tree t)
{
	if (Empty(t) == true || t->root == NULL)
		return t;
	return t->root;
}

size_t height(tree t)
{
	size_t l = 1, r = 1;
	if (Empty(t) == true)
		return 0;
	l += height(left(t));
	r += height(right(t));
	if (l >= r)
		return l;
	return r;
}

element headTree(tree t)
{
	return t->value;
}

tree left(tree t)
{
	return t->left;
}

tree right(tree t)
{
	return t->right;
}

tree ConsTree(element e, tree left, tree right, tree root)
{
	tree t = malloc(sizeof(node));
	AssignElement(&t->value, e);
	t->root = t;
	
	t->left = left;		t->right = right;
	if(Empty(root) == false)
		t->root = root;
	return t;
}

tree emptyTree(void)
{
	return NULL;
}

bool Empty(tree t)
{
	if (t == NULL)
		return true;
	return false;
}

/*------------------------------------------------------------------------------------------------*/

bool detectTree(element e, tree t)
{
	if (Empty(t) == true)
		return false;
	if (IsEqual(e, t->value))
		return true;
	return (detectTree(e, t->left) ||
			detectTree(e, t->right));
}

bool detectOrdTree(element e, tree t)
{
	if (Empty(t) == true)
		return false;
	int x = cmp(e, t->value);
	
	switch (x)
	{
	case 0:
		return true;
	case -1:
		return detectOrdTree(e, t->left);
	case 1:
		return detectOrdTree(e, t->left);
	default:
		return false;
	}
}

tree InsBinOrdTree(element e, tree t)
{
	if (Empty(t) == true)
	{
		t = ConsTree(e, emptyTree(), emptyTree(), emptyTree());
		return t;
	}

	int x = cmp(e, headTree(t));
	switch (x)
	{
	case -1:
		if (Empty(left(t)) == true)
		{
			t->left = ConsTree(e, emptyTree(), emptyTree(), t->root);
			return t->left;
		}
		t = left(t);
		break;
	case 1:
		if (Empty(right(t)) == true)
		{
			t->right = ConsTree(e, emptyTree(), emptyTree(), t->root);
			return t->right;
		}
		t = right(t);
		break;
	default:							/*Nel caso che l'elemento che sto considerando sia = a t->value, per convenzione vado a sinistra;*/
		if (Empty(left(t)) == true)
		{
			t->left = ConsTree(e, emptyTree(), emptyTree(), t->root);
			return t->left;
		}
		t = left(t);
		break;
	}
	return InsBinOrdTree(e, t);
}

tree copyTree(tree t)
{
	if (Empty(t) == true)
		return emptyTree();
	tree c = emptyTree();
	c = ConsTree(t->value, copyTree(left(t)), copyTree(right(t)), Root(c));
	SetRootTree(c, c);
	return c;
}

void SetRootTree(tree t, node *NewRoot)
{
	if (Empty(t) == true)
		return;
	t->root = NewRoot;
	SetRootTree(left(t), NewRoot);		SetRootTree(right(t), NewRoot);
}

void DeleteAllTree(tree t)
{
	if (Empty(t) == true)
		return;
	t = Root(t);
	SetRootTree(left(t), left(t));		SetRootTree(right(t), right(t));
	DeleteElement(t->value);
	DeleteAllTree(left(t));		DeleteAllTree(right(t));
	free(t);
}

node *searchBinTree(element e, tree t)
{
	if (Empty(t) == true)
		return emptyTree();
	if (IsEqual(e, t->value) == true)
		return t;
	return searchBinTree(e, left(t));		return searchBinTree(e, right(t));
}

/*-----Funzioni di visita dell'albero------------------------------------------------------------------------------------------------------*/

void preOrder(tree t)
{
	if (Empty(t) == false)
	{
		printf("\t"); 
		PrintElement(headTree(t));
		preOrder(left(t)); preOrder(right(t));
	}
}

void inOrder(tree t)
{
	if (Empty(t) == false)
	{
		inOrder(left(t));
		printf("\t"); PrintElement(headTree(t));
		inOrder(right(t));
	}
}

void postOrder(tree t)
{
	if (Empty(t) == false) {
		postOrder(left(t)); postOrder(right(t));
		printf("\t"); PrintElement(headTree(t));
	}
}