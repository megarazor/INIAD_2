#include <stdio.h>
#include <unistd.h>
#include "hardware.h"
#include "os.h"


typedef enum {
    NOTSTARTED, RUNNING, SLEEPING,
} task_status_t;

typedef struct {
    task_status_t status;

    /* Valid only when NOTSTARTED */
    void (*fn)();
    void *stack;

    /* Valid only when SLEEPING */
    context_t regs;
    uint64_t wakeup_time;
} TCB;


TCB tasks[10];
int task_count = 0;

TCB* current_tcb = NULL;


int add_task(void (*fn)(), char* stack)
{
    TCB *tcb;

    if (task_count > sizeof(tasks)/sizeof(tasks[0])) {
        return -1;
    }

    /* Initialize a TCB */
    tcb = &(tasks[task_count++]);

    tcb->status = NOTSTARTED;
    tcb->fn = fn;
    tcb->stack = stack;

    return 0;
}

int i= 0;

TCB* schedule() // First come first serve
{ 
    i= (i + 1) % task_count;
    if (tasks[i].status != RUNNING){
        return &tasks[i];
    }
    return NULL;

    /* // Runs but only TOYO and INIAD
    for (int i= 0; i < task_count; i++){
        if (tasks[i].status == NOTSTARTED || tasks[i].status == SLEEPING){
            // tasks[i].status= RUNNING;
            return &tasks[i];
        }
    } 
    return NULL; */

    /* // Remove implementation
    for (int i= 0; i < task_count; i++){
        if (tasks[i].status == NOTSTARTED || tasks[i].status == SLEEPING){
            TCB to_be_run= tasks[i];
            int j;
            for (j= i; j < task_count - 1; j++){
                tasks[j]= tasks[j + 1];
            }
            tasks[task_count - 1]= to_be_run;
            task_count--;
            return &tasks[task_count];
        }
    }
    // printf("REACH HERE\n");
    return NULL; */
}


void schedule_and_dispatch()
{
    TCB *tcb = NULL;
    task_status_t prev_status;
    
    while (tcb == NULL) {
        tcb = schedule();
        if (tcb == NULL) usleep(100);
    }
    
    current_tcb = tcb;
    prev_status = tcb->status;
    tcb->status = RUNNING;
    
    if (prev_status == NOTSTARTED) {
        set_stack_pointer(tcb->stack);
        tcb->fn();
    }
    else {
        restore_context(tcb->regs);
    }
}


int sleep_task(int milliseconds)
{
    TCB* tcb = current_tcb;
    tcb->status = SLEEPING;
    tcb->wakeup_time = current_time_milliseconds() + milliseconds;

    if (save_context(tcb->regs) == 0) {
        /* Returned directly */
        schedule_and_dispatch();
        return 0; /* not executed */
    }
    else {
        /* Returned from longjmp */
        return 0;
    }
}
