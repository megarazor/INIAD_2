/* purge.c */

#include <stdio.h>
#include <stdlib.h>
#include "array_list.h"

LIST reverse(LIST lst){
    if (lst == NULL)
        return lst;
    LIST res= list_construct();
    for (POSITION i= list_first(lst); i != list_last(lst); i= list_next(lst, i)){
        list_insert(res, list_first(res), list_retrieve(lst, i));
    }
    return res;
}

int main(int argc, char* argv[]) {
    LIST lst = list_construct();
    POSITION p = list_first(lst);

    for(int i = 0; i < 20; i++) {
        list_insert(lst, p, rand() % 10);
    }
    list_print(lst);
    LIST rved= reverse(lst);
    list_print(rved);

    return 0;
}
