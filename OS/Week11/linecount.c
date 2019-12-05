#include <sys/mman.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    int er, i, count, fd = -1;
    struct stat fileinfo;
    char* map = NULL;

    if (argc != 2) {
        fprintf(stderr, "Usage: linecount <file>\n");
        return 1;
    }
    
    fd = open(argv[1], O_RDONLY);
    if (fd < 0) goto error;

    er = fstat(fd, &fileinfo);
    if (er < 0) goto error;

    /* Map the whole file onto memory address
       (fileinfo->st_size contains the file size) */
    map = (char*)mmap(NULL, fileinfo.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (map == NULL) goto error;

    for (i = 0, count = 0; i < fileinfo.st_size - 1; i++) {
        if (map[i] == '\n') count++;
    }

    printf("line count: %d\n", count + 1);

    munmap(map, fileinfo.st_size);
    close(fd);
    
    return 0;

 error:
    if (map) munmap(map, fileinfo.st_size);
    if (fd >= 0) close(fd);
    fprintf(stderr, "ERROR\n");
    return 1;
}