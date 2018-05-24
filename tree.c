#include "tree.h"

//PRIMITIVE
bool empty(tree t)
{
	return (t == NULL);
}

tree emptyTree(void)
{
	return NULL;
}

element root(tree t) {
	if (empty(t) == true)
		return;	/* Non c'è valore di ritorno se l'albero è vuoto*/
	else return t->value;
}

tree left(tree t) {
	if (empty(t) == true)
	 return NULL;
	return t->left;
}

tree right(tree t) {
	if (empty(t) == true)
	 return NULL;
	return t->right;
}

tree consTree(element e, tree left, tree right)
{
	tree t = (node*)malloc(sizeof(node));
	t->value = e;
	t->left = left;    t->right = right;
	return t;
}

void showEl(element a) {		/*Relativa all'elemento;*/
	if(a != NULL)
		printf("%d", a);
}

int cmp(element a, element b)
{
	if(a == b)
		return 0;
	if(a < b)
		return -1;
	return 1;
}

//ESPLORAZIONE
void preOrder(tree t) {
	if (empty(t) == false)
	{
		printf("\t");
		showEl(root(t));
			preOrder(left(t));
			preOrder(right(t));
	}
}

void inOrder(tree t)
{
	if (!empty(t)) {
			inOrder(left(t));
		printf("\t");
		showEl(root(t));
			inOrder(right(t));
	}
}


void postOrder(tree t) {
	if (!empty(t)) {
			postOrder(left(t));
			postOrder(right(t));
		printf("\t");
		showEl(root(t));
	}
}

//NOT-PRIMITIVE
bool memberTree(element e, tree t) {
	if (empty(t) == true)
		return false;
	if (cmp(e, root(t) == true))
		return true;
	return (memberTree(e, left(t)) || memberTree(e, right(t)));
}


bool memberTreeOrd(element e, tree t)
{
	if (empty(t) == true)
		return false;
	switch (cmp(e, root(t)))
	{
		case 0:
			return true;
		case -1:
			return memberTreeOrd(e, left(t));
		case 1:
			return memberTreeOrd(e, right(t));
	}
}

tree copy(tree t)
{
	if (empty(t) == true)
		return NULL;
	return consTree(root(t), copy(left(t)), copy(right(t)));
}

int height(tree t)
{
	if (empty(t) == true)
		return 0;
	int hl = height(left(t)), hr = height(right(t));
	if (hl > hr) return 1 + hl;
	return 1 + hr;
}

tree insertBinOrdTree(element e, tree t)
{
	tree l = t;
	if (empty(t))
		return consTree(e, emptyTree(), emptyTree());

	while (empty(t) == false)
	{
		if (cmp(e, root(t)) == 0 || cmp(e, root(t)) == - 1)			/* Se e <= root(t)*/
		{
			if (empty(left(t)))
			{
				t->left = consTree(e, emptyTree(), emptyTree());
				t = left(t);
			}
			t = left(t);
		}
		/*Altrimenti, se e > root(t):*/
		if (empty(t->right) == true)
		{
				t->right = consTree(e, emptyTree(), emptyTree());
				t = right(t);
		}
			t = right(t);
		}
	}
	return l;
}

bool detect(element e, tree t)
{
	if(empty(t) == true)
		return false;
	if(IsEqual(e, t) == true)
		return true;
	if(detect(e, t->left) == true)
		return true;
	if(detect(e, t->right) == true)
		return true;
	return false;
}

tree search(element e, tree t)
{
	/*"pl" e "pr" i puntatori per memorizzare se la root in questione è
		figlia sinistra o destra.*/
	tree pl = NULL, pr = NULL;

	if(detect(e, t) == false)
	{
		return NULL;
	}
	//Cerco l'elemento:
	while (IsEqual(e, root(t)) == false && empty(t) == false)
	{
		if (cmp(e, root(t)) == -1)
		{
			pl = t; pr = emptyTree(); t = left(t);
		}
		/*Altrimenti, se e > root(t):*/
		pl = emptyTree(); pr = t; t = right(t);
	}
	return t;
}


tree search_and_destroy(element e, tree t)
{
	/*-"l" è puntatore alla root dell'albero originale;
	  -"next" puntatore all'elemento successivo su cui scorrere;
	  -"pl" e "pr" i puntatori per memorizzare se la root in questione è
	  figlia sinistra o destra.*/
	tree l = t, next;
	tree pl = NULL, pr = NULL;

	//Cerco l'elemento:
	while (IsEqual(e, root(t)) == false && empty(t) == false)
	{
		if (cmp(e, root(t)) == -1)
		{
			pl = t; pr = emptyTree(); t = left(t);
		}
		/*Altrimenti, se e > root(t):*/
		pl = emptyTree(); pr = t; t = right(t);
	}

	if (empty(t) == false)
	{
		// Il nodo da eliminare è una foglia:
		if (empty(left(t)) && empty(right(t))) {
			if (t == l)	// Se e' la root ritorno un albero vuoto;
				return emptyTree();
			next = emptyTree();
		}

		// Il nodo da eliminare ha un solo figlio
		if (empty(left(t)) && !empty(right(t))) {	//Se � quello destro:
			// Se e' la root ritorno il figlio
			if (t == l)
				return right(t);
			next = right(t);
		}
		if (!empty(left(t)) && empty(right(t))) {	//Se � quello sinistro:
			// Se e' la root ritorno il figlio
			if (t == l)
				return left(t);
			next = left(t);
		}

		// Il nodo da eliminare ha due figli
		pr = t;
		pl = emptyTree();

		next = right(t);	//Vai a destra;
		if (!empty(next))
			while (!empty(left(next))) {	//Scorri fino a trovare l'ultimo;
				pr = emptyTree();
				pl = next;
				next = left(next);	//Scorri lungo la sinistra;
			}
		t->value = root(next);
		if (right(next) != NULL)
			next = right(next);
		else
			next = emptyTree();

	}
	if (!empty(pl))			//Nel caso fosse un figlio sinistro:
		pl->left = next;
	if (!empty(pr))			//Nel caso fosse un figlio destro:
		pr->right = next;
	return l;
}
