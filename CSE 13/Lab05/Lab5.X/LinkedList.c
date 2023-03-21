#include <stdio.h>
#include <stdlib.h>

#include "BOARD.h"
#include "LinkedList.h"

ListItem *LinkedListNew(char *data) {
    ListItem *li = calloc(1, sizeof(ListItem));
    if (li == NULL) {
        return NULL;
    }
    li -> previousItem = NULL;
    li -> data = data;
    li -> nextItem = NULL;
    return li;
}

ListItem *LinkedListCreateAfter(ListItem *item, char *data) {
    ListItem *new_node = calloc(1, sizeof(ListItem));
    if (new_node == NULL) {
        return NULL;
    }
    new_node -> previousItem = item;
    new_node -> data = data;
    new_node -> nextItem = NULL;
    
    if (item -> nextItem != NULL){
        new_node -> nextItem = item -> nextItem;
        item -> nextItem -> previousItem = new_node;
    }
   
    item -> nextItem = new_node;
    
    
    return new_node;
}

char *LinkedListRemove(ListItem *item) {
    if (item == NULL) {
        return NULL;
    }
    char *x = item -> data;
    
    if (item -> previousItem != NULL){
        item -> previousItem -> nextItem = item -> nextItem;
    }
    if (item -> nextItem != NULL){
        item -> nextItem -> previousItem = item -> previousItem;
    }
    free(item);
    item = NULL;
    return x;
}

int LinkedListSize(ListItem *list) {
    //i think this just counts the number of object in the list 
    //need to set to head then scroll to tail and count it all
    int size = 0;
    if (list == NULL) {
        return NULL;
    }
    while (list -> previousItem != NULL){
        list = list -> previousItem;
    }
    while (list != NULL){
        size += 1;
        list = list -> nextItem;
    }
    return size;
}

ListItem *LinkedListGetFirst(ListItem *list) {
    if (list == NULL) {
        return NULL;
    }
    while (list -> previousItem != NULL){
        list = list -> previousItem;
    }
    return list;
}

ListItem *LinkedListGetLast(ListItem *list) {
    if (list == NULL) {
        return NULL;
    }
    while (list -> nextItem != NULL){
        list = list -> nextItem;
    }
    return list;
}

int LinkedListSwapData(ListItem *firstItem, ListItem *secondItem) {
    //swaps two things so a b c could become c b a
    if (firstItem == NULL) {
        return STANDARD_ERROR;
    }
    if (secondItem == NULL) {
        return STANDARD_ERROR;
    }
    char *temp = firstItem -> data;
    firstItem -> data = secondItem -> data;
    secondItem -> data = temp;
    
    return SUCCESS;
}

int LinkedListPrint(ListItem *list) {
    if (list == NULL) {
        return STANDARD_ERROR;
    }
    while (list -> previousItem != NULL){
        list = list -> previousItem;
    }
    printf("[");
    while (list != NULL){
        printf("%s, ", list->data);
        list = list -> nextItem;
    }
    printf("]");
    return SUCCESS;
}
