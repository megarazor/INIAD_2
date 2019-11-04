/* dlinked_list.c */

#include <stdlib.h>
#include <stdio.h>
#include "dlinked_list.h"

LIST list_construct() {
    dlinked_list* lst = malloc(sizeof(dlinked_list));
    list_node* node = malloc(sizeof(list_node));
    node->next = NULL;
    node->previous = NULL;
    lst->top = node;
    lst->tail = node;

    return lst;
}

void list_free(LIST lst) {
    list_node* node = lst->top;
    while(node != NULL) {
        list_node* next = node->next;
        free(node);
        node = next;
    }
    free(lst);
}

void list_print(LIST lst) {
    if((lst == NULL) || (lst->top == NULL) || (lst->top->next == NULL)) {
        return;
    }

    list_node* node = lst->top->next;
    while(node->next != NULL) {
        printf("%d -> ", node->value);
        node = node->next;
    }
    printf("%d\n", node->value);
}

void list_insert(LIST lst, POSITION pos, int value) {
    if((lst == NULL) || (pos == NULL)){
        return;
    }
    list_node* new_node = (list_node*)malloc(sizeof(list_node));
    new_node->value = value;
    
    new_node->next = pos->next;
    if(new_node->next != NULL) {
        new_node->next->previous = new_node;
    } else {
        lst->tail = new_node;
    }
    new_node->previous = pos;
    pos->next = new_node;
}

void list_delete(LIST lst, POSITION pos) {
    if((lst == NULL) || (pos == NULL)) {
        return;
    }

    list_node* next = pos->next;
    if(next == NULL) {
        return;
    }

    pos->next = next->next;
    if(pos->next != NULL) {
        pos->next->previous = pos;
    } else {
        lst->tail = pos;
    }
    free(next);
}

int list_retrieve(LIST lst, POSITION pos) {
    if((lst == NULL) || (pos == NULL) || (pos->next == NULL)) {
        return 0;
    }
    return pos->next->value;
}

POSITION list_first(LIST lst) {
    return lst->top;
}

POSITION list_last(LIST lst) {
    return lst->tail;
}

POSITION list_next(LIST lst, POSITION pos) {
    if((lst == NULL) || (pos == NULL)) {
        return NULL;
    }
    return pos->next;
}

POSITION list_previous(LIST lst, POSITION pos) {
    if((lst == NULL) || (pos == NULL)) {
        return NULL;
    }
    return pos->previous;
}

POSITION list_get(LIST lst, int n) {
    if((lst == NULL) || (lst->top == NULL)) {
        return NULL;
    }

    list_node* node = lst->top;
    for(int i = 0; i < n; i++) {
        if(node->next == NULL) {
            return NULL;
        }
        node = node->next;
    }
    return node;
}

POSITION list_index(LIST lst, int value) {
    if((lst == NULL) || (lst->top == NULL)) {
        return NULL;
    }
    POSITION second_last= lst->top;
    if (lst->top->next== NULL){
        return second_last;
    }
    if (lst->tail!= NULL) {
        if (lst->tail->previous!= NULL) {
            second_last= lst->tail->previous;
        }
    }
    POSITION pos= lst->top->next;
    while (pos!= NULL){
        if (pos->value== value){
            return pos;
        }
        pos= pos->next;
    }
    return second_last;
}

int list_real_index(LIST lst, POSITION pos){
    int index= 0;
    POSITION cur= lst->top->next;
    while (cur!= NULL){
        if (cur== pos){
            return index;
        }
        else{
            index++;
            cur= cur->next;
        }
    }
    return 0;
}
