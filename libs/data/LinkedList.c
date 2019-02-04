#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "LinkedList.h"

//We add a node in the head position of the list beginning with start
void add(Node **start, char lab[], double val, Node *arr, struct set_t* set){
	
		Node *newNode;
		newNode = malloc(sizeof(Node));
	
		newNode->value = val;
		newNode->array = arr;
		newNode->setType = set;
		strcpy(newNode->label,lab);
		newNode->next = (*start);
	
		(*start) = newNode;
	
}

void addIf(Node **start, char lab[], double val, double val2, Node *arr){
	
		Node *newNode;
		newNode = malloc(sizeof(Node));
	
		newNode->value = val;
		newNode->restore = val2;
		newNode->array = arr;
		strcpy(newNode->label,lab);
		newNode->next = (*start);
	
		(*start) = newNode;
	
}

Node* find(Node *start, char lab[]){
	
	while(start != NULL){
		if ( strcmp(start->label, lab ) == 0)
			return start;
		
		start = start->next;
	}
	
	return NULL;
}

//We would like to define a variable. If it is already present we modify it, 
//otherwise we add it
void define(Node **start, char lab[], double val, Node *arr, struct set_t* set){
	
	Node *res = find( (*start), lab);
	
	if(  res != NULL){ // if exists, change it
		//printf("Found with value %f\n", res->value);
		res->value = val;
		res->array = arr;
		res->setType = set;
		//printf("Adding set");
	 }else
		append(start, lab, val, arr, set); //else add it*/
}

//similar to add but addition is made at the end of the list
void append(Node **start, char lab[], double val, Node *arr, struct set_t* set){

	if((*start) == NULL){
		add(start, lab, val, arr, set);
		return;
	}

	Node *curr = (*start);

	while( curr->next !=  NULL){
		curr = curr->next;
	}

		Node *newNode;
		newNode = malloc(sizeof(Node));
	
		newNode->value = val;
		newNode->array = arr;
		newNode->setType = set;
		strcpy(newNode->label,lab);

		
		curr->next = newNode;


}

//support method to print entire list
void print_List(Node *start){
	
	while(start != NULL){
		printf("Current value: %.3f\n", start->value);
		start = start->next;
	}

	printf("\n");
}

//Return a reference (double pointer for new memory allocation) of the given array, if present,
//otherwise NULL
Node ** findReferenceToArray(Node **start, char lab[]){

	Node **arr = NULL;
	Node *list = (*start);
	while( list != NULL){
		
		if( strcmp(list->label, lab) == 0 && list->array != NULL){
			arr =  &(list->array);
			break;
		}
		list = list->next;
	}

	return arr;
}

//Print the whole array in the decided format
void print_array(char lab[], Node **start){ 
	
	Node **mod = findReferenceToArray(start, lab);
	Node *arr = (*mod);

	
	if(arr == NULL){
		yyerror("Syntax error: array does not exist");
	} else{
		printf("[");
		int first = 1;
		while(arr != NULL){
			printf(first? "" : " , ");
			printf("%.3f", arr->value);
			arr = arr->next;
			first = 0;
		}
		printf("]\n");
	}	
}

//Return the array item identified by the given index, if it does not exist throw an error
double returnArrayItem(Node **start, char lab[], int index){
	
	Node **mod = findReferenceToArray(start, lab);
	Node *arr = (*mod);

	if(arr == NULL){
		yyerror("Syntax error: array does not exist");
	} else{
		int current = 0;
		while(arr != NULL){

			if(current == index)
				return arr->value;

			arr = arr->next;
			current++;
		}

		yyerror("Syntax error: array index out of cup");

		return 0.0;
	}
}

//Set the array item identified by the given index. 
//if the index is greater than the length of the array, we initialize the element in between to 0
void setArrayItem(Node **start, char lab[], int index, double value){
	
	
	Node **mod = findReferenceToArray(start, lab);
	Node *arr = (*mod);

	if(arr == NULL){
		yyerror("Syntax error: array does not exist");
	} else{

		if(index < 0)
			yyerror("Syntax error: array index cannot be negative");

		int current = 0; 
		//If the index is already in use
		while(arr != NULL){

			if(current == index){
				arr->value = value;
				return;
			}
			arr = arr->next;
			current++;
		}
		
	//If it does not exist, let's initialize with 0.0 all the one 
	//in between and then set the desired one
	char tempLab[12];

	while(current < index){
		sprintf(tempLab, "%d", current); 
		append(mod, tempLab, 0.0, NULL, NULL);
		current++;
		
	}
	sprintf(tempLab, "%d", current);
	append(mod, tempLab, value, NULL, NULL);

	}
}

double arrayLength (Node **start, char lab[]){
	
	Node **mod = findReferenceToArray(start, lab);
	Node *arr = (*mod);

	int length = 0;
	while(arr != NULL){
		length++;
		arr = arr->next;
	}

	return (double)length;
}

void pop(Node **start){
	

	if( (*start) == NULL){
		yyerror("Cannot pop head element, list is empty");
		return;
	}

	Node *head = (*start);

	(*start) = ((*start)->next);

	free(head);
	//printf("Next start val: %f\n",(*start)->value); 
	
}
