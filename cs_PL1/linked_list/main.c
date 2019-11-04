#include "linked_list.h"

int main(void){
    num_t* list= NULL;
    num_t** pp= &list;
    FILE* fp1 = fopen("Week05/int.i", "r");
    FILE* fp2 = fopen("Week05/int.o", "w");
    printf("Node count (read): %ld\n", read_from_file(pp, fp1));
    printf("Node count (write): %ld\n", write_to_file(list, fp2));
    print_list(list);
    while (list!= NULL) {
        printf("Pop: %ld\n", pop_head(pp)->n);
        print_list(list);
    }
    printf("\n");
    fclose(fp1);
    fclose(fp2);
}
