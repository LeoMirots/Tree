/*	Libreria per gestire alberi binari di dati, gli elementi dell'albero possono
	essere qualsiasi tipo di dato, degli interi, dei double o delle struct,
	è sufficiente definirli e modificare la definizione di elemento nella
	libreria "el.h".
*/

#if !defined TREE_H	
#define TREE_H

#include "list.h"

extern tree Root(tree t);												/*Se il nodo puntato da t ha un "root" non nullo, Ritorna quello, ovvero il puntatore al nodo radice dell'albero, invece se t è un albero vuoto o non ha un "root" valido ritorna un puntatore al nodo stesso;*/
extern size_t height(tree t);											/*Ritorna l'altezza del ramo + lungo dell'albero*/
extern element headTree(tree t);										/*Ritorna il valore dell'elemento contenuto nel nodo puntato da t;*/
extern tree left(tree t);												/*Ritorna il ramo sinistro dell'albero;*/
extern tree right(tree t);												/*Ritorna l'albero destro dell'albero;*/
extern tree ConsTree(element e, tree left, tree right, tree root);		/*Ritorna un albero avente come radice un nodo contenente l'elemento e, left come ramo sinistro, right come ramo destro, e root come root;*/
extern tree emptyTree(void);											/*Restituisce un albero vuoto;*/
extern bool Empty(tree t);												/*Ritorna true se l'albero è vuoto, false altrimenti;*/

extern bool detectTree(element e, tree t);				/*Ritorna true se l'elemento è presente nell'albero, false altrimenti;*/
extern bool detectOrdTree(element e, tree t);			/*Ottimizzato per gli alberi BST, ritorna true se l'elemento è presente nell'albero, false altrimenti;*/
extern tree InsBinOrdTree(element e, tree t);			/*Inserisce ordinatamente l'elemento "e" nell'albero "t", mantenendolo un albero BST;*/
extern void SetRootTree(tree t, node *NewRoot);			/*Imposta tutti i campi "root" dell'albero t passato come parametro con il puntatore a nodo "NewRoot";*/
extern tree copyTree(tree t);							/*Ritorna un albero che è la copia dell'albero t passato come parametro;*/
extern bool Destroy(node *p);							/*Elimina il nodo puntato da p, liberando la memoria allocata dall'elemento e dalla struct dell'albero;*/
extern tree moveUp(tree t, tree Root);					/*Ritorno il nodo padre di t, Root è la radice dell'albero contenente t (Root(t));*/
extern tree succ(tree t);								/*Ritorna un puntatore al nodo + a sinistra del sottoalbero di destra di t;*/
extern tree Search_and_Destroy(element e, tree t);		/*Trova ed elimina l'elemento e nell'albero t e ritorna la radice del nuovo albero;*/
extern void DeleteAllTree(tree t);						/*Dato un puntatore a un nodo passato come parametro, risale alla radice dell'albero(il root) e cancella tutto l'albero liberando la memoria allocata;*/
extern node *searchBinTree(element e, tree t);			/*Cerca nell'albero t e nei suoi sottoalberi l'elemento e, se lo trova ritorna un puntatore al nodo cercato, altrimenti ritorna NULL. Se sono presenti 2 elementi con lo stesso valore cercato ritorna quello più a sinistra;*/

/*----------Funzioni di visita dell'albero:-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

extern void preOrder(tree t);				/*Visita e stampa gli elementi partendo dalla radice, esplorando completamente la parte sinista e infine la parte destra dell'albero; */
extern void inOrder(tree t);				/*Visita e Stampa gli elementi dell'albero dall'estremità a sinistra, si visitano i sottoalberi a destra e si risale fino alla radice, poi si esplora la parte destra dell'albero;*/
extern void postOrder(tree t);				/*Visita e stampa gli elementi partendo ultimo livello, esplorando tutti i fratelli, e reiterando poi il procedimento per tutti i livelli precedenti, fino alla radice;*/

