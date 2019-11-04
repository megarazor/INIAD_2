#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student {
    char name[20];
    int score;
    struct student *next;
} student_t;

void print(student_t *list) {
    if (list==NULL){
        printf("The list is NULL.\n");
        return;
    }
    student_t *cur= list;
    while (1) {
        printf("%s: %d\n", cur->name, cur->score);
        cur= cur->next;
        if (cur==list) {
            printf("\n");
            return;
        }
    }
}

void append(student_t** list, char* name, int score) {
    student_t *new_std= malloc(sizeof(*new_std));
    strcpy(new_std->name, name);
    new_std->score= score;
    if (*list== NULL) {
        *list= new_std;
        new_std->next= new_std;
        return;
    }
    student_t *cur= *list;
    while (cur->next!=*list)
        cur= cur->next;
    cur->next= new_std;
    new_std->next= *list;
}

int data(student_t *list, char* name) {
    if (list== NULL){
        return -1;
    }
    student_t *cur= list;
    while (1) {
        if (strcmp(cur->name, name)==0) {
            return cur->score;
        }
        else {
            cur= cur->next;
            if (cur==list){
                return -1;
            }
        }
    }
    return -1;
}

student_t* search(student_t *list, char *name) {
    if (list==NULL){
        return NULL;
    }
    student_t *cur= list;
    while (1) {
        if (strcmp(cur->name, name)==0) {
            return cur;
        }
        else {
            cur= cur->next;
            if (cur==list){
                return NULL;
            }
        }
    }
    return NULL;
}

void delete(student_t** list, char* name) {
    if (list==NULL){
        return;
    }
    if ((*list)->next== *list) {
        if (strcmp((*list)->name, name)==0){
            free(*list);
            *list= NULL;
        }
        return;
    }
    student_t *cur= *list;
    while (1){
        if (strcmp(cur->next->name, name)==0) {
            student_t* to_delete= cur->next;
            if (to_delete==*list){
                cur->next= to_delete->next;
                free(to_delete);
                *list= cur->next;
                return;
            }
            cur->next= to_delete->next;
            free(to_delete);
            return;
        }
        else {
            cur= cur->next;
            if (cur==*list){
                return;
            }
        }
    }
}

int main() {
    student_t *list= NULL, *elm= NULL;
    student_t **p_list= &list;
    elm= malloc(sizeof(*elm));
    strcpy(elm->name, "INIAD");
    elm->next= NULL;
    elm->score= 90;
    list= elm;
    elm= NULL;

    elm= malloc(sizeof(*elm));
    strcpy(elm->name, "Toyo");
    elm->next= NULL;
    elm->score= 80;
    list->next= elm;
    elm= NULL;

    elm= malloc(sizeof(*elm));
    strcpy(elm->name, "Jyoho");
    elm->next= NULL;
    elm->score= 70;
    list->next->next= elm;
    elm= NULL;

    elm= malloc(sizeof(*elm));
    strcpy(elm->name, "Renke");
    elm->next= NULL;
    elm->score= 75;
    list->next->next->next= elm;
    elm->next= list;

    print(list);
    append(p_list, "Bruh", 45);
    print(list);
    printf("%s's score: %d\n", "Renke", data(list, "Renke"));
    printf("%s's score: %d\n", "Bruh", data(list, "Bruh"));
    printf("%s's score: %d\n", "INIAD", data(list, "INIAD"));
    printf("%s's score: %d\n\n", "Someone", data(list, "Someone"));

    student_t* sch1= search(list, "Bruh");
    printf("Search result: %s: %d\n", sch1->name, sch1->score);
    student_t* sch2= search(list, "INIAD");
    printf("Search result: %s: %d\n\n", sch2->name, sch2->score);
    // student_t* sch3= search(list, "Hit");
    //printf("Search result: %s: %d\n\n", sch3->name, sch3->score);
    
    delete(p_list, "INIAD"); 
    print(list);
    delete(p_list, "Renke");
    print(list);
    delete(p_list, "Bruh");
    print(list);
    delete(p_list, "Jyoho");
    print(list);
    delete(p_list, "Toyo");
    print(list); 
}
