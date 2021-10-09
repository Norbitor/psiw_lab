#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int pdesk[2];

    if (pipe(pdesk) == -1)
    {
        perror("Creating a pipe");
        exit(1);
    }

    switch (fork())
    {
    case -1:
        perror("Error while creating a process");
        exit(1);
    case 0: // child process
        if (write(pdesk[1], "Hello!", 7) == -1)
        {
            perror("Error while writing to pipe");
            exit(1);
        }
        exit(0);
    default:
    { // parent process
        char buf[10];
        if (read(pdesk[0], buf, 10) == -1)
        {
            perror("Error while reading from pipe");
            exit(1);
        }
        printf("Read from pipe: %s\n", buf);
    }
    }
}
