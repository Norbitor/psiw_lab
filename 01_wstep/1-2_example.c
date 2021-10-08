#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int d;

    if (argc < 2)
    {
        return 1;
    }

    d = open(argv[1], O_RDONLY);
    if (d == -1)
    {
        perror("Error while opening a file");
        exit(1);
    }

    return 0;
}