/*----------Element2--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

extern tree2 Root2(tree2 t);												/*Se il nodo puntato da t ha un "root" non nullo, Ritorna quello, ovvero il puntatore al nodo radice dell'albero, invece se t è un albero vuoto o non ha un "root" valido ritorna un puntatore al nodo stesso;*/
extern size_t height2(tree2 t);											/*Ritorna l'altezza del ramo + lungo dell'albero*/
extern element2 headTree2(tree2 t);										/*Ritorna il valore dell'elemento contenuto nel nodo puntato da t;*/
extern tree2 left2(tree2 t);												/*Ritorna il ramo sinistro dell'albero;*/
extern tree2 right2(tree2 t);												/*Ritorna l'albero destro dell'albero;*/
extern tree2 ConsTree2(element2 e, tree2 left, tree2 right, tree2 root);		/*Ritorna un albero avente come radice un nodo contenente l'elemento e, left come ramo sinistro, right come ramo destro, e root come root;*/
extern tree2 emptyTree2(void);											/*Restituisce un albero vuoto;*/
extern bool Empty2(tree2 t);												/*Ritorna true se l'albero è vuoto, false altrimenti;*/

extern bool detectTree2(element2 e, tree2 t);				/*Ritorna true se l'elemento è presente nell'albero, false altrimenti;*/
extern bool detectOrdTree2(element2 e, tree2 t);			/*Ottimizzato per gli alberi BST, ritorna true se l'elemento è presente nell'albero, false altrimenti;*/
extern tree2 InsBinOrdTree2(element2 e, tree2 t);			/*Inserisce ordinatamente l'elemento "e" nell'albero "t", mantenendolo un albero BST;*/
extern void SetRootTree2(tree2 t, node2 *NewRoot);			/*Imposta tutti i campi "root" dell'albero t passato come parametro con il puntatore a nodo "NewRoot";*/
extern tree2 copyTree2(tree2 t);							/*Ritorna un albero che è la copia dell'albero t passato come parametro;*/
extern bool Destroy2(node2 *p);							/*Elimina il nodo puntato da p, liberando la memoria allocata dall'elemento e dalla struct dell'albero;*/
extern tree2 moveUp2(tree2 t, tree2 Root);					/*Ritorno il nodo padre di t, Root è la radice dell'albero contenente t (Root(t));*/
extern tree2 succ2(tree2 t);								/*Ritorna un puntatore al nodo + a sinistra del sottoalbero di destra di t;*/
extern tree2 Search_and_Destroy2(element2 e, tree2 t);		/*Trova ed elimina l'elemento e nell'albero t e ritorna la radice del nuovo albero;*/
extern void DeleteAllTree2(tree2 t);						/*Dato un puntatore a un nodo passato come parametro, risale alla radice dell'albero(il root) e cancella tutto l'albero liberando la memoria allocata;*/
extern node2 *searchBinTree2(element2 e, tree2 t);			/*Cerca nell'albero t e nei suoi sottoalberi l'elemento e, se lo trova ritorna un puntatore al nodo cercato, altrimenti ritorna NULL. Se sono presenti 2 elementi con lo stesso valore cercato ritorna quello più a sinistra;*/

/*----------Funzioni di visita dell'albero:-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

extern void preOrder2(tree2 t);				/*Visita e stampa gli elementi partendo dalla radice, esplorando completamente la parte sinista e infine la parte destra dell'albero; */
extern void inOrder2(tree2 t);				/*Visita e Stampa gli elementi dell'albero dall'estremità a sinistra, si visitano i sottoalberi a destra e si risale fino alla radice, poi si esplora la parte destra dell'albero;*/
extern void postOrder2(tree2 t);				/*Visita e stampa gli elementi partendo ultimo livello, esplorando tutti i fratelli, e reiterando poi il procedimento per tutti i livelli precedenti, fino alla radice;*/

#endif //TREE_H