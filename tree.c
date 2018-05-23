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
	if (empty(t)) abort();
	else return t->value;
}

tree left(tree t) {
	if (empty(t)) return NULL;
	else return t->left;
}

tree right(tree t) {
	if (empty(t)) return NULL;
	else return t->right;
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


bool memberTreeOrd(element e, tree t) {
	if (empty(t) == true)
		return false;
	if (cmp(e, root(t)) == true)
		return true;
	if (e < root(t))
		return memberTreeOrd(e, left(t));
	else return memberTreeOrd(e, right(t));
}



tree copy(tree t) {

	return consTree(root(t), emptyTree(), emptyTree());
}

int height(tree t) {
	if (t = emptyTree())
		return 0;
	else {
		int hl = height(left(t)), hr = height(right(t));
		if (hl > hr) return 1 + hl;
		else return 1 + hr;
	}
}

tree insBinOrdTree(element e, tree t) {
	tree l = t;
	if (empty(t))
		return consTree(e, emptyTree(), emptyTree());

	while (!empty(t)) {
		if (e <= root(t)) {
			if (empty(left(t))) {
				t->left = consTree(e, emptyTree(), emptyTree());
				t = left(t);
			}
			t = left(t);
		}
		else {
			if (empty(t->right)) {
				t->right = consTree(e, emptyTree(), emptyTree());
				t = right(t);
			}
			t = right(t);
		}
	}
	return l;
}


tree deleteElement(tree t, element e) {
	/*-"l" è puntatore alla root dell'albero originale; 
	  -"next" puntatore all'elemento successivo su cui scorrere;
	  -"pl" e "pr" i puntatori per memorizzare se la root in questione è
	  figlia sinistra o destra.*/
	tree l = t, next;
	tree pl = NULL, pr = NULL;

	//Cerco l'elemento:
	while (root(t) != e && !empty(t)) {
		if (e < root(t)) {
			pl = t; pr = emptyTree(); t = left(t);
		}
		else {
			pl = emptyTree(); pr = t; t = right(t);
		}
	}
	//printf("\ntrovato %d", root(t));

	if (!empty(t)) {
		
		// Il nodo da eliminare è una foglia:
		if (empty(left(t)) && empty(right(t))) {
			if (t == l)	// Se e' la root ritorno un albero vuoto;
				return emptyTree(); 
			next = emptyTree();
		}
		
		// Il nodo da eliminare ha un solo figlio
		if (empty(left(t)) && !empty(right(t))) {	//Se è quello destro:
			// Se e' la root ritorno il figlio
			if (t == l)
				return right(t);
			next = right(t);
		}
		if (!empty(left(t)) && empty(right(t))) {	//Se è quello sinistro:
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
