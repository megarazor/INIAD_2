#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdint.h>

struct stack {
    int buf[128];
    int count;
};

struct stack stk;
pthread_mutex_t mtx;

void stack_init(struct stack* stk)
{
    stk->count = 0;
}

void stack_push(struct stack* stk, int val)
{
    pthread_mutex_lock(&mtx);
    stk->buf[stk->count++] = val;
    pthread_mutex_unlock(&mtx);
}

int stack_pop(struct stack* stk)
{
    pthread_mutex_lock(&mtx);
    if (stk->count <= 0) {
        goto ERROR;
    }
    stk->count--;
    pthread_mutex_unlock(&mtx);
    return stk->buf[stk->count];
    
ERROR:
    fprintf(stderr, "ERROR: stack is empty\n");
    pthread_mutex_unlock(&mtx);
    abort();
}

void *thread_entry(void *arg){
    int i;
    for (i= 0; i < (intptr_t)arg; i++){
        stack_push(&stk, i);
        printf("%d\n", stack_pop(&stk));
    }
    return NULL;
}

int main(int argc, char* argv[])
{
    stack_init(&stk);
    int err;
    err = pthread_mutex_init(&mtx, NULL);
    if (err != 0)
        goto ERROR;

    void* retval1, *retval2;
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, thread_entry, (void*)69);
    pthread_create(&tid2, NULL, thread_entry, (void*)69);
    pthread_join(tid1, &retval1);
    pthread_join(tid2, &retval2);
    
    printf("Thread returns: %p, %p\n", retval1, retval2);  
    
    return 0;
ERROR:
    fprintf(stderr, "ERROR\n");
    return -1;
}