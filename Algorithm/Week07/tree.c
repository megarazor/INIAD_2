/* tree.c */

#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

Node* tree_construct(T value, Node** nodes, int length) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->parent = NULL;
    node->right_sibling = NULL;
    if((nodes != NULL) && (length > 0)) {
        node->leftmost_child = nodes[0];
        nodes[0]->parent = node;
        for(int i = 1; i < length; i++) {
            nodes[i - 1]->right_sibling = nodes[i];
            nodes[i]->parent = node;
        }
    } else {
        node->leftmost_child = NULL;
    }
    return node;
}

void tree_free(Node* tree) {
    if(tree->leftmost_child != NULL) {
        tree_free(tree->leftmost_child);
    }
    if(tree->right_sibling != NULL) {
        tree_free(tree->right_sibling);
    }
    free(tree);
}

int tree_depth(Node* node) {
    int depth = 0;
    while(node->parent != NULL) {
        node = node->parent;
        depth++;
    }
    return depth;
}

int tree_height(Node* node) {
    if (node == NULL)
        return -1;
    int tallest_height= tree_height(node->leftmost_child);
    if (node->leftmost_child != NULL){
        Node *cur= node->leftmost_child->right_sibling;
        while(cur != NULL){
            int cur_height= tree_height(cur);
            if (cur_height > tallest_height)
                tallest_height = cur_height;
            cur = cur->right_sibling;
        } 
    }
    return (tallest_height + 1);
}

void tree_preorder(Node* tree, Visitfn f) {
    f(tree->value);

    Node* node = tree->leftmost_child;
    while(node != NULL) {
        tree_preorder(node, f);
        node = node->right_sibling;
    }
}

void tree_inorder(Node* tree, Visitfn f) {
    Node* node = tree->leftmost_child;
    if(node != NULL) {
        tree_inorder(node, f);
    }

    f(tree->value);

    if(node != NULL) {
        node = node->right_sibling;
        while(node != NULL) {
            tree_inorder(node, f);
            node = node->right_sibling;
        }
    }
}

void tree_postorder(Node* tree, Visitfn f) {
    Node* node = tree->leftmost_child;
    while(node != NULL) {
        tree_postorder(node, f);
        node = node->right_sibling;
    }

    f(tree->value);
}