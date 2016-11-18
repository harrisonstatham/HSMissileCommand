///////////////////////////////////////////////////////////////////////
// Doubly Linked List
//
// This file should contain you implementation of the doubly-linked
// list data structure as described in the project documentation.
//
// Some functions are provided for you - use these as guides for the
// implementation of the remaining functions.
//
// This code can be tested using the testbench module. See
// testbench.h in the source, and LL_testbench_documentation.pdf in
// the project documentation for more information.
//
// GEORGIA INSTITUTE OF TECHNOLOGY, FALL 2016
///////////////////////////////////////////////////////////////////////


#include <stdlib.h>
#include <stdio.h>
#include "doubly_linked_list.h"



/**
 * create_llnode
 *
 * Helper function that creates a node by allocating memory for it on the heap,
 * and initializing its previous and next pointers to NULL and its data pointer to the input
 * data pointer
 *
 * @param data A void pointer to data the user is adding to the doublely linked list.
 * @return A pointer to the linked list node
 */

static LLNode* create_llnode(void* data) {
    LLNode* newNode = (LLNode*)malloc(sizeof(LLNode));
    newNode->data = data;
    newNode->previous = NULL;
    newNode->next = NULL;
    return newNode;
}


/**
 * create_dlinkedlist
 *
 * Creates a doublely liked list by allocating memory for it on the heap. Initialize the size to zero,
 * as well as head, current, and tail pointer to NULL
 *
 * @return A pointer to an empty dlinkedlist
 */

DLinkedList* create_dlinkedlist(void) {
    
    DLinkedList* newList = (DLinkedList*)malloc(sizeof(DLinkedList));
    
    newList->head       = NULL;
    newList->tail       = NULL;
    newList->current    = NULL;
    newList->size       = 0;
    
    return newList;
}


/**
 * InsertHead
 *
 * Insert the data to the head of the doublely linked list. Update the current pointer of the list only
 * when it is originally NULL.
 *
 * @param dll A pointer to the doubly linked list
 * @param data A void pointer to data the user is adding to the doublely linked list.
 *
 */

void insertHead(DLinkedList* dll, void* data){
    
    LLNode* newNode = create_llnode(data);
    
    if(dll->head == NULL){
        
        dll->size++;
        
        dll->head       = newNode;
        dll->current    = newNode;
        dll->tail       = newNode;
        
    } else {
        
        dll->size++;
        
        newNode->next           = dll->head;
        (dll->head)->previous   = newNode;
        dll->head               = newNode;
        
    }
}


/**
 * insertTail
 *
 * Insert the data to the tail of the doublely linked list. Update the current pointer of the list only
 * when it is originally NULL
 *
 * @param dll A pointer to the doubly linked list
 * @param data A void pointer to data the user is adding to the doublely linked list.
 *
 */

void insertTail(DLinkedList* dll, void* data){
    
    LLNode *newNode = create_llnode(data);
    
    if(isnull(dll->tail)) {
        
        dll->size++;
        dll->head       = newNode;
        dll->tail       = newNode;
        dll->current    = newNode;
        
    } else {
        
        dll->size++;
        newNode->previous   = dll->tail;
        dll->tail->next     = newNode;
        dll->tail           = newNode;
    }
    
}


/**
 * insertAfter
 *
 * Insert the new data to the doublely linked list right after the current pointer
 *
 * @param dll       A pointer to the doubly linked list
 * @param newData   A void pointer to the new data that the user want to add after data
 * @return          1 if insert the new data successfully
 *                  0 if the current pointer is NULL
 */

int insertAfter(DLinkedList* dll, void* newData){
    
    if(isnull(dll->current)) return 0;
    
    LLNode *newNode = create_llnode(newData);
    
    // Update the newNode pointers first.
    newNode->next       = dll->current->next;
    newNode->previous   = dll->current;
    
    
    if(ptreq(dll->current, dll->tail)) {
        
        dll->tail = newNode;
        
    } else if(notnull(dll->current->next)) {
        
        // If it is then update the prev item.
        dll->current->next->previous = newNode;
    }
    
    // Update the current->next pointer.
    dll->current->next = newNode;
    
    // Increase the size.
    dll->size++;
    
    return 1;
}



/**
 * insertBefore
 *
 * Insert the new data to the doublely linked list right before the current pointer
 *
 * @param dll       A pointer to the doubly linked list
 * @param newData   A void pointer to the new data that the user want to add after data
 * @return          1 if insert the new data successfully
 *                  0 if the current pointer is NULL
 */

