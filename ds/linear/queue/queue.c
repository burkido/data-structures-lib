#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

LINKED_QUEUE linked_queue_init(){
	
    LINKED_QUEUE queue = malloc( 1 * sizeof(LINKED_QUEUE_t));
	if(queue == NULL){
		printf("Error while initializing queue! File: queue.c @linked_queue init");
		return;
	}

	queue->head = NULL;
	queue->tail = NULL;

	return queue;
}

bool linked_queue_is_empty(LINKED_QUEUE queue){
	
    if (queue->head == NULL)
        return true;
    else
        return false;
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
		printf("Error while enqueueing(? :d) queue! File: queue.c @linked_queue_enqueue");
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