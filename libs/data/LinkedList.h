typedef struct Node {
    double value; //value of the current node
    struct Node* array; 
    char label[20]; //Label of the current node
    //pointer to next element of the linked list
    struct Node* next;
} Node;

void add(Node **start, char lab[], double val, Node *arr);
void append(Node **start, char lab[], double val, Node *arr);
void print_List(Node *start);
Node* find(Node *start, char lab[]);
void define(Node **start, char lab[], double val, Node *arr);
void print_array(char lab[], Node **start);
double returnArrayItem(Node **start, char lab[], int index);
void setArrayItem(Node **start, char lab[], int index, double value);