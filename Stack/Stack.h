/*
 * Stack.h
 *
 *  Created on: 26/04/2017
 *      Author: is708932
 */

#ifndef STACK_H_
#define STACK_H_

typedef enum {False, True} Boolean;

typedef void* Type;
typedef struct strStack* Stack;
typedef unsigned int UInt32;

Stack stack_create();
void  stack_push(Stack, Type);
Type  stack_pop(Stack);
Type  stack_pop2(Stack);
Type  stack_top(Stack);
Boolean stack_isEmpty(Stack);
UInt32  stack_size(Stack);
void  stack_destroy(Stack);

#endif /* STACK_H_ */
