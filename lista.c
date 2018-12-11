#ifndef LISTA_C_
#define LISTA_C_

#include "lista.h"
#include <stdlib.h>
#include <stdio.h>

// cria a lista
Sllist* sllCreate()
{
	Sllist *l;
	l=(Sllist*)malloc(sizeof(Sllist));
	if(l!=NULL){
		l->first=NULL;
		l->cur=NULL; //current - percorrer a lista
		return l;
	}
	return NULL;
}
// a funcao retorna o primeiro elemento da lista
void* sllFirst(Sllist *l)
{
	if(l!=NULL){
		if(l->first!=NULL){
			l->cur=l->first;
			return l->cur->data;
		}
	}
	return NULL;
}
// funcao pega o proximo no e retorna o dado amarzenado no mesmo
void* sllGetNext(Sllist *l)
{
	Slnode *aux;
	if(l!=NULL){
		if(l->cur->next!=NULL){
			aux=l->cur;
			l->cur=aux->next;
			return l->cur->data;
		}
	}
	return NULL;
}
// funcao destroi a lista
int sllDestroy(Sllist *l)
{
	if(l->first == NULL){
		free(l);
		return TRUE;
	}
	return FALSE;
}
// insere um novo elemento na lista na primeira posicao
int sllInsertFirst(Sllist *l, void *data)
{
	Slnode *newnode;
	if(l!=NULL){
		newnode=(Slnode*)malloc(sizeof(Slnode));
		if(newnode!=NULL){
			newnode->data=data;
			newnode->next=l->first;
			l->first=newnode;
			return TRUE;
		}
	}
	return FALSE;
}

void *sllRemoveSpec(Sllist *l, void* key, int (*comp)(void*,void*))
{
	Slnode *cur, *prev;
	int stat;
    void *data;
	if(l!=NULL){
		if(l->first!=NULL){
			cur=l->first;
			prev=NULL;
			stat=comp(key,cur->data);
			while(stat!=TRUE && cur->next!=NULL){
				prev = cur;
				cur=cur->next;
				stat=comp(key,cur->data);
			}
			if(stat == TRUE){
				if(prev!=NULL){
					prev->next = cur->next;
				}else{
					l->first = cur->next;
				}
				data = cur->data;
				free(cur);
				return data;
			}
		}
	}
	return NULL;
}

void *sllQuery(Sllist *l, void *key, int(*comp)(void*,void*))
{
    Slnode *cur;
	int stat;
	if(l!=NULL){
		if(l->first!=NULL){
			cur=l->first;
			stat=comp(key,cur->data);
			while(stat!=TRUE && cur->next!=NULL){
				cur=cur->next;
				stat=comp(key,cur->data);
			}
			if(stat==TRUE){
				return cur->data;
			}
		}
	}
	return NULL;
}

int sllInsertAfterSpec(Sllist *l, void *key, int(*comp)(void*,void*), void*data)
{
        Slnode *cur, *newnode, *next;
        int stat;
        if(l!=NULL){
            if(l->first!=NULL){
                cur = l->first;
                next = cur->next;
                stat = comp(key,cur->data);
                while(stat!=TRUE && next!=NULL){
                    cur=cur->next;
                    next = cur->next;
                    stat = comp(key,cur->data);
                }
                if(stat==TRUE){
                    newnode = (Slnode*)malloc(sizeof(Slnode));
                    if(newnode!=NULL){
                        newnode->data=data;
                        newnode->next=next;
                        cur->next=newnode;
                        return TRUE;
                    }
                }
            }
        }
        return NULL;
}


#endif
