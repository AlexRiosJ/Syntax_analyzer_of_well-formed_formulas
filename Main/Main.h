/*
 * Main.h
 *
 *  Created on: 27/04/2017
 *      Author: Cursos
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <Queue.h>
#include <Stack.h>

typedef enum {
	OPEN_PA,
	CLOSE_PA,
	ATOMIC,
	UNARY,
	BINARY
}NodeTreeType_t;

struct TreeNode{
	char  data;
	struct TreeNode *left, *right;
	NodeTreeType_t type;
	Bool isComplete;
};

//FUNC PROTOTYPES
typedef struct TreeNode* TreeNode;
TreeNode treeNode_create(char);
Queue stringToQueue(char*);
void printPostfix(TreeNode n);
void printTree(TreeNode, int);
void tree_destroy(TreeNode);
void pause();
Bool implcation(Bool, Bool);
Bool outMenu();

TreeNode treeNode_create(char data){		//To create a treeNode
	TreeNode n = (TreeNode) malloc(sizeof(struct TreeNode));
	n->isComplete = FALSE;
	if(data >= 'a' && data <= 'z'){
		n->data = data;
		n->type = ATOMIC;
		n->isComplete = TRUE;
	}else{
		switch(data){		//These are the characters that the node can receive
			case '\xAA':	n->data = data;	n->type = UNARY;	break;	//Hexadecimal for printing and scanning in cmd
			case '(':	n->data = data;	n->type = OPEN_PA;	break;
			case ')':	n->data = data;	n->type = CLOSE_PA;	break;
			case '\x26':	n->data = data;	n->type = BINARY;	break;	//Hexadecimal for printing and scanning in cmd
			case '\x7C':	n->data = data;	n->type = BINARY;	break;	//Hexadecimal for printing and scanning in cmd
			case '#':	n->data = data;	n->type = BINARY;	break;
			case '$':	n->data = data;	n->type = BINARY;	break;
			default :	return NULL;
		}
	}
	n->left  = NULL;
	n->right = NULL;
	return n;
}

Queue stringToQueue(char* string){			//To introduce the string into a Queue
	Queue q1 = queue_create();
	int i;
	for(i = 0; i < strlen(string); i++){
		if(string[i] == '-' && string[i+1] == '>'){ 	//To convert the expression '->' into a single char to facilitate its use
			i++;
			TreeNode n = treeNode_create('$');
				if(n != NULL){
					queue_offer(q1, n);
				} else{
					queue_destroy(q1);
					return NULL;
				}
		}
		else if(string[i] == '<' && string[i+1] == '-' && string[i+2] == '>'){	//To convert the expression '<->' into a single char
			i += 2;																//to facilitate its use
			TreeNode n = treeNode_create('#');
			if(n != NULL){
				queue_offer(q1, n);
			} else{
				queue_destroy(q1);
				return NULL;
			}
		}
		else if(string[i] != ' '){						//To ignore spaces of the string
			TreeNode n = treeNode_create(string[i]);
			if(n != NULL){
				queue_offer(q1, n);
			} else{
				queue_destroy(q1);
				return NULL;
			}
		}
	}
	return q1;
}

void printPostfix(TreeNode n) {							//To print the postfix notation
	if(n->left  != NULL) printPostfix(n->left);
	if(n->right != NULL) printPostfix(n->right);
	if(n->data == '#')
		printf("<->");
	else if(n->data == '$')
		printf("->");
	else
		printf("%c", n->data);
}

void printTree(TreeNode n, int spaces){					//To print the tree
	int i;
	for(i = 0; i < spaces; i++)
		printf(" ");
	if(n->data == '#'){
		puts("<->");
		spaces += 2;
	} else if(n->data == '$'){
		puts("->");
		spaces += 2;
	}else
		printf("%c\n", n->data);
	if(n->left  != NULL) printTree(n->left,  spaces + 2);
	if(n->right != NULL) printTree(n->right, spaces + 2);
}

void tree_destroy(TreeNode n){							//To destroy the tree
	if(n->left  != NULL) tree_destroy(n->left);
	if(n->right != NULL) tree_destroy(n->right);
	free(n);
}

void pause(){											//To do pauses in the .exe running
	printf("Presiona enter para continuar . . .");
	getchar();
}

Bool implcation(Bool a, Bool b){						//Logical implication function
	Bool implication;
	if(a == b)
		implication = TRUE;
	if(a == FALSE && b == TRUE)
		implication = b;
	else if(a == TRUE && b == FALSE)
		implication = b;
	return implication;
}

Bool outMenu(){											//Menu for out or introduce another formula
	int opc = 0;
	printf("\nIngresar otra f\xA2rmula\t(0)\n");
	printf("Salir\t\t\t(1)\n");
	printf("Opci\xA2n: ");
	scanf("%d", &opc);
	getchar();
	if(opc == FALSE || opc == TRUE)
		return opc;
	else{
		printf("\xADOpci\xA2n inv\xA0lida! Intenta de nuevo . . .\n");
		return outMenu();
	}
}

#endif /* MAIN_H_ */
