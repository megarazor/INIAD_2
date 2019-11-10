#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

#define BBUF_SIZE 10

typedef struct bounded_buffer {
    char elements[BBUF_SIZE];
    int head;
    int tail;
} bbuf;

bbuf b;
pthread_mutex_t mtx;
pthread_cond_t not_empty;
pthread_cond_t not_full;

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
    pthread_mutex_lock(&mtx);
    while (b->head == b->tail){
        pthread_cond_wait(&not_empty, &mtx); // Wait until there's at least 1 element in the bbuf
        // printf("blip\n");
    }
    char res= b->elements[b->head];
    b->head= (b->head + 1) % BBUF_SIZE;
    pthread_cond_broadcast(&not_full); // Broadcast that the bbuf is not full, as 1 element was removed
    pthread_mutex_unlock(&mtx);
    return res;    
}

void bb_put(bbuf *b, char c){
    pthread_mutex_lock(&mtx);
    while ((b->head - b->tail - 1) % BBUF_SIZE == 0){ // Wait until there's empty space in the bbuf
        pthread_cond_wait(&not_full, &mtx);
    }
    b->elements[b->tail]= c;
    b->tail= (b->tail + 1) % BBUF_SIZE;
    pthread_cond_broadcast(&not_empty); // Broadcast that the bbuf is not empty, as 1 element was added
    pthread_mutex_unlock(&mtx);
}

void *thread_entry_get(void *arg){
    // printf("blip\n");
    int i;
    for (i= 0; i < (intptr_t)arg - 1; i++){
        printf("%c -> ", bb_get(&b));
    }
    printf("%c\n", bb_get(&b));
    return NULL;
}

void *thread_entry_put(void *arg){
    // printf("blip\n");
    int i;
    for (i= 0; i < (intptr_t)arg; i++){
        bb_put(&b, rand_char());
    }
    return NULL;
}

int main(){
    bb_init(&b);
    int err;
    err = pthread_mutex_init(&mtx, NULL);
    if (err != 0) goto ERROR;
    err = pthread_cond_init(&not_empty, NULL);
    if (err != 0) goto ERROR;
    err = pthread_cond_init(&not_full, NULL);
    if (err != 0) goto ERROR;

    void* retval1, *retval2;
    pthread_t tid1, tid2;
    err= pthread_create(&tid1, NULL, thread_entry_get, (void*)69);
    if (err != 0) goto ERROR;
    err= pthread_create(&tid2, NULL, thread_entry_put, (void*)69);
    if (err != 0) goto ERROR;
    pthread_join(tid1, &retval1);
    pthread_join(tid2, &retval2);
    
    printf("Thread GET returns: %p\nThread PUT returns: %p\n", retval1, retval2); 
    return 0;

ERROR:
    fprintf(stderr, "ERROR\n");
    return -1;
}