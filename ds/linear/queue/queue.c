/*
   * Description: This code is a simple implementation of a linked list queue. It is used to store data in a linked list format. 
   * It can be used to store any type of data, as the data is stored as a void pointer. 
   * The linked list nodes are stored in a queue-like fashion. 
   * The head of the queue is the first node, and the tail is the last node. 
   * The head is removed when the dequeue function is called. 
   * The tail is added to when the enqueue function is called. 
   * The queue can be initialized using the linked_queue_init() function.
   * The queue can be freed using the linked_queue_free() function.
   * The queue can be checked if it is empty using the linked_queue_is_empty() function.
   * The queue can be checked for its size using the linked_queue_size() function.
   * The queue can be added to using the linked_queue_enqueue() function.
   * The queue can be removed from using the linked_queue_dequeue() function.
   *
   * Function Names: 
   * linked_queue_init()
   * linked_queue_is_empty()
   * linked_queue_free()
   * linked_queue_size()
   * linked_queue_enqueue()
   * linked_queue_dequeue()
   *
   * Variable Names:
   * queue -> The queue that is being initialized, freed, checked if empty, checked for size, or manipulated.
   * data -> The data that is being stored in the queue.
   * new_node -> The new node that is being added to the queue.
   * old_node -> The old node that is being removed from the queue.
   * tmp_queue -> The temporary queue that is used to iterate through the queue, and check its size.
   * size -> The size of the queue.
   *
   * Other Information:
   * The queue can store any type of data.
   * The queue is stored in a linked list format.
   * The queue is stored in a queue-like format, where the head is the first node, and the tail is the last node.
   * The head is removed when the dequeue function is called.
   * The tail is added to when the enqueue function is called.
   * The queue can be initialized using the linked_queue_init() function.
   * The queue can be freed using the linked_queue_free() function.
   * The queue can be checked if it is empty using the linked_queue_is_empty() function.
   * The queue can be checked for its size using the linked_queue_size() function.
   * The queue can be added to using the linked_queue_enqueue() function.
   * The queue can be removed from using the linked_queue_dequeue() function.
*/

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* 
* This is a linked implementation of a queue data structure.
* The structure is a singly linked list with a head and a tail
*/
typedef struct linked_queue_node{
	void *data;
	struct linked_queue_node *next;
}LINKED_QUEUE_NODE_t, *LINKED_QUEUE_NODE;

typedef struct linked_queue{
	LINKED_QUEUE_NODE head;
	LINKED_QUEUE_NODE tail;
}LINKED_QUEUE_t, *LINKED_QUEUE;

/*
* This function initializes a queue and returns a pointer to it
*/
LINKED_QUEUE linked_queue_init(){
	// Allocate the memory for the new queue
	LINKED_QUEUE queue = malloc( 1 * sizeof(LINKED_QUEUE_t));
	// If the memory allocation failed, return NULL
	if(queue == NULL){
		printf("Error while initializing queue! File: queue.c @linked_queue init");
		return NULL;
	}
	// Initialize the head and tail to NULL
	queue->head = NULL;
	queue->tail = NULL;
	// Return the new queue
	return queue;
}

bool linked_queue_is_empty(LINKED_QUEUE queue){
    return queue->head == NULL;
}

void linked_queue_free(LINKED_QUEUE queue){
	free(queue);
}

int linked_queue_size(LINKED_QUEUE queue){
	
    int size = 0;
	
    LINKED_QUEUE_NODE tmp_queue = NULL;
	
    if(queue->head == NULL)
		return 0;

	tmp_queue = queue->head->next;

	while(tmp_queue != NULL) {
		size++;
		tmp_queue = tmp_queue->next;
	}

	return size + 1;
}

/*
* This function adds a new element to the end of the queue and sets the tail to point to this new element
*/
void linked_queue_enqueue(LINKED_QUEUE queue,void *data){
	
    LINKED_QUEUE_NODE new_node = malloc(1 * sizeof(LINKED_QUEUE_NODE_t));
	if(new_node == NULL){
		printf("Error while enqueueing queue! File: queue.c @linked_queue_enqueue");
		return;
	}

	new_node->data = data;
	new_node->next = NULL;
	
    if(linked_queue_is_empty(queue))
		queue->head = new_node;
	else
		queue->tail->next = new_node;
	
	queue->tail = new_node;
}

/*
* This function returns the data of the first element of the queue and sets the head to point to the next element
*/
void* linked_queue_dequeue(LINKED_QUEUE queue){
	
    void *data = NULL;
	
    LINKED_QUEUE_NODE old_node = queue->head;

	if(linked_queue_is_empty(queue))
		return data;
	
	data = queue->head->data;
	queue->head = queue->head->next;
	free(old_node);
    
	return data;
}

LINKED_QUEUE linked_queue_init(){
	// Allocate the memory for the new queue
	LINKED_QUEUE queue = malloc( 1 * sizeof(LINKED_QUEUE_t));
	// If the memory allocation failed, return NULL
	if(queue == NULL){
		printf("Error while initializing queue! File: queue.c @linked_queue init");
		return NULL;
	}
	// Initialize the head and tail to NULL
	queue->head = NULL;
	queue->tail = NULL;
	// Return the new queue
	return queue;
}

bool linked_queue_is_empty(LINKED_QUEUE queue){
    return queue->head == NULL;
}

void linked_queue_free(LINKED_QUEUE queue){
	
	free(queue);
}

int linked_queue_size(LINKED_QUEUE queue){
	
    int size = 0;
	
    LINKED_QUEUE_NODE tmp_queue = NULL;
	
    if(queue->head == NULL)
		return 0;

	tmp_queue = queue->head->next;

	while(tmp_queue != NULL) {
		size++;
		tmp_queue = tmp_queue->next;
	}

	return size + 1;
}

void linked_queue_enqueue(LINKED_QUEUE queue,void *data){
	
    LINKED_QUEUE_NODE new_node = malloc(1 * sizeof(LINKED_QUEUE_NODE_t));
	if(new_node == NULL){
		printf("Error while enqueueing queue! File: queue.c @linked_queue_enqueue");
		return;
	}

	new_node->data = data;
	new_node->next = NULL;
	
    if(linked_queue_is_empty(queue))
		queue->head = new_node;
	else
		queue->tail->next = new_node;
	
	queue->tail = new_node;
}

void* linked_queue_dequeue(LINKED_QUEUE queue){
	
    void *data = NULL;
	
    LINKED_QUEUE_NODE old_node = queue->head;

	if(linked_queue_is_empty(queue))
		return data;
	
	data = queue->head->data;
	queue->head = queue->head->next;
	free(old_node);
    
	return data;
}