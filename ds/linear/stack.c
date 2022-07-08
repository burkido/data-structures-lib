#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void *linked_stack_pop(LINKED_STACK stack) {

	LINKED_STACK_NODE node;
	void *val = NULL;

	if (stack->head != NULL) {
		node = stack->head;
		val = node->data;
		stack->head = node->next;
		free(node);
	} else {
		printf("Error! File: linked_stack.c @linked_stack_pop");
	}

	return val;
}

void linked_stack_push(LINKED_STACK stack, void *data) {
	
	LINKED_STACK_NODE new_node = malloc(sizeof(LINKED_STACK_NODE_t));

	 new_node->data = data;
	 new_node->next = stack->head;
	 stack->head = new_node;
}

void *linked_stack_top(LINKED_STACK stack) {

	void *r_node = NULL;

	if (stack->head != NULL)
		r_node = stack->head->data;

	return r_node;
}

int linked_stack_is_empty(LINKED_STACK stack) {
	
	int is_empty = 0;

	if (stack->head == NULL) {
        printf("Error! File: linked_stack.c @linked_stack_is_empty");
        is_empty = 1;
    }

	return is_empty;
}

LINKED_STACK linked_stack_init() {

	LINKED_STACK stack=malloc(sizeof(LINKED_STACK_t));
	stack->head = NULL;
	return stack;
}

void linked_stack_free(LINKED_STACK stack) {
	
	if (stack->head != NULL) {
		free(stack->head);
	}

	free(stack);
}

void clone(LINKED_STACK source, LINKED_STACK target) {

	LINKED_STACK_NODE node = (LINKED_STACK_NODE)source;

	int val;

    while((val = linked_stack_pop(source)))
        linked_stack_push(target, val);

    linked_stack_free(source);
}

void linked_stack_print(LINKED_STACK stack) {

	LINKED_STACK tmp = linked_stack_init();

	int val;
	while((val = linked_stack_pop(stack))) {
		printf("%d\n",val);
		linked_stack_push(tmp,val);
	}

    clone(tmp,stack);
}