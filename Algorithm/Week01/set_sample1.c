/* set_sample1.c */

#include <stdio.h>

typedef struct node {
    int val;
    struct node *next;
} node;

node node15 = {757, NULL};
node node14 = {311, &node15};
node node13 = {242, &node14};
node node12 = {233, &node13};
node node11 = {912, &node12};
node node10 = {859, &node11};
node node9 = {408, &node10};
node node8 = {88, &node9};
node node7 = {822, &node8};
node node6 = {551, &node7};
node node5 = {645, &node6};
node node4 = {353, &node5};
node node3 = {477, &node4};
node node2 = {167, &node3};
node node1 = {96, &node2};

int member(node* list, int value) {
    if(list == NULL) {
        return 0;
    }
    if(list->val == value) {
        return 1;
    }
    return member(list->next, value);
}

int main(int argc, char* argv[]) {
    int value;
    printf("Input value:");
    scanf("%d", &value);

    if(member(&node1, value)) {
        printf("%d is in the set.\n", value);
    } else {
        printf("%d is not in the set.\n", value);
    }
    
    return 0;
}