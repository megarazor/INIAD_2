#include<stdio.h>

union tmp{
        short s;
        char c[2];
};
union crypt{
        int i;
        union tmp t[2];
};

int main(void){
        union crypt A, res;
        
        A.i= 1528104909;
        res.t[0].c[0]= A.t[1].c[0];
        res.t[0].c[1]= A.t[0].c[0];
        res.t[1].c[0]= A.t[1].c[1];
        res.t[1].c[1]= A.t[0].c[1];

        printf("%d\n", res.i);
}
