#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>


#define BUF_SIZE 8192

int main(int argc, char* argv[])
{
    FILE *src = NULL, *dst = NULL;
    char buf[BUF_SIZE];
    //int i;

    if (argc != 3) {
        fprintf(stderr, "Usage: filecopy <src> <dest>\n");
        return 1;
    }

    src = fopen(argv[1], "r");
    if (!src) goto error;
    
    dst = fopen(argv[2], "w");
    if (!dst) goto error;

    for (;;) {
        size_t cnt;

        cnt = fread(buf, 1, sizeof(buf), src);
        if (cnt <= 0) break;

        /* FIXME: should add error handling */
        fwrite(buf, 1, cnt, dst);
    }

    fclose(dst);
    fclose(src);
    return 0;

 error:
    if (dst) fclose(dst);
    if (src) fclose(src);
    fprintf(stderr, "ERROR\n");
    return 1;
}