int insertBefore(DLinkedList* dll, void* newData){
    
    if(isnull(dll->current)) return 0;
    
    
    LLNode *newNode = create_llnode(newData);
    
    // Update newNode's pointers.
    newNode->next = dll->current;
    newNode->next = dll->current->previous;
    
    // Check to see if dll->current->prev is valid.
    
    if(ptreq(dll->current, dll->head)) {
    
        dll->head = newNode;
        
    } else if(notnull(dll->current->previous)) {
        
        dll->current->previous->next = newNode;
    }
    
    // Update the current->prev pointer.
    dll->current->previous = newNode;
    
    // Increase the size.
    dll->size++;
    
    return 1;
}


/**
 * deleteBackward
 *
 * Delete the node the current pointer is pointed at, and move the current pointer backwards.
 * Be aware that deleteBackward will cause a problem if the current pointer is pointing
 * at list head
 *
 * @param dll           A pointer to the doubly linked list
 * @param shouldFree    Flag. 1 indicates if data should be freed upon deletion of node.
 * @return              the data of the new current pointer and NULL if the current pointer is NULL
 */

void* deleteBackward(DLinkedList* dll, int shouldFree){
    
    if(isnull(dll->current)) return NULL;
    
    // Save a pointer to the current node. Now we can modify the dll however we want.
    LLNode *current = dll->current;
    
    
    // If the current element is the tail of the list, then we update the tail
    // pointer to be the previous element.
    if(ptreq(dll->current, dll->tail)) {
        
        dll->tail = dll->current->previous;
    }
    
    
    // If the current element is the head of the list, then we update the head
    // pointer to be the next element.
    
    if(ptreq(dll->current, dll->head)) {
        
        dll->head = dll->current->next;
    }
    
    
    // We are deleting the current node.
    // Therefor we want to update the previous node's pointers, and the next node's pointers
    // to "heal" the list.
    
    if(notnull(dll->current->next)) {
        dll->current->next->previous = dll->current->previous;
    }
    
    if(notnull(dll->current->previous)) {
        
        dll->current->previous->next = dll->current->next;
    }
    
    
    // Update the current pointer.
    dll->current = current->previous;
    
    
    // Should we free the data at the current pointer?
    if(shouldFree) {
        
        free(current->data);
    }
    
    // Free the node.
    free(current);
    
    dll->size--;
    
    // Fix the current node, and return the data .
    if(notnull(dll->current)) {
        
        //dll->current->next = NULL;
        
        return dll->current->data;
    }
    
    return NULL;
}


/**
 * deleteForward
 *
 * Delete the node the current pointer is pointed at, and move the current pointer forwards.
 * Be aware that deleteForward will cause problem if the current pointer is pointing
 * at list tail
 *
 * @param dll           A pointer to the doubly linked list
 * @param shouldFree    Flag. 1 indicates if data should be freed upon deletion of node.
 * @return              the data of the new current pointer and NULL if the current pointer is NULL
 */

void* deleteForward(DLinkedList* dll, int shouldFree){
    
    if(isnull(dll->current)) return NULL;
    
    // Grab a copy of the current & current->next pointer.
    
    LLNode *current = dll->current;
    
    
    // If the current element is the tail of the list, then we update the
    // tail pointer to be the previous pointer of the current element.
    
    if(ptreq(dll->current, dll->tail))  {
        
        dll->tail = dll->current->previous;
    }
    
    
    // If the current element is the head of the list, then we update the head
    // pointer to be the next node.
    
    if(ptreq(dll->current, dll->head)) {
        
        dll->head = dll->current->next;
    }
    
    
    // We are deleting the current node.
    // Therefor we want to update the previous node's pointers, and the next node's pointers
    // to "heal" the list.
    
    // Update the next node's pointers.
    
    if(notnull(dll->current->next)) {
        
        dll->current->next->previous = dll->current->previous;
    }
    
    // Update the previous node's pointers
    
    if(notnull(dll->current->previous)) {
        
        dll->current->previous->next = dll->current->next;
    }
    
    
    // Update the current pointer
    dll->current = current->next;
    
    
    // Check to see if we should free the data at the current node.
    if(shouldFree) {
        
        free(current->data);
    }
    
    free(current);
    
    // Reduce the size to reflect the change.
    dll->size--;
    
    
    if(notnull(dll->current)) {
    
        //dll->current->previous = NULL;
        
        return dll->current->data;
    }
    
    return NULL;
}


