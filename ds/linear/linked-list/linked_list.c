#include "linked_list.h"
#include "helper.h"


DATA data_init(void *data) {
	
    DATA new_data;

	new_data = malloc(sizeof(DATA_t));
	new_data->data = data;

	return new_data;
}

LINKED_LIST linked_list_init() {

    LINKED_LIST new_node;

    new_node = malloc(sizeof(LINKED_LIST_t));
    if (new_node != NULL) {
		new_node->head = NULL;
	} else {
		printf("Error! File: linked_list.c @linked_list_init");
	}

	return new_node;
}

LINKED_LIST_NODE linked_node_init(void *data) {

    LINKED_LIST_NODE new_node;

	new_node = malloc(sizeof(LINKED_LIST_NODE_t));
	new_node->data = data;
	new_node->next = NULL;

	return new_node;
}

bool is_next_node_null(LINKED_LIST_NODE node) {

    node != NULL ? false : true;
}

void linked_list_append(LINKED_LIST list, void *data) {

    LINKED_LIST_NODE node, new_node;

    new_node = linked_node_init(data);
    node = (LINKED_LIST_NODE)list;
    while (node->next != NULL) {
        node = node->next;
    }

    node->next = new_node;
}

void linked_list_free(LINKED_LIST list) {


}

void linked_list_prepend(LINKED_LIST list, void *data) {

    LINKED_LIST_NODE new_list;
	new_list = linked_node_init(data);

	new_list->next = list->head;
	list->head = new_list;
}

void linked_list_insert(LINKED_LIST list, void* data, int idx) {

    int i;
    LINKED_LIST_NODE new_list, curr, after;

	new_list = linked_node_init(data);
	curr = (LINKED_LIST_NODE)list;

	for (i = 0; i < idx; i++) {
		curr = curr->next;
	}

	after = curr->next;
	new_list->next = after;
	curr->next = new_list;
}

void linked_list_set(LINKED_LIST list, void *data, int idx) {

	if(idx > linked_list_size(list)) {
		printf("Error! File: linked_list.c @linked_list_set Error is: Index out of bound! Given index is %d but max value is %d", idx, linked_list_size(list));
		return;
	}

    int i;
	idx++;
	LINKED_LIST_NODE curr;

	curr = (LINKED_LIST_NODE)list;
	for (i = 0; i < idx; i++) {
		curr = curr->next;
	}
	curr->data = data;
}

void *linked_list_get(LINKED_LIST list, int idx) {

	LINKED_LIST_NODE curr;
	curr = (LINKED_LIST_NODE)list;

	while (curr->next != NULL) {
		curr = curr->next;
	}

	return curr->data;
}

int linked_list_size(LINKED_LIST list) {
	
    LINKED_LIST_NODE node = list->head;
	int size = 0;
	
    while(node != NULL){
		node = node->next;
		size++;
	}
    
	return size;
}

void linked_list_fprint(LINKED_LIST list, FILE* fp, void(*print_type)(FILE *, void *))
{
	LINKED_LIST_NODE node;
	int i, size;

	node = list->head;
	size = linked_list_size(list);
	printf("Linked List: ");

	for (i = 0; i < size; i++)
	{
		print_type(fp, node->data);
		node = node->next;
	}
	printf("\n");
}

void *linked_list_remove(LINKED_LIST list, int idx) {

	int i;
	LINKED_LIST_NODE node, tmp, data;
	
	node = (LINKED_LIST_NODE)list;
	
	for (i = 0; i < idx; i++) {
		node = node->next;
	}

	tmp = node->next;
	data = node;
	node->next = tmp->next;
	free(tmp);

	return data;
}

void *linked_list_remove_all(LINKED_LIST list) {

	int i, size;

	size = linked_list_size(list);
	for (i = 0; i < size; i++) {
		linked_list_remove(list, 0);
	}
}

void linked_list_concatenate(LINKED_LIST first_list, LINKED_LIST second_list){

	LINKED_LIST_NODE first_node, second_node;

	first_node = (LINKED_LIST_NODE)first_list;
	second_node = (LINKED_LIST_NODE)second_list->head;

	while (first_node->next != NULL) {
		first_node = first_node->next;
	}

	first_node->next = second_node;
}