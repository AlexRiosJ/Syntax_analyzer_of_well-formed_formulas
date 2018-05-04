/*
 * Main.c
 *
 *  Created on: 26/04/2017
 *      Author: is708932
 */

#include "Main.h"

#define BUFFER_LEN 100

int main(){
	Bool exitFlag = FALSE;				//Exit Flag
	do{
		system("cls");					//Clear screen for cmd
		setbuf(stdout, NULL);
		Bool wf = TRUE;					//WELL-FORMED FORMULA
		Bool syntaxErr = FALSE;
		printf("*** ANALIZADOR DE F\xE0RMULAS BIEN FORMADAS ***\n");
		printf("\nIntroduce una f\xA2rmula: ");
		char sFormula[BUFFER_LEN];
		gets(sFormula);					//gets() fails when only enter key
		pause();
		Queue q1 = stringToQueue(sFormula);
		if(q1 == NULL)
			syntaxErr = TRUE;

		//Create one queue to hold the array
		Stack A_Stack = stack_create();
		Stack B_Stack = stack_create();

		TreeNode temp = NULL, temp2 = NULL, temp3 = NULL, temp4 = NULL, root = NULL;
		Bool thereAreParenthesis = FALSE;
		Bool thereIsBinary 		 = FALSE;

		//HERE IT BEGINS
		while (((!queue_isEmpty(q1) || !stack_isEmpty(A_Stack)) && wf) && !syntaxErr){

			//PUSH MODE
			temp = (struct TreeNode*) queue_poll(q1);
			while (!queue_isEmpty(q1) && temp->type != CLOSE_PA){
				stack_push(A_Stack, temp);
				temp = (struct TreeNode*) queue_poll(q1);
			}
			if(!(temp == NULL))
				stack_push(A_Stack,temp);

			//POP MODE
			do{
				temp2 = (struct TreeNode*) stack_pop(A_Stack);
				if(temp2 != NULL){
					//All of this conditions are pushing the top data from A stack to the B stack
					//When is an atomic proposition by itself
					if(temp2->type == CLOSE_PA || temp2->isComplete == TRUE)
						stack_push(B_Stack, temp2);

					//When enter negation condition
					else if(temp2->type == UNARY){
						if(stack_isEmpty(B_Stack)) wf = FALSE;
						else{
							temp3 = (struct TreeNode*) stack_pop(B_Stack);
							if(temp3->isComplete){
								temp2->right = temp3;
								temp2->isComplete = TRUE;
								stack_push(B_Stack,temp2);
							}
							else wf = FALSE;
						}
					}

					//When evaluating a binary expression
					else if (temp2->type == BINARY){
						if(stack_isEmpty(B_Stack) || stack_isEmpty(A_Stack)) wf = FALSE;
						else{
							temp3 = (struct TreeNode*) stack_pop(B_Stack);
							temp4 = (struct TreeNode*) stack_pop(A_Stack);
							if(temp3->isComplete && temp4->isComplete){
								temp2->left  = temp4;
								temp2->right = temp3;
								temp2->isComplete = TRUE;
								stack_push(B_Stack,temp2);
								thereIsBinary = TRUE;
							}
							else wf = FALSE;
						}
					}

					//When evaluating the node the open parentheses
					else if(temp2->type == OPEN_PA){
						if(stack_isEmpty(B_Stack))
							wf = FALSE;
						else{
							temp3  = (struct TreeNode*) stack_pop(B_Stack);
							if(temp3->isComplete){
								if(stack_isEmpty(B_Stack))
									wf = FALSE;
								else{
									temp4 = (struct TreeNode*) stack_pop(B_Stack);
									if(temp4->type == CLOSE_PA){
										stack_push(A_Stack, temp3);
										thereAreParenthesis = TRUE;
									}else
										wf = FALSE;
								}
							}else
								wf = FALSE;
						}
					}
				}
				else{
					wf = FALSE;
				}
				if(stack_isEmpty(A_Stack))
					root = (struct TreeNode*) stack_pop(B_Stack);
			}while(!stack_isEmpty(B_Stack) && wf);
			if(!implcation(thereIsBinary, thereAreParenthesis))
				wf = FALSE;
			thereAreParenthesis = FALSE;
			thereIsBinary		= FALSE;
		}

		if(root != NULL){
			if(root->data == ')')
				wf = FALSE;
		}

		if(!wf){
			printf("\nSYNTAX ERROR - F\xE0RMULA MAL FORMADA\n");
			stack_destroy(A_Stack);
			stack_destroy(B_Stack);
			if(root != NULL)
				tree_destroy(root);
			queue_destroy(q1);
		} else if(syntaxErr){
			printf("\nSYNTAX ERROR - CARACTERES INV\xB5LIDOS\n");
			stack_destroy(A_Stack);
			stack_destroy(B_Stack);
		} else{
			printf("\n\n* F\xE0RMULA BIEN FORMADA *\n");
			printf("Notaci\xA2n polaca inversa: ");
			printPostfix(root);
			printf("\n");
			printf("\xB5rbol binario generado:\n");
			printTree(root, 2);
			stack_destroy(A_Stack);
			stack_destroy(B_Stack);
			tree_destroy(root);
			queue_destroy(q1);
		}
		exitFlag = outMenu();
		pause();
	} while(!exitFlag);
	return 0;
}

