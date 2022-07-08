gcc -c linked_list.c -o linked_list.o
ar rcs liblinked_list.a linked_list.o

gcc -c helper.c -o helper.o
ar rcs libhelper.a helper.o

gcc -c test.c -o test.o
gcc -o test.exe test.o -L. -llinked_list -lhelper