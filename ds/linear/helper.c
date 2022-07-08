#include <stdlib.h>
#include <stdio.h>
#include "helper.h"

LINKED_LIST_NODE until_idx(LINKED_LIST_NODE curr, int idx){

	int i;
	for(i = 0; i <= idx; i++){
		curr = curr->next;
	}

	return curr;
}

void integer_printer(FILE* fp, void *data) {

	fprintf(fp, "%d ", *(int*)data);
}

void char_printer(FILE *fp, void *data) {
	fprintf(fp,"%c ",*(char *)data);
}