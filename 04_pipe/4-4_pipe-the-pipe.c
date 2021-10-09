#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
        close(pdesk[1]);
        dup2(pdesk[0], 0);
        execlp("tr", "tr", "a-z", "A-Z", NULL);
        perror("Error while executing tr");
        exit(1);
    }
    }
}
