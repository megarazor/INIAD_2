#include <sys/mman.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF 1000

int main (int argc, char* argv[]){
    if ((argc != 4) && (argc != 2)){
        fprintf(stderr, "Usage: %s <num-of-lines> <file-name>\n", argv[0]);
        return -1;
    }
    char filename[BUF]= "";
    int n;
    if (argc == 4){
        if (strcmp(argv[1], "-n") != 0){
            fprintf(stderr, "Usage: %s <num-of-lines> <file-name>\n", argv[0]);
            return -1;
        }
        n= atoi(argv[2]);
        strcpy(filename, argv[3]);        
    }
    else{
        n= 3; // Default: 3 lines
        strcpy(filename, argv[1]);
    }

    int er, fd = -1;
    struct stat fileinfo;
    char* map = NULL;

    // File open    
    fd = open(filename, O_RDONLY);
    if (fd < 0) goto error;

    er = fstat(fd, &fileinfo);
    if (er < 0) goto error;

    /* Map the whole file onto memory address
       (fileinfo->st_size contains the file size) */
    map = (char*)mmap(NULL, fileinfo.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (map == NULL) goto error;
    
    
    char **lines= malloc(sizeof(sizeof(char)*BUF)*(n + 1));
    for (int i= 0; i < (n + 1); i++){
        lines[i]= malloc(sizeof(char)*BUF);
        lines[i][0]= '\0';
    }

    for (int i= 0; i < fileinfo.st_size - 1; i++){
        strncat(lines[n], &map[i], 1);
        if (map[i] == '\n'){           
            for (int i= 0; i < n; i++){
                strcpy(lines[i], lines[i + 1]);
            }
            lines[n][0]= '\0';
        }
    }

    for (int i= 0; i < n; i++){
        printf("%s", lines[i]);
    }
    munmap(map, fileinfo.st_size);
    close(fd);
    
    return 0;
error:
    if (map) munmap(map, fileinfo.st_size);
    if (fd >= 0) close(fd);
    fprintf(stderr, "ERROR\n");
    return -1;
}