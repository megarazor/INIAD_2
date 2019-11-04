#include <stdio.h>
#include "array_queue.h"

int main(int argc, char* argv[]) {
    QUEUE queue = queue_construct();

    for(;;) {
        char buf[256];
        char c;
        int value = 0;
        
        fgets(buf, 256, stdin);
        if(sscanf(buf, "%c %d", &c, &value) == 0) {
            continue;
        }
        switch(c) {
            case 'i':
                queue_enqueue(queue, value);
                printf("enqueue:%d\n", value);
                break;
            case 'd':
                value = queue_dequeue(queue);
                printf("dequeue:%d\n", value);
                break;
            case 'r':
                value = queue_front(queue);
                printf("front:%d\n", value);
                break;
            case 'f':
                queue_pushfront(queue, value);
                printf("pushfront:%d\n", value);
                break;
            case 'b':
                value = queue_popback(queue);
                printf("popback:%d\n", value);
                break;
        }

        queue_print(queue);
        printf("Front: %d\n", queue->front);
        printf("Rear: %d\n\n", queue->rear);
    }
}
