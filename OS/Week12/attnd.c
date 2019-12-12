#include <stdio.h>
#include <string.h>
int main(int argc, char const* argv[])
{
    char buf[5];
    if (argc != 2) {
        printf("usage: %s <data>\n", argv[0]);
        return 1;
    }
    strncpy(buf, argv[1]);
    printf("%s\n", buf);
    return 0;
}