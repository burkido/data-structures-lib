#ifndef LINKED_LIST_H
#define LINKED_LIST_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct LINKED_LIST_NODE_s *LINKED_LIST_NODE;
typedef struct LINKED_LIST_NODE_s{
	LINKED_LIST_NODE next; /* Do not change the order */
	void *data;
} LINKED_LIST_NODE_t[1];

typedef struct LINKED_LIST_s *LINKED_LIST;
typedef struct LINKED_LIST_s{
  	LINKED_LIST_NODE head;
} LINKED_LIST_t[1], *LINKED_LIST;

typedef struct DATA_s{
	void *data;
} DATA_t[1], *DATA;


/*  functions  */

LINKED_LIST linked_list_init();
LINKED_LIST_NODE linked_node_init(void *data);
void linked_list_append(LINKED_LIST list, void *data);
void linked_list_prepend(LINKED_LIST list, void *data);
bool is_next_node_null(LINKED_LIST_NODE node);
void linked_list_free(LINKED_LIST list);
void linked_list_insert(LINKED_LIST list, void *data, int idx);
void linked_list_set(LINKED_LIST list,void *data, int idx);
void *linked_list_get(LINKED_LIST list, int idx);
void linked_list_fprint(LINKED_LIST list, FILE* fp, void(*print_type)(FILE*, void*));
int linked_list_size(LINKED_LIST list);
void *linked_list_remove(LINKED_LIST list, int idx);
void *linked_list_remove_all(LINKED_LIST list);
void linked_list_concatenate(LINKED_LIST list, LINKED_LIST list2);
DATA data_init(void *data);


#endif /*LINKED_LIST_H*/