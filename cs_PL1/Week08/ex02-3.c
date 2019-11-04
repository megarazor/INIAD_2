#include <stdio.h>
#include <stdlib.h>

int my_add(int, int);
int my_sub(int, int);
int my_mul(int, int);
int my_div(int, int);

typedef int (*CalcFunc)(int, int);
typedef struct _OpEntry {
    char operator;
    CalcFunc func_ptr;
} OpEntry;

/* retrieves a function from the OpEntry array and returns a pointer of the function. */
CalcFunc search_func(OpEntry[], int, char);

int BUFSIZE = 10;

int main() {
    OpEntry operations[] = {
        { '+', my_add }, { '-', my_sub },
        { '*', my_mul }, { '/', my_div }
    };

    char buf[BUFSIZE];

    printf("\ninput operation: +,-,*,/ ");
    fread(buf, sizeof(char), 1, stdin);

    char operator  = buf[0];
    int val1 = 100;
    int val2 = 200;
    
    // please refer to this URL: https://www.jpcert.or.jp/sc-rules/c-arr01-c.html
    CalcFunc operation_func = search_func(operations, 
        sizeof(operations)/sizeof(operations[0]), operator); 

    if (operation_func == NULL) {
        printf("unknown operator");
    } else {
        printf("\n%d %c %d = %d \n", val1, operator, val2, operation_func(val1, val2));
    }
    return 0;
}

int my_add(int val1, int val2){
    return val1 + val2;
}
int my_sub(int val1, int val2){
    return val1 - val2;
}
int my_mul(int val1, int val2){
    return val1 * val2;
}
int my_div(int val1, int val2){
    return (val1 / val2);
}

CalcFunc search_func(OpEntry operations[], int operations_num, char operator) { 
    CalcFunc func_ptr = NULL;
    for (int i=0; i<operations_num; i++) {
        if (operations[i].operator == operator) {
            func_ptr= operations[i].func_ptr;
            break;
        }
    }
    return func_ptr;
}
