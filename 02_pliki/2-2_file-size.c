#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int desc;
    long rozm;

    if (argc < 2)
    {
        fprintf(stderr, "Too less parameters. Use:\n");
        fprintf(stderr, "%s <file name>\n", argv[0]);
        exit(1);
    }

    desc = open(argv[1], O_RDONLY);
    if (desc == -1)
    {
        perror("File open error");
        exit(1);
    }

    rozm = lseek(desc, 0, SEEK_END);
    if (rozm == -1)
    {
        perror("Seek error");
        exit(1);
    }

    printf("File size %s: %ld bytes\n", argv[1], rozm);

    if (close(desc) == -1)
    {
        perror("File close error");
        exit(1);
    }

    exit(0);
}