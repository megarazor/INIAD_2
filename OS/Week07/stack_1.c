#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

struct stack {
    int buf[128];
    int count;
};

struct stack stk;

void stack_init(struct stack* stk)
{
    stk->count = 0;
}

void stack_push(struct stack* stk, int val)
{
    stk->buf[stk->count++] = val;
}

int stack_pop(struct stack* stk)
{
    if (stk->count <= 0) {
        fprintf(stderr, "ERROR: stack is empty\n");
        abort();
    }

    return stk->buf[--stk->count];
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

    void* retval1, *retval2;
    pthread_t tid1, tid2;
    int err;
    err= pthread_create(&tid1, NULL, thread_entry, (void*)69);
    if (err != 0)
        goto ERROR;
    err= pthread_create(&tid2, NULL, thread_entry, (void*)69);
    if (err != 0)
        goto ERROR;
    pthread_join(tid1, &retval1);
    pthread_join(tid2, &retval2);
    
    printf("Thread 1 returns: %p\nThread 2 returns: %p\n", retval1, retval2); 
    
    return 0;
ERROR:
    fprintf(stderr, "ERROR\n");
    return -1;
}