/*
	Biblioteca desenvolvida por Hélter Pinheiro para trabalho de E.D
	Lista simplesmente encadeada
	Data: 21/10/2018
*/

#ifndef LISTA_H_
#define LISTA_H_
#define TRUE 0
#define FALSE 1
/*
	estrutura correspondente ao nó da lista
*/
typedef struct _slnode_{
	struct _slnode_*next;
	void *data;
}Slnode;

/*
	Nós da lista
*/

typedef struct _sllist_{
	Slnode *first;
	Slnode *cur;
}Sllist;

#ifdef LISTA_C_
	Sllist* sllCreate(); // cria uma lista simplesmente encadeada
	void* sllFirst(Sllist *l); // retorna o primeiro da lista
	void* sllGetNext(Sllist *l); // prega o próximo nó da lista
	int sllDestroy(Sllist *l); // destroi a lisa (apenas quando não há nenhum nó sobrando)
	int sllInsertFirst(Sllist *l, void *data);// insere na primeira posição da lista
	void *sllRemoveSpec(Sllist *l, void* key, int (*comp)(void*,void*)); // remove determinado nó da lista
	void *sllQuery(Sllist *l, void *key, int(*comp)(void*,void*)); //procura determinado nó da lista
	int sllInsertAfterSpec(Sllist *l, void *key, int(*comp)(void*,void*), void*data);// insere na lista um nó depois do nó especificado
#else
	extern Sllist* sllCreate();
	extern void* sllFirst(Sllist *l);
	extern void* sllGetNext(Sllist *l);
	extern int sllDestroy(Sllist *l);
	extern int sllInsertFirst(Sllist *l, void *data);
	extern void *sllRemoveSpec(Sllist *l, void* key, int (*comp)(void*,void*));
	extern void *sllQuery(Sllist *l, void *key, int(*comp)(void*,void*));
	extern int sllInsertAfterSpec(Sllist *l, void *key, int(*comp)(void*,void*), void*data);
#endif //LISTA_C_

#endif //LISTA_H_
