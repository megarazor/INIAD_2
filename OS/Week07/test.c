#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

#define BBUF_SIZE 5

typedef struct bounded_buffer {
    char elements[BBUF_SIZE];
    int head;
    int tail;
} bbuf;

bbuf b;

char rand_char(){ // Generates a random lower/upper case alphabetic character
    int n= rand() % 26;
    int cap= rand() % 2;
    if (cap == 0){
        n+= 65; // upppercase
    }
    else{
        n+= 97; // lowercase
    }
    return n;
}

void bb_init(bbuf *b){
    b->head= 0;
    b->tail= 0;
}

char bb_get(bbuf *b){
    if (b->head == b->tail){
        printf("Empty!\n");
        return '\0';
    }
    char res= b->elements[b->head];
    b->head= (b->head + 1) % BBUF_SIZE;
    return res;    
}

void bb_put(bbuf *b, char c){
    if ((b->head - b->tail - 1) % BBUF_SIZE == 0){
        printf("Head: %d, Tail: %d -> Full!\n", b->head, b->tail);
        return;
    }
    b->elements[b->tail]= c;
    b->tail= (b->tail + 1) % BBUF_SIZE;
}

void bb_print(bbuf *b){
    if(b->head == b->tail) {
        printf("Empty!\n");
    }
    printf("Head: %d, Tail: %d\n", b->head, b->tail);
    for(int i = b->head; i != b->tail; i = (i + 1) % BBUF_SIZE) {
        if((i + 1 - b->tail) % BBUF_SIZE == 0) {
            printf("%d\n\n", b->elements[i]);
        } else {
            printf("%d -> ", b->elements[i]);
        }
    }    
}

int main(){
    bb_init(&b);
    bb_put(&b, rand_char());
    bb_print(&b);
    bb_put(&b, rand_char());
    bb_print(&b);
    bb_put(&b, rand_char());
    bb_print(&b);
    bb_put(&b, rand_char());
    bb_print(&b);
    bb_put(&b, rand_char());
    bb_print(&b);
    bb_put(&b, rand_char());
    bb_print(&b);

}