#include "linked_list.h"
#include "helper.h"

void main() {

    LINKED_LIST list = linked_list_init();
    LINKED_LIST list2 = linked_list_init();
    DATA data1, data2, data3, data4, data5, data6, data7, data8;

    data1 = data_init((int*)2);
    data2 = data_init((int*)4);
    data3 = data_init((int*)6);
    data4 = data_init((int*)8);

    data5 = data_init((int*)1);
    data6 = data_init((int*)3);
    data7 = data_init((int*)5);
    data8 = data_init((int*)7);

    linked_list_append(list, data1);
    linked_list_append(list, data2);
    linked_list_append(list, data3);
    linked_list_append(list, data4);

    linked_list_append(list2, data5);
    linked_list_append(list2, data6);
    linked_list_append(list2, data7);
    linked_list_append(list2, data8);


    linked_list_fprint(list, stdout, integer_printer);
    linked_list_fprint(list2, stdout, integer_printer);

    linked_list_concatenate(list, list2);

    linked_list_fprint(list, stdout, integer_printer);
}