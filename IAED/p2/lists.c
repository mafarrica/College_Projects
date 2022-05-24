#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lists.h"



void insertInList_end(Node *head, Node *item){
    Node *temp = head;

    while(temp->next != NULL){
        temp = temp->next;
    }

    temp->next = item;
    item->next = NULL;

}



void deleteFromList(Node *before, Node *toDelete){
    before->next = toDelete->next;
    toDelete->next = NULL;
}