/**
 * destroyList
 *
 * Destroy the doublely linked list. Everything in the linked list including list structure,
 * nodes and data are all freed from the heap
 *
 * @param dll A pointer to the doubly linked list
 * @param shouldFree Flag. 1 indicates if data should be freed upon deletion of node.
 *
 */

void destroyList(DLinkedList* dll, int shouldFree){
    if(dll->head != NULL){
        getHead(dll);
        while(deleteForward(dll,shouldFree)){};
    }
    free(dll);
}


/**
 * getHead
 *
 * Return the data contained in the head of the doublely linked list, and set the list current pointer
 * to head
 *
 * @param dll A pointer to the doubly linked list
 * @return the head data or  NULL if head == NULL
 */

void* getHead(DLinkedList* dll){
    if(dll->head != NULL){
        dll->current = dll->head;
        return (dll->head)->data;
    }else{
        return NULL;
    }
}


/**
 * getTail
 *
 * Return the data contained in the tail of the doublely linked list, and set the current pointer
 * to tail
 *
 * @param dll   A pointer to the doubly linked list
 * @return      the tail data or  NULL if tail == NULL
 */

void* getTail(DLinkedList* dll){
    
    if(isnull(dll->tail)) return NULL;
    
    // Set the current pointer to the tail.
    dll->current = dll->tail;
    
    // Return the tail data.
    return dll->tail->data;
}


/**
 * getCurrent
 *
 * Return the data the current pointer is pointing at
 *
 * @param dll   A pointer to the doubly linked list
 * @return      the current data or NULL if current == NULL
 */

void* getCurrent(DLinkedList* dll){
    
    if(isnull(dll->current)) return NULL;
    
    return dll->current->data;
}


/**
 * getNext
 *
 * Return the next data the current pointer is pointing at, and move the current pointer to next node
 *
 * @param dll   A pointer to the doubly linked list
 * @return      the next data or NULL if current == NULL
 */

void* getNext(DLinkedList* dll){
    
    if(isnull(dll->current)) return NULL;
    
    // Check to see if next is valid.
    if(notnull(dll->current->next)) {
        
        dll->current = dll->current->next;
        
        return dll->current->data;
    }
    
    // If current->next is NULL then we write current NULL, and return NULL.
    dll->current = NULL;
    
    return NULL;
}


/**
 * getPrevious
 *
 * Return the previous data the current pointer is pointing at, and move the current pointer to
 * previous node
 *
 * @param dll   A pointer to the doubly linked list
 * @return      the previous data or NULL if current == NULL
 */

void* getPrevious(DLinkedList* dll){
    
    if(isnull(dll->current)) return NULL;
    
    // Check to see if the previous element is NULL, if not then we can grab the data.
    if(notnull(dll->current->previous)) {
        
        dll->current = dll->current->previous;
        
        return dll->current->data;
    }
    
    // If current->prev is NULL then we set the current pointer and return NULL.
    
    dll->current = NULL;
    
    return NULL;
}


/**
 * getSize
 *
 * Return the size of the doubly linked list
 *
 * @param dll A pointer to the doubly linked list
 * @return  the size
 */

int getSize(DLinkedList* dll){
    
    return dll->size;
}


/*====================================================================
 * Harrison Added
 *====================================================================*/

typedef int (*dlinkedlist_callback)(DLinkedList *, LLNode *node);



/**
 * walk_dlinkedlist
 *
 * Walk the linked list and apply some callback function to each node in the
 * linked list.
 *
 * @param   dll     A pointer (DLinkedList *) to the list.
 * @param   fn      A function pointer (dlinkedlist_callback) to execute on each node.
 *
 */

void walk_dlinkedlist(DLinkedList *dll, dlinkedlist_callback fn) {
    
    // Start at the head and walk the list.
    
    LLNode *current = dll->head; // Not to be confused with dll->current !!
    LLNode *temp;
    
    while(current) {
        
        // We dont know what the callback function might do to the current node,
        // so we should store the next value, so we can continue to walk the list, in
        // the event that the callback deallocates the node for example.
        temp = current->next;
        
        // Call the callback on each node in the list.
        // We dont specify what the callback can do at all. Its has full power over the linked list.
        //
        // Also note that the callback return value (int) is not used here - oh well.
        //
        fn(dll, current);
        
        // Continue walking.
        current = temp;
    }
    
}



