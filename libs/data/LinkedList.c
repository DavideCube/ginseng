#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "LinkedList.h"

//We add a node in the head position of the list beginning with start
void add(Node **start, char lab[], double val){
	
		Node *newNode;
		newNode = malloc(sizeof(Node));
	
		newNode->value = val;
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
void define(Node **start, char lab[], double val){
	
	Node *res = find( (*start), lab);
	
	if(  res != NULL){ // if exists, change it
		printf("Found with value %f\n", res->value);
		res->value = val;
	 }else
		add(start, lab, val); //else add it*/
}



//support method to print entire list
void print_List(Node *start){
	
	while(start != NULL){
		printf("Current value: %f\n", start->value);
		start = start->next;
	}
}
