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
		return detectOrdTree(e, t->right);
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

bool Destroy(node *p)
{
	if (p == NULL)
		return true;
	int ctrl = DeleteElement(p->value);
	if (ctrl != 0)
		return false;
	if (p == p->root)
	{
		SetRootTree(left(p), left(p));		SetRootTree(right(p), right(p));
	}
	free(p);
	return true;
}

tree moveUp(tree t, tree Root)
{
	if (Empty(t) == true || Empty(Root) == true)
		return emptyTree();

	if (left(Root) == t || right(Root) == t)
		return Root;
	return moveUp(t, left(Root));		return moveUp(t, right(Root));
}

tree succ(tree t)
{
	if (Empty(t) == true)
		return emptyTree();
	if (Empty(right(t)) == true)
		return emptyTree();
	tree tmp = right(t);
	tree pl_tmp = emptyTree();
	while (Empty(left(tmp)) == false)
	{
		pl_tmp = tmp;
		tmp = left(tmp);
	}
	return tmp;
}

tree Search_and_Destroy(element e, tree t)
{
	if (Empty(t) == true)
		return t;
	if (detectOrdTree(e, t) == false)
		return t;

	tree pl = emptyTree();		tree pr = emptyTree();		/*Puntatori al padre di t, previous left & previous right;*/
															/*pl significa che il padre del nodo da eliminare lo ha come figlio sinistro, di conseguenza pr è emptyTree();*/

	while (Empty(t) == false && IsEqual(e, headTree(t)) == false) /*Cerco il nodo da eliminare ricordando di chi è figlio;*/
	{
		if (cmp(e, headTree(t)) == -1)
		{
			pl = t;		pr = emptyTree();	t = left(t);
		}

		if (cmp(e, headTree(t)) == 1)
		{
			pl = emptyTree();	 pr = t;	t = right(t);
		}
	}
	
	bool IsRoot = false;									/*Mi dice se il nodo da eliminare è la radice dell'albero;*/
	if (Empty(pl) == true && Empty(pr) == true)
		IsRoot = true;
	
	/*Il nodo da eliminare può essere una foglia, oppure avere 1 o 2 figli, 3 casi in tutto:*/
	
	/*Il nodo è una foglia: occorre solo eliminare il nodo;*/
	if (Empty(left(t)) == true && Empty(right(t)) == true)
	{
		if (IsRoot == true)
			return emptyTree();

		Destroy(t);

		if (Empty(pl) == false)
			pl->left = emptyTree();		/*Una foglia non ha figli;*/
		else
			pr->right = emptyTree();
		return Root(pl);
	}

	/*Il nodo ha un figlio: occorre sostituire il figlio al nodo da eliminare;*/
	tree next = emptyTree();		/*Variabile temporanea per tenere traccia del figlio del nodo da eliminare;*/
	
	if (Empty(left(t)) == true && Empty(right(t)) == false)			/*Se il nodo da eliminare ha SOLO un figlio destro:*/
		next = right(t);											/*Salvo il puntatore dentro "next";*/
	else															/*Altrimenti:*/
		if (Empty(left(t)) == false && Empty(right(t)) == true)		/*Se il nodo ha SOLO un figlio sinistro: */
			next = left(t);											/*Salvo il puntatore in next;*/
	
	if (Empty(next) == false)
	{
		if(IsRoot == true)
		{
			SetRootTree(next, next);
		}

		Destroy(t);													/*Elimino il nodo da eliminare;*/

		if (Empty(pl) == false)										/*Se il nodo da eliminare era il figlio sinistro del padre:*/
			pl->left = next;										/*Imposto il figlio sinistro del padre all'indirizzo del figlio del nodo da eliminare;*/
		else														/*Altrimenti, il nodo da eliminare può essere il figlio destro o la radice dell'albero;*/
			if (Empty(pr) == false)									/*Se il nodo da eliminare era il figlio destro del padre:*/
				pr->right = next;									/*Imposto il figlio destro del padre all'indirizzo del figlio di del nodo da eliminare;*/
																		/*Altrimenti, il nodo da eliminare non ha padre ed era per forza la radice dell'albero con un solo figlio;*/
		return Root(next);											/*Ritorno l'indirizzo della radice dell'albero;*/
	}

	/*Se il nodo da eliminare ha 2 figli: occorre eliminarlo e sostituirlo con il nodo succ()*/
	if (Empty(left(t)) == false && Empty(right(t)) == false)
	{
		tree x = right(t);						/*x è il puntatore al nodo succ() di t;*/
		tree pl_x = x;							/*Puntatore al padre di x, se x è la radice pl_x = x il succ() di t;*/
		while (Empty(left(x)) == false)
		{
			pl_x = x;
			x = left(x);
		}

		tree xl_tmp = t->left;
		tree xr_tmp = t->right;

		if (IsRoot == true)
		{
			SetRootTree(t, x);
		}

		Destroy(t);

		if (Empty(right(x)) == false)
			pl_x->left = right(x);
		else
			pl_x->left = emptyTree();

		x->left = xl_tmp;
		if(x != xr_tmp)
			x->right = xr_tmp;

		if(Empty(pl) == false)
			pl->left = x;
		return Root(x);
	}
	return NULL;		/*Qui non deve mai arrivare, i casi si estinguono nelle precedenti parentesi;*/
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