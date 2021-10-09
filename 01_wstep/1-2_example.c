#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int d;

    if (argc < 2)
    {
        return 10;
    }

    d = open(argv[1], O_RDONLY);
    if (d == -1)
    {
        perror("Error while opening a file");
        exit(1);
    }
    printf("Descriptor number %d\n", d);
    sleep(60); // check now under /proc/<proc num>/fd
    close(d);
    printf("Descriptor number %d\n", d);
    sleep(30); // check now under /proc/<proc num>/fd
    return 0;
}
