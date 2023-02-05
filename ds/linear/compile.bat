gcc -c linked-list/linked_list.c -o linked_list.o
ar rcs liblinked_list.a linked_list.o

gcc -c stack/stack.c -o stack.o
ar rcs libstack.a stack.o

gcc -c queue/queue.c -o queue.o
ar rcs libqueue.a queue.o

gcc -c helper/helper.c -o helper.o
ar rcs libhelper.a helper.o

gcc -c test.c -o test.o
gcc -o test.exe test.o -L. -llinked_list -lhelper