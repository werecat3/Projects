/* 
 * File:   LinkedListTest.c
 * Author: Jerret Schlosser
 *
 * Created on April 30, 2021, 3:11 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BOARD.h"
#include "LinkedList.h"


/*
 * 
 */
int main(void) {
    BOARD_Init();
    
    printf("The beginning of Jrschlos's test harness.\n");
    int counter = 0;
    int subcounter = 0;
    char *node = "apple"; //what is put in the list first
    char *cool = "tree"; //what is put in second
    char *test = "words"; //what is put in between the first two
    char *test_2 = "lamp"; //used to add another element after in order to 
                           //prove that the size function works correctly
    
    //this is testing that the list new works correctly
    ListItem *list = LinkedListNew(node);
    
    if (strcmp(list -> data, node) == 0){
        counter += 1;
    }
    if (list -> nextItem == NULL){
        counter += 1;
        printf("Testing LinkedListNew: passed (%d / 2)\n", counter);
    }
    counter = 0;
    //printf("%d \n", LinkedListSize(list));
    
    //testing that create after works correctly
    list = LinkedListCreateAfter(list, cool);
    if (strcmp(list -> data, cool) == 0){
        counter += 1;
    }
    
    //this tests putting it in between two items so it moves around to each side of the new
    //thing in order to see if the values are kept in the right order
    list = LinkedListGetFirst(list);
    list = LinkedListCreateAfter(list, test);
    if (strcmp(list -> data, test) == 0){
        subcounter += 1;
    }
    list = LinkedListGetFirst(list);
    if (strcmp(list -> data, node) == 0){
        subcounter += 1;
    }
    list = LinkedListGetLast(list);
    if (strcmp(list -> data, cool) == 0){
        subcounter += 1;
    }
    if (subcounter == 3) {
        counter += 1;
    }
    printf("Testing LinkedListCreateAfter: passed (%d / 2)\n", counter);
    counter = 0;
    
    
    //testing get first works 
    list = LinkedListGetFirst(list);
    if (strcmp(list -> data, node) == 0){
        counter += 1;
    }
    if (list -> previousItem == NULL){
        counter += 1;
    }
    printf("Testing LinkedListGetFirst: passed (%d / 2)\n", counter);
    counter = 0;
    
    //testing get last works
    list = LinkedListGetLast(list);
    if (strcmp(list -> data, cool) == 0){
        counter += 1;
    }
    if (list -> nextItem == NULL){
        counter += 1;
    }
    printf("Testing LinkedListGetLast: passed (%d / 2)\n", counter);
    counter = 0;
    
    int x = LinkedListSize(list);
    if (x == 3) {
        counter += 1;
    }
    list = LinkedListGetLast(list);
    list = LinkedListCreateAfter(list, test_2);
    int y = LinkedListSize(list);
    if (y == 4) {
        counter += 1;
    }
    printf("Testing LinkedListSize: passed (%d / 2)\n", counter);
    counter = 0;
    
    printf("\nTesting the ListPrint works correctly\n");
    printf("Printing out the entire list up to this point using ListPrint\n");
    printf("The list currently will be apple, words, tree, lamp\n");
            
    LinkedListPrint(list);
    
    printf("\n\nTesting the SwapDate works correctly\n");
    printf("Moving around the list items using ListSwapData\n");
    printf("The list should become apple, lamp, tree, words\n");
    ListItem *firstlist = list -> previousItem -> previousItem;
    LinkedListSwapData(firstlist, list);
    LinkedListPrint(list);
    
    
    printf("\n\nTesting the remove works correctly\n");
    printf("Removing the 2nd item from the list\n");
    printf("The list should become apple, tree, words\n");
    ListItem *removeList_1 = list -> previousItem -> previousItem;
    LinkedListRemove(removeList_1);
    LinkedListPrint(list);
    
    
    printf("\n\nTesting the remove works correctly again\n");
    printf("Removing the 2nd item from the list\n");
    printf("The list should become apple, tree, words\n");
    ListItem *removeList_2 = list -> previousItem;
    LinkedListRemove(removeList_2);
    LinkedListPrint(list);
    
    
    printf("\n");

    BOARD_End();
    while (1);
    return 0;
}

