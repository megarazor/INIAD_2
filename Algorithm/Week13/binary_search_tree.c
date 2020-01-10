/* binary_search_tree.c */

#include "binary_search_tree.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

treeset_node* set_construct_node(int value) {
    treeset_node* new_node = (treeset_node*)malloc(sizeof(treeset_node));
    new_node->value = value;
    new_node->height= 1;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void set_free_node(treeset_node* node) {
    if(node != NULL) {
        free(node->left);
        free(node->right);
        free(node);
    }
}

SET set_construct() {
    treeset* set = (treeset*)malloc(sizeof(treeset));
    set->root = NULL;
    return set;
}

void set_free(SET set) {
    set_free_node(set->root);
    free(set);
}

#define COUNT 10
void print2DUtil(treeset_node* root, int space) { 
    // Base case 
    if (root == NULL) 
        return; 
  
    // Increase distance between levels 
    space += COUNT; 
  
    // Process right child first 
    print2DUtil(root->right, space); 
  
    // Print current node after space 
    // count 
    printf("\n"); 
    for (int i = COUNT; i < space; i++) 
        printf(" "); 
    printf("%d\n", root->value); 
  
    // Process left child 
    print2DUtil(root->left, space); 
} 
  
void set_print2D(SET set){ 
   if (set == NULL) return;
   print2DUtil(set->root, 0);
} 

void rotate_right(treeset_node* node){
    treeset_node* left= node->left;
    treeset_node* left_right= left->right;
    left->right= node;
    node->left= left_right;
    if (node->left->height > node->right->height)
        node->height= node->left->height;
    else
        node->height= node->right->height;
    if (left->left->height > left->right->height)
        left->height= left->left->height;
    else
        left->height= left->right->height;
}

void rotate_left(treeset_node* node){
    treeset_node* right= node->right;
    treeset_node* right_left= right->left;
    right->left= node;
    node->right= right_left;
    if (node->left->height > node->right->height)
        node->height= node->left->height;
    else
        node->height= node->right->height;
    if (right->left->height > right->right->height)
        right->height= right->left->height;
    else
        right->height= right->right->height;
}

void self_balance(treeset_node* node, int inserted_value){
    // Update heights
    if (node->left->height > node->right->height)
        node->height= node->left->height + 1;
    else
        node->height= node->right->height + 1;
    
    int balance_factor= node->left->height - node->right->height;
    printf("Balance factor: %d\n", balance_factor);
    if (balance_factor > 1){
        if (inserted_value < node->left->value){
            // Left Left case
            printf("Rotating\n");
            rotate_right(node);
        }
        else{
            // Left Right case
            printf("Rotating\n");
            rotate_left(node->left);
            rotate_right(node);
        }
    }
    else if (balance_factor < -1){
        if (inserted_value > node->right->value){
            // Right Right case
            printf("Rotating\n");
            rotate_left(node);
        }
        else{
            // Right Left case
            printf("Rotating\n");
            rotate_right(node->right);
            rotate_left(node);
        }
    }
    printf("Don't need to rotate\n");
}

treeset_node* set_insert_node(treeset_node* node, int value) {
    if(node->value > value) {
        if(node->left == NULL) {
            node->left = set_construct_node(value);
            printf("Calling self-balance...\n");
            self_balance(node, value);
            return 1;
        } else {
            return set_insert_node(node->left, value);
        }
    } else if(node->value < value) {
        if(node->right == NULL) {
            node->right = set_construct_node(value);
            printf("Calling self-balance...\n");
            self_balance(node, value);
            return 1;
        } else {
            return set_insert_node(node->right, value);
        }
    } else {
        return 0;
    }
}

int set_insert(SET set, int value) {
    if(set->root == NULL) {
        set->root = set_construct_node(value);
        return 1;
    } 

    return set_insert_node(set->root, value);
}

int set_deletemin_node(treeset_node** node) {
    if((*node)->left != NULL) {
        int result = set_deletemin_node(&((*node)->left));
        return result;
    }

    int value = (*node)->value;
    if((*node)->right == NULL) {
        free(*node);
        *node = NULL;
    } else {
        treeset_node* tmp = *node;
        *node = (*node)->right;
        free(tmp);
    }

    return value;
}

int set_delete_node(treeset_node** node, int value) {
    if(*node == NULL) {
        return 0;
    }
    
    if((*node)->value > value) {
        int result = set_delete_node(&((*node)->left), value);
        return result;
    } else if((*node)->value < value) {
        int result = set_delete_node(&((*node)->right), value);
        return result;
    } else {
        if(((*node)->left == NULL) && ((*node)->right == NULL)) {
            free(*node);
            *node = NULL;
        } else if((*node)->left == NULL) {
            treeset_node* tmp = *node;
            *node = (*node)->right;
            free(tmp);
        } else if((*node)->right == NULL) {
            treeset_node* tmp = *node;
            *node = (*node)->left;
            free(tmp);
        } else {
            (*node)->value = set_deletemin_node(&((*node)->right));
        }

        return 1;
    }
}

int set_delete(SET set, int value) {
    return set_delete_node(&(set->root), value);
}

int set_member_node(treeset_node* node, int value) {
    if (node != NULL){
        if (value == node->value)
            return 1;
        else if (value < node->value)
            return set_member_node(node->left, value);
        else
            return set_member_node(node->right, value);
    }
    return 0;
}

int set_member(SET set, int value) {
    return set_member_node(set->root, value);
}

int set_min_node(treeset_node* node) {
    if (node != NULL){
        if (node->left != NULL)
            return set_min_node(node->left);
        else
            return node->value;
    }
    return 0;
}

int set_min(SET set) {
    if(set->root == NULL) {
        return 0;
    }
    return set_min_node(set->root);
}

int set_max_node(treeset_node* node) {
   if (node != NULL){
        if (node->right != NULL)
            return set_max_node(node->right);
        else
            return node->value;
    }
    return 0;
}

int set_max(SET set) {
    if(set->root == NULL) {
        return 0;
    }
    return set_max_node(set->root);
}

