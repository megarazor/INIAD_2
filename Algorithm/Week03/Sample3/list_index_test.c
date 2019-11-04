#include <stdio.h>
#include <stdlib.h>
#include "dlinked_list.h"

int main(int argc, char* argv[]) {
    LIST lst = list_construct();
    POSITION p = list_first(lst);
    int n= atoi(argv[1]);

    POSITION pos = first(lst);
insert(lst, pos, 1);
insert(lst, pos, 2);
insert(lst, pos, 3);
pos = next(lst, pos);
delete(lst, pos);
insert(lst, pos, 4);

    /*for(int i = 0; i < 10; i++) {
        list_insert(lst, p, rand() % 100);
    } 
    list_print(lst);
    
    // For linked list & doubly linked list testing.
    printf("list_index(%d): %p\n", n, list_index(lst, n));
    printf("Index: %d\n", list_real_index(lst, list_index(lst, n)));  
    //printf("lst: %p\n", lst);
    printf("lst->top: %p\n", lst->top);
    printf("lst->tail->previous: %p\n", lst->tail->previous);

    /*printf("list_index(%d): %d\n", n, list_index(lst, n)); // For array testing 
    */ 

    return 0;
}

