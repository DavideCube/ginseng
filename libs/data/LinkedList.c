#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "LinkedList.h"

//We add a node in the head position of the list beginning with start
void add(Node **start, char lab[], double val, Node *arr){
	
		Node *newNode;
		newNode = malloc(sizeof(Node));
	
		newNode->value = val;
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
void define(Node **start, char lab[], double val, Node *arr){
	
	Node *res = find( (*start), lab);
	
	if(  res != NULL){ // if exists, change it
		//printf("Found with value %f\n", res->value);
		res->value = val;
		res->array = arr;
	 }else
		add(start, lab, val, arr); //else add it*/
}



//support method to print entire list
void print_List(Node *start){
	
	while(start != NULL){
		printf("Current value: %f\n", start->value);
		start = start->next;
	}
}

Node* findArray(Node* start, char lab[]){

	Node *arr = NULL;
	while(start != NULL){
		if( strcmp(start->label, lab) == 0){
			arr = start->array;
			break;
		}
		start = start->next;
	}

	return arr;
}


void print_array(char lab[], Node *start){
	
	Node *arr = findArray(start, lab);

	
	if(arr == NULL){
		yyerror("Syntax error: array does not exist");
	} else{
		printf("[");
		int first = 1;
		while(arr != NULL){
			printf(first? "" : " , ");
			printf("%.2f", arr->value);
			arr = arr->next;
			first = 0;
		}
		printf("]\n");
	}	
}


double returnArrayItem(Node *start, char lab[], int index){
	
	Node *arr = findArray(start, lab);

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