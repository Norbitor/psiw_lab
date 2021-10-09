#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#define MAX 512

int main(int argc, char *argv[])
{
    int pdesk[2];

    if (pipe(pdesk) == -1)
    {
        perror("Error while creating a pipe");
        exit(1);
    }

    switch (fork())
    {
    case -1:
        perror("Error while creating a process");
        exit(1);
    case 0: // child process
        dup2(pdesk[1], 1);
        execvp("ls", argv);
        perror("Error while executing ls");
        exit(1);
    default:
    { // parent process
        char buf[MAX];
        int lb, i;

        close(pdesk[1]);
        while ((lb = read(pdesk[0], buf, MAX)) > 0)
        {
            for (i = 0; i < lb; i++)
                buf[i] = toupper(buf[i]);
            if (write(1, buf, lb) == -1)
            {
                perror("Error while writing to stdout");
                exit(1);
            }
        }
        if (lb == -1)
        {
            perror("Error while reading from pipe");
            exit(1);
        }
    }
    }
}
