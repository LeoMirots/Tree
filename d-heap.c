/*
L'heap è un particolare insieme, costituito da elementi che dispongono di una
proprietà (chiave) sulla quale è definita una relazione di ordinamento totale
(Code di priorità)

Una d-heap e’ un albero radicato d-ario che:
1. E’ quasi completo: completo almeno fino al penultimo livello
2. Ogni nodo v contiene un elemento e ed una chiave x(v) sul cui dominio e’ definita una relazione di ordinamento totale
3. Ogni nodo n diverso dalla radice ha la chiave non minore del padre x(v) >= x(parent(v))

Dato un d-heap con n nodi, l’albero ha altezza O(logd n)
• La radice dell’abero contiene sempre la chiave di valore minimo (o massimo), grazie alla proprietà 3 (ordinamento heap)
• Puo’ essere rappresentato con un vettore considerando in modo implicito la posizione

Dato il padre i, i figli sono: d*i – d + 2, ..., d*i + 1
dove d rappresenta il numero di rami per ogni nodo e i rappresenta la posizione
dell'elemento di cui si stanno cercando i figli.
Se ho un albero con d = 3, e voglio sapere i figli del nodo in posizione 2,
questi si troveranno: 3*2 - 3 + 2, 3*2 - 3 + 3, 3*2 - 3 + 4 --> 3*2 - 1, 3*2, 3*2 + 1 --> 5, 6, 7;
*/
