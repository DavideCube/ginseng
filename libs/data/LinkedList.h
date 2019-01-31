#include "set.h"

typedef struct Node {
    double value; //value of the current node
    struct Node* array; 
    char label[20]; //Label of the current node
    //pointer to next element of the linked list
    struct set_t* setType;
    struct Node* next;
    
    double restore;

} Node;

void add(Node **start, char lab[], double val, Node *arr, struct set_t* set);
void addIf(Node **start, char lab[], double val, double val2, Node *arr);
void append(Node **start, char lab[], double val, Node *arr, struct set_t* set);
void print_List(Node *start);
Node* find(Node *start, char lab[]);
void define(Node **start, char lab[], double val, Node *arr, struct set_t* set);
void print_array(char lab[], Node **start);
double returnArrayItem(Node **start, char lab[], int index);
void setArrayItem(Node **start, char lab[], int index, double value);
double arrayLength (Node **start, char lab[]);
void pop(Node **start);