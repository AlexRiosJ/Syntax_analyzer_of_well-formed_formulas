/*
 * Queue.c
 *
 *  Created on: 26/04/2017
 *      Author: is708932
 */

#include "Queue.h"
#include <stdlib.h>

struct strNode{
	Type data;
	struct strNode* next;
};

typedef struct strNode* Node;

struct strQueue{
	Node first, last;
	UInt size;
};

Queue queue_create(){
	Queue q = (Queue)malloc(sizeof(struct strQueue));
	q->size = 0;
	q->first = NULL;
	q->last = NULL;
	return q;
}

Bool queue_isEmpty(Queue q){
	if(q == NULL)
		return TRUE;
	return q->first == NULL;
}

UInt queue_size(Queue q){
	return q->size;
}

Type queue_peek(Queue q){
	if(queue_isEmpty(q)) return NULL;
	return q->first->data;
}

void queue_offer(Queue q, Type _data){
	Node n = (Node)malloc(sizeof(struct strNode));
	n->data = _data;
	n->next = NULL;
	if(queue_isEmpty(q)){
		q->first = n;
	}else{
		q->last->next = n;
	}
	q->last = n;
	q->size ++;
}

Type queue_poll(Queue q){
	if(queue_isEmpty(q))return NULL;
	Node n = q->first;
	Type d = n->data;
	q->first = n->next;
	free(n);
	q->size --;
	return d;

}

void queue_destroy(Queue q){
	if(!queue_isEmpty(q)){
		Node current = q->first;
		Node _nxt = current->next;
		while(_nxt != NULL){
			free(current);
			current = _nxt;
			_nxt = _nxt->next;
		}
		free(current);
	}
	free(q);
}
