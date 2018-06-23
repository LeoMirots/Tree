/*	Libreria per gestire alberi di dati, gli elementi dell'albero possono
essere qualsiasi tipo di dato, degli interi, dei double o delle struct,
è sufficiente definirli e modificare la definizione di elemento nella
libreria "el.h".
*/

#if !defined TREE_H	
#define TREE_H

#include "list.h"

extern tree Root(tree t);				/*Se il nodo puntato da t ha un "root" non nullo, Ritorna quello, ovvero il puntatore al nodo radice dell'albero, invece se t è un albero vuoto o non ha un "root" valido ritorna un puntatore al nodo stesso;*/
extern size_t height(tree t);			/*Ritorna l'altezza del ramo + lungo dell'albero*/
extern element headTree(tree t);		/*Ritorna il valore dell'elemento contenuto nel nodo puntato da t;*/
extern tree left(tree t);				/*Ritorna il ramo sinistro dell'albero;*/
extern tree right(tree t);				/*Ritorna l'albero destro dell'albero;*/
extern tree ConsTree(element e, tree left, tree right, tree root);		/*Ritorna un albero avente come radice un nodo contenente l'elemento e, left come ramo sinistro, right come ramo destro, e root come root;*/
extern tree emptyTree(void);			/*Restituisce un albero vuoto;*/
extern bool Empty(tree t);				/*Ritorna true se l'albero è vuoto, false altrimenti;*/

extern bool detectTree(element e, tree t);				/*Ritorna true se l'elemento è presente nell'albero, false altrimenti;*/
extern bool detectOrdTree(element e, tree t);			/*Ottimizzato per gli alberi BST, ritorna true se l'elemento è presente nell'albero, false altrimenti;*/
extern tree InsBinOrdTree(element e, tree t);
extern void SetRootTree(tree t, node *NewRoot);			/*Imposta tutti i campi "root" dell'albero t passato come parametro con il puntatore a nodo "NewRoot";*/
extern tree copyTree(tree t);				/*Ritorna un albero che è la copia dell'albero t passato come parametro;*/
extern void DeleteAllTree(tree t);			/*Dato un puntatore a un nodo passato come parametro, risale alla radice dell'albero(il root) e cancella tutto l'albero liberando la memoria allocata;*/
extern node *searchBinTree(element e, tree t);		/*Cerca nell'albero t e nei suoi sottoalberi l'elemento e, se lo trova ritorna un puntatore al nodo cercato, altrimenti ritorna NULL. Se sono presenti 2 elementi con lo stesso valore cercato ritorna quello più a sinistra;*/

/*----------Funzioni di visita dell'albero:-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

extern void preOrder(tree t);				/*Visita e stampa gli elementi partendo dalla radice, esplorando completamente la parte sinista e infine la parte destra dell'albero; */
extern void inOrder(tree t);				/*Visita e Stampa gli elementi dell'albero dall'estremità a sinistra, si visitano i sottoalberi a destra e si risale fino alla radice, poi si esplora la parte destra dell'albero;*/
extern void postOrder(tree t);				/*Visita e stampa gli elementi partendo ultimo livello, esplorando tutti i fratelli, e reiterando poi il procedimento per tutti i livelli precedenti, fino alla radice;*/

#endif //TREE_H