typedef struct Node {
    double value; //value of the current node
    char label[20]; //Label of the current node
    //pointer to next element of the linked list
    struct Node* next;
} Node;

void add(Node **start, char lab[], double val);
void print_List(Node *start);
Node* find(Node *start, char lab[]);
void define(Node **start, char lab[], double val);
