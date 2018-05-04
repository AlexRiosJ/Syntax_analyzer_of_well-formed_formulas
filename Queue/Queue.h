/*
 * Queue.h
 *
 *  Created on: 26/04/2017
 *      Author: is708932
 */

#ifndef QUEUE_H_
#define QUEUE_H_


typedef enum {FALSE, TRUE} Bool;


typedef void* Type;
typedef struct strQueue* Queue;
typedef unsigned int UInt;

Queue queue_create();
void  queue_destroy(Queue);
Bool  queue_isEmpty(Queue);
void  queue_offer(Queue, Type);
Type  queue_peek(Queue);
Type  queue_poll(Queue);
UInt  queue_size(Queue);

#endif /* QUEUE_H_ */
