#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX 1

int main(int argc, char *argv[])
{
    char buf[MAX];
    int source_fd, target_fd;
    int read_bytes;

    if (argc < 3)
    {
        fprintf(stderr, "Too less parameters. Use:\n");
        fprintf(stderr, "%s <source file> <target file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    source_fd = open(argv[1], O_RDONLY);
    if (source_fd == -1)
    {
        perror("Source file open error");
        exit(EXIT_FAILURE);
    }

    target_fd = creat(argv[2], 0640);
    if (target_fd == -1)
    {
        perror("Target file open error");
        exit(EXIT_FAILURE);
    }

    lseek(source_fd, -1, SEEK_END);
    while ((read_bytes = read(source_fd, buf, MAX)) > 0)
    {
        
        if (write(target_fd, buf, read_bytes) == -1)
        {
            perror("Target file writing error");
            exit(EXIT_FAILURE);
        }
        int pos = lseek(source_fd, -2, SEEK_CUR);
        if (pos == -1)
        {
            break;
        }
    }
    if (read_bytes == -1)
    {
        perror("Source file read error");
        exit(EXIT_FAILURE);
    }

    if (close(source_fd) == -1 || close(target_fd) == -1)
    {
        perror("File close error");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
