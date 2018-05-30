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

element root(tree t) 
{	
	return t->value;
}

tree left(tree t)
{
	if (empty(t) == true)
	 return NULL;
	return t->left;
}

tree right(tree t) 
{
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

void showEl(element e)		/*Relativa all'elemento;*/
{		
	printf("%d", e);
}

bool IsEqual(element a, element b)
{
	if (a == b)
		return true;
	return false;
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
	if (empty(t) == false) {
			inOrder(left(t));
		printf("\t");
		showEl(root(t));
			inOrder(right(t));
	}
}


void postOrder(tree t) {
	if (empty(t) == false) {
			postOrder(left(t));
			postOrder(right(t));
		printf("\t");
		showEl(root(t));
	}
}

//NOT-PRIMITIVE
bool detectTreeOrd(element e, tree t)
{
	if (empty(t) == true)
		return false;
	switch (cmp(e, root(t)))
	{
		case 0:
			return true;
		case -1:
			return detectTreeOrd(e, left(t));
		case 1:
			return detectTreeOrd(e, right(t));
	}
	return false; /*Qui non dovrebbe mai arrivare;*/
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
		else 
			if (empty(t->right) == true)
			{
				t->right = consTree(e, emptyTree(), emptyTree());
				t = right(t);
			}
			t = right(t);
	}
	return l;
}

bool detectTree(element e, tree t)
{
	if(empty(t) == true)
		return false;
	if(IsEqual(e, root(t)) == true)
		return true;
	if(detectTree(e, t->left) == true)
		return true;
	if(detectTree(e, t->right) == true)
		return true;
	return false;
}

tree search(element e, tree t)
{
	/*"pl" e "pr" i puntatori per memorizzare se la root in questione è
		figlia sinistra o destra.*/
	tree pl = NULL, pr = NULL;

	if(detectTree(e, t) == false)
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
		else
		{
			pl = emptyTree(); pr = t; t = right(t);
		}
	}
	return t;
}


tree search_and_destroy(element e, tree t)
{
	return NULL;
}

tree ConstInputAnticipato(void)
{
	element e;
	element stop = 0;

	printf("Inserisci valore: ");
	scanf("%i", &e);

	if (isEqual(e, stop))
		return emptytree();
	else
	{
		tree l, r;
		l = ConstInputAnticipato();
		r = ConstInputAnticipato();

		consttree(e, l, r);
	}
}

tree ConstVettAnticipato(int* vett, int* next) //IMPORTANTE: passare l'indirizzo di una variabile int next inizializzata a 0. La funzione legge l'albero da vettore preorder
{
	element e = vett[*next];
	element stop = 0;

	if (isEqual(e, stop))
	{
		return emptytree();
	}
	else
	{
		tree l, r;
		(*next)++;
		l = ConstVettAnticipato(vett, next);
		(*next)++;
		r = ConstVettAnticipato(vett, next);

		consttree(e, l, r);
	}
}
