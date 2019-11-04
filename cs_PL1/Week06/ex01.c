#include<stdio.h>
#include<stdlib.h>

struct student{
        int id;
        char *name;
        struct student *next;
};

int main(void){
        struct student *list, *head, *final;

        list = malloc(sizeof(struct student));
        list->id = 3;
        list->name = "Jyouho";
        list->next = NULL;
        head = list;
        final = list;

        /*for (list= head; list!=NULL; list= list->next) {
            printf("id: %d, name: %s\n", list->id, list->name);
        }
        printf("\n"); */

        // Problem 1-1		
        list = malloc(sizeof(struct student));
        list->id = 1;
        list->name = "Toyo";
        list->next = head;
        head = list;

        /*for (list= head; list!=NULL; list= list->next) {
            printf("id: %d, name: %s\n", list->id, list->name);
        }
        printf("\n"); */
				
        // Problem 1-3
        list = malloc(sizeof(struct student));
        list->id = 4;
        list->name = "Renke";
        list->next = NULL;
        final->next= list;
        final= list;

        /*for (list= head; list!=NULL; list= list->next) {
            printf("id: %d, name: %s\n", list->id, list->name);
        }
        printf("\n"); */
				
        // Problem 1-4
        list = malloc(sizeof(struct student));
        list->id = 2;
        list->name = "INIAD";
        list->next= head->next;
        head->next= list;

        /*for (list= head; list!=NULL; list= list->next) {
            printf("id: %d, name: %s\n", list->id, list->name);
        }
        printf("\n"); */

        // Problem 1-5
        struct student *before_to_delete= head->next;
        struct student *to_delete= before_to_delete->next;
        before_to_delete->next= to_delete->next;
        free(to_delete);

        /*for (list= head; list!=NULL; list= list->next) {
            printf("id: %d, name: %s\n", list->id, list->name);
        }
        printf("\n"); */
				
        // Problem 1-2
        for (list= head; list!=NULL; list= list->next) {
            printf("id: %d, name: %s\n", list->id, list->name);
        }
        printf("\n");
}