/**
 * popHead_dlinkedlist
 *
 * @brief           Pop the head element off the front, and return the data.
 *
 * @param dll       A pointer (DLinkedList *) to the doubly linked list.
 *
 */

void *popHead_dlinkedlist(DLinkedList *dll) {
    
    if(notnull(dll->head)) {
        
        // Grab a copy of the pointer to the next element.
        LLNode *next = dll->head->next;
        
        // Save the data.
        void *data = dll->head->data;
        
        // Free the node.
        free(dll->head);
        
        // Update the head element.
        dll->head = next;
        
        // Update the size of the list.
        dll->size--;
        
        return data;
    }
    
    return NULL;
}


/**
 * popTail_dlinkedlist
 *
 * @brief           Pop the tail element off the back, and return the data.
 *
 * @param dll       A pointer (DLinkedList *) to the doubly linked list.
 *
 */

void *popTail_dlinkedlist(DLinkedList *dll) {
    
    if(notnull(dll->tail)) {
        
        LLNode *prev    = dll->tail->previous;
        void *data      = dll->tail->data;
        
        // Free the node.
        free(dll->tail);
        
        // Set the new tail.
        dll->tail = prev;
        
        // Update the size of the list.
        dll->size--;
        
        return data;
    }
    
    return NULL;
}






/**
 * print_dlinkedlist_internal
 *
 * @brief           An internal functions specifically for printing out a linked list.
 *
 * @param dll       A pointer (DLinkedList *) to the doubly linked list
 * @param node      A pointer (LLNode *) to the node to print.
 *
 */

int print_dlinkedlist_internal(DLinkedList *dll, LLNode *node) {
    
    
    // Where are we printing to?
    // If we are running on the computer we can just printf.
    // If we are running on the MBED then we need to print to a serial port.
    
    if(HARRISON_CODE_ON_MBED) {
        
        // Print to serial port here.
        
    } else {
        
        // I have very mixed feelings about this code...
        // Its nice and "compact" but does it suffer from lack of readibility?
        // Decisions, decisions...
        
        const char *status =  isHeadCurrentTail_dlinkedlist(dll, node)    ? "Head, Current, Tail" :
                        isCurrentTail_dlinkedlist(dll, node)        ? "Current, Tail"       :
                        isHeadCurrent_dlinkedlist(dll, node)        ? "Head, Current"       :
                        isCurrent_dlinkedlist(dll, node)            ? "Current"             :
                        isHead_dlinkedlist(dll, node)               ? "Head"                :
                        isTail_dlinkedlist(dll, node)               ? "Tail"                : "";
        
        
        printf("LLNode {\n");
        printf("\t address  = %p <-- %s\n", node, status);
        printf("\t data     = %s \n", (char *) node->data);
        printf("\t previous = %p \n", node->previous);
        printf("\t next     = %p \n", node->next);
        printf("}; \n\n");
    
    }
        
    return 0;
}




/**
 * print_dlinkedlist
 *
 * @brief           Print out the linked list.
 *
 * @param dll       A pointer to the doubly linked list
 *
 */

void print_dlinkedlist(DLinkedList *dll) {
    
    // We can walk the list, and print each element.
    
    
    // If we are on the MBED then we want to print to the serial port.
    // If we are on the desktop then we can safely printf without worrying.
    
    if(HARRISON_CODE_ON_MBED) {
        
        // do some serial stuff here.
        
    } else {
    
        printf("DLinkedList {\n");
        printf("\t address  = %p \n", dll);
        printf("\t size     = %d \n", dll->size);
        printf("\t head     = %p \n", dll->head);
        printf("\t current  = %p \n", dll->current);
        printf("\t tail     = %p \n", dll->tail);
        printf("-----------------------------\n\n");
    
    }
    
    if(dll->size == 0) {
        
        if(HARRISON_CODE_ON_MBED) {
        
            // Print to serial port.
            
        } else {
            
            printf("Empty list. \n\n");
        }
        
    } else {
    
        // Walk the list and print.
        walk_dlinkedlist(dll, print_dlinkedlist_internal);
    }
    
    if(HARRISON_CODE_ON_MBED) {
        
        // print to serial port.
        
    } else {
        
        printf("}; \n\n");
    }
}




