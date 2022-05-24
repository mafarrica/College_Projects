#ifndef LISTS_H
#define LISTS_H



typedef struct Node{
    void *value;
    struct Node *next;
}Node;





void insertInList_end(Node *head, Node *item);

void deleteFromList(Node *before, Node *toDelete);




#endif