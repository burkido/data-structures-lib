#ifndef HELPER_H
#define HELPER_H

#include "linked_list.h"

/*  functions  */

LINKED_LIST_NODE until_idx(LINKED_LIST_NODE curr, int idx);
void integer_printer(FILE* fp, void* data);
void char_printer(FILE *fp, void *data);


#endif /*HELPER_H*/