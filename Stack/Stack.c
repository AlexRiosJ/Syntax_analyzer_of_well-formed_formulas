/*
 * Stack.c
 *
 *  Created on: 26/04/2017
 *      Author: is708932
 */

#include "Stack.h"
#include <stdlib.h>

struct strNode{
	Type data;
	struct strNode* prior;
};

typedef struct strNode* Node;

struct strStack{
	Node Top;
	UInt32 size;
};

Stack stack_create(){
	Stack st = (Stack)malloc(sizeof(struct strStack));
	st->Top = NULL;
	st->size = 0;

	return st;
}

void stack_push(Stack st, Type _data){
	Node n = (Node)malloc(sizeof(struct strNode));
	n->data = _data;
	n->prior = st->Top;
	st->Top = n;
	st->size ++;
}

Type stack_pop(Stack st){
	if(stack_isEmpty(st))
			return NULL;

	Node n = st->Top;
	Type d = n->data;
	st->Top = n->prior;
	free(n);
	st->size --;

	return d;
}

Type stack_pop2(Stack st){
	if(stack_isEmpty(st) || stack_size(st)==1) return NULL;
	Node n = st->Top->prior;
	Type d = n->data;
	st->Top->prior = n->prior;
	free(n);
	st->size--;
	return d;
}

//Type stack_pop2(Stack st){
//	if(stack_isEmpty(st) || st->Top->prior == NULL)
//		return NULL;
//
//	Node n = st->Top->prior;
//	Type d = n->data;
//	st->Top->prior = n->prior;
//	free(n);
//	st->size --;
//
//	return d;
//}

Type stack_top(Stack st){
	if(stack_isEmpty(st))
		return NULL;

	return st->Top->data;

		/*Node n = st->Top;
		if (n != NULL)
			return n->data;
		else
			return NULL;*/
}

Boolean stack_isEmpty(Stack st){
	return st->Top == NULL;
}

void stack_destroy(Stack st){
	if(!stack_isEmpty(st)){
		Node current = st->Top;
		Node _prior = current->prior;

		while(_prior != NULL){
			free(current);
			current = _prior;
			_prior = _prior->prior;
		}
		free(current);
	}
	free(st);
}

UInt32 stack_size(Stack st){
	return st->size;
}
