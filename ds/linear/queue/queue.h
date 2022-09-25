#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct LINKED_QUEUE_NODE_s *LINKED_QUEUE_NODE;
typedef  struct LINKED_QUEUE_NODE_s {
	LINKED_QUEUE_NODE next;
	void *data;
} LINKED_QUEUE_NODE_t[1];

typedef struct {
	LINKED_QUEUE_NODE head;
	LINKED_QUEUE_NODE tail;
} LINKED_QUEUE_t[1], *LINKED_QUEUE;

/* Function declerations */
LINKED_QUEUE linked_queue_init();
bool linked_queue_is_empty(LINKED_QUEUE queue);
int linked_queue_size(LINKED_QUEUE queue);
void* linked_queue_dequeue(LINKED_QUEUE queue);
void linked_queue_enqueue(LINKED_QUEUE queue,void *data);


#endif /* QUEUE_H_ */