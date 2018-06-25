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
	if (Empty(root) == false)
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
		if (IsRoot == true)
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
		if (x != xr_tmp)
			x->right = xr_tmp;

		if (Empty(pl) == false)
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

/*------------Element2--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

tree2 Root2(tree2 t)
{
	if (Empty2(t) == true || t->root == NULL)
		return t;
	return t->root;
}

size_t height2(tree2 t)
{
	size_t l = 1, r = 1;
	if (Empty2(t) == true)
		return 0;
	l += height2(left2(t));
	r += height2(right2(t));
	if (l >= r)
		return l;
	return r;
}

element2 headTree2(tree2 t)
{
	return t->value;
}

tree2 left2(tree2 t)
{
	return t->left;
}

tree2 right2(tree2 t)
{
	return t->right;
}

tree2 ConsTree2(element2 e, tree2 left2, tree2 right2, tree2 root)
{
	tree2 t = malloc(sizeof(node2));
	AssignElement2(&t->value, e);
	t->root = t;
	
	t->left = left2;		t->right = right2;
	if(Empty2(root) == false)
		t->root = root;
	return t;
}

tree2 emptyTree2(void)
{
	return NULL;
}

bool Empty2(tree2 t)
{
	if (t == NULL)
		return true;
	return false;
}

/*------------------------------------------------------------------------------------------------*/

bool detectTree2(element2 e, tree2 t)
{
	if (Empty2(t) == true)
		return false;
	if (IsEqual2(e, t->value))
		return true;
	return (detectTree2(e, t->left) ||
			detectTree2(e, t->right));
}

bool detectOrdTree2(element2 e, tree2 t)
{
	if (Empty2(t) == true)
		return false;
	int x = cmp2(e, t->value);
	
	switch (x)
	{
	case 0:
		return true;
	case -1:
		return detectOrdTree2(e, t->left);
	case 1:
		return detectOrdTree2(e, t->right);
	default:
		return false;
	}
}

tree2 InsBinOrdTree2(element2 e, tree2 t)
{
	if (Empty2(t) == true)
	{
		t = ConsTree2(e, emptyTree2(), emptyTree2(), emptyTree2());
		return t;
	}

	int x = cmp2(e, headTree2(t));
	switch (x)
	{
	case -1:
		if (Empty2(left2(t)) == true)
		{
			t->left = ConsTree2(e, emptyTree2(), emptyTree2(), t->root);
			return t->left;
		}
		t = left2(t);
		break;
	case 1:
		if (Empty2(right2(t)) == true)
		{
			t->right = ConsTree2(e, emptyTree2(), emptyTree2(), t->root);
			return t->right;
		}
		t = right2(t);
		break;
	default:							/*Nel caso che l'elemento che sto considerando sia = a t->value, per convenzione vado a sinistra;*/
		if (Empty2(left2(t)) == true)
		{
			t->left = ConsTree2(e, emptyTree2(), emptyTree2(), t->root);
			return t->left;
		}
		t = left2(t);
		break;
	}
	return InsBinOrdTree2(e, t);
}

tree2 copyTree2(tree2 t)
{
	if (Empty2(t) == true)
		return emptyTree2();
	tree2 c = emptyTree2();
	c = ConsTree2(t->value, copyTree2(left2(t)), copyTree2(right2(t)), Root2(c));
	SetRootTree2(c, c);
	return c;
}

void SetRootTree2(tree2 t, node2 *NewRoot)
{
	if (Empty2(t) == true)
		return;
	t->root = NewRoot;
	SetRootTree2(left2(t), NewRoot);		SetRootTree2(right2(t), NewRoot);
}

bool Destroy2(node2 *p)
{
	if (p == NULL)
		return true;
	int ctrl = DeleteElement2(p->value);
	if (ctrl != 0)
		return false;
	if (p == p->root)
	{
		SetRootTree2(left2(p), left2(p));		SetRootTree2(right2(p), right2(p));
	}
	free(p);
	return true;
}

tree2 moveUp2(tree2 t, tree2 Root2)
{
	if (Empty2(t) == true || Empty2(Root2) == true)
		return emptyTree2();

	if (left2(Root2) == t || right2(Root2) == t)
		return Root2;
	return moveUp2(t, left2(Root2));		return moveUp2(t, right2(Root2));
}

tree2 succ2(tree2 t)
{
	if (Empty2(t) == true)
		return emptyTree2();
	if (Empty2(right2(t)) == true)
		return emptyTree2();
	tree2 tmp = right2(t);
	tree2 pl_tmp = emptyTree2();
	while (Empty2(left2(tmp)) == false)
	{
		pl_tmp = tmp;
		tmp = left2(tmp);
	}
	return tmp;
}

tree2 Search_and_Destroy2(element2 e, tree2 t)
{
	if (Empty2(t) == true)
		return t;
	if (detectOrdTree2(e, t) == false)
		return t;

	tree2 pl = emptyTree2();		tree2 pr = emptyTree2();		/*Puntatori al padre di t, previous left2 & previous right2;*/
															/*pl significa che il padre del nodo da eliminare lo ha come figlio sinistro, di conseguenza pr è emptyTree2();*/

	while (Empty2(t) == false && IsEqual2(e, headTree2(t)) == false) /*Cerco il nodo da eliminare ricordando di chi è figlio;*/
	{
		if (cmp2(e, headTree2(t)) == -1)
		{
			pl = t;		pr = emptyTree2();	t = left2(t);
		}

		if (cmp2(e, headTree2(t)) == 1)
		{
			pl = emptyTree2();	 pr = t;	t = right2(t);
		}
	}
	
	bool IsRoot = false;									/*Mi dice se il nodo da eliminare è la radice dell'albero;*/
	if (Empty2(pl) == true && Empty2(pr) == true)
		IsRoot = true;
	
	/*Il nodo da eliminare può essere una foglia, oppure avere 1 o 2 figli, 3 casi in tutto:*/
	
	/*Il nodo è una foglia: occorre solo eliminare il nodo;*/
	if (Empty2(left2(t)) == true && Empty2(right2(t)) == true)
	{
		if (IsRoot == true)
			return emptyTree2();

		Destroy2(t);

		if (Empty2(pl) == false)
			pl->left = emptyTree2();		/*Una foglia non ha figli;*/
		else
			pr->right = emptyTree2();
		return Root2(pl);
	}

	/*Il nodo ha un figlio: occorre sostituire il figlio al nodo da eliminare;*/
	tree2 next = emptyTree2();		/*Variabile temporanea per tenere traccia del figlio del nodo da eliminare;*/
	
	if (Empty2(left2(t)) == true && Empty2(right2(t)) == false)			/*Se il nodo da eliminare ha SOLO un figlio destro:*/
		next = right2(t);											/*Salvo il puntatore dentro "next";*/
	else															/*Altrimenti:*/
		if (Empty2(left2(t)) == false && Empty2(right2(t)) == true)		/*Se il nodo ha SOLO un figlio sinistro: */
			next = left2(t);											/*Salvo il puntatore in next;*/
	
	if (Empty2(next) == false)
	{
		if(IsRoot == true)
		{
			SetRootTree2(next, next);
		}

		Destroy2(t);													/*Elimino il nodo da eliminare;*/

		if (Empty2(pl) == false)										/*Se il nodo da eliminare era il figlio sinistro del padre:*/
			pl->left = next;										/*Imposto il figlio sinistro del padre all'indirizzo del figlio del nodo da eliminare;*/
		else														/*Altrimenti, il nodo da eliminare può essere il figlio destro o la radice dell'albero;*/
			if (Empty2(pr) == false)									/*Se il nodo da eliminare era il figlio destro del padre:*/
				pr->right = next;									/*Imposto il figlio destro del padre all'indirizzo del figlio di del nodo da eliminare;*/
																		/*Altrimenti, il nodo da eliminare non ha padre ed era per forza la radice dell'albero con un solo figlio;*/
		return Root2(next);											/*Ritorno l'indirizzo della radice dell'albero;*/
	}

	/*Se il nodo da eliminare ha 2 figli: occorre eliminarlo e sostituirlo con il nodo succ2()*/
	if (Empty2(left2(t)) == false && Empty2(right2(t)) == false)
	{
		tree2 x = right2(t);						/*x è il puntatore al nodo succ2() di t;*/
		tree2 pl_x = x;							/*Puntatore al padre di x, se x è la radice pl_x = x il succ2() di t;*/
		while (Empty2(left2(x)) == false)
		{
			pl_x = x;
			x = left2(x);
		}

		tree2 xl_tmp = t->left;
		tree2 xr_tmp = t->right;

		if (IsRoot == true)
		{
			SetRootTree2(t, x);
		}

		Destroy2(t);

		if (Empty2(right2(x)) == false)
			pl_x->left = right2(x);
		else
			pl_x->left = emptyTree2();

		x->left = xl_tmp;
		if(x != xr_tmp)
			x->right = xr_tmp;

		if(Empty2(pl) == false)
			pl->left = x;
		return Root2(x);
	}
	return NULL;		/*Qui non deve mai arrivare, i casi si estinguono nelle precedenti parentesi;*/
}

void DeleteAllTree2(tree2 t)
{
	if (Empty2(t) == true)
		return;
	t = Root2(t);
	SetRootTree2(left2(t), left2(t));		SetRootTree2(right2(t), right2(t));
	DeleteElement2(t->value);
	DeleteAllTree2(left2(t));		DeleteAllTree2(right2(t));
	free(t);
}

node2 *searchBinTree2(element2 e, tree2 t)
{
	if (Empty2(t) == true)
		return emptyTree2();
	if (IsEqual2(e, t->value) == true)
		return t;
	return searchBinTree2(e, left2(t));		return searchBinTree2(e, right2(t));
}

/*-----Funzioni di visita dell'albero------------------------------------------------------------------------------------------------------*/

void preOrder2(tree2 t)
{
	if (Empty2(t) == false)
	{
		printf("\t"); 
		PrintElement2(headTree2(t));
		preOrder2(left2(t)); preOrder2(right2(t));
	}
}

void inOrder2(tree2 t)
{
	if (Empty2(t) == false)
	{
		inOrder2(left2(t));
		printf("\t"); PrintElement2(headTree2(t));
		inOrder2(right2(t));
	}
}

void postOrder2(tree2 t)
{
	if (Empty2(t) == false) {
		postOrder2(left2(t)); postOrder2(right2(t));
		printf("\t"); PrintElement2(headTree2(t));
	}
}