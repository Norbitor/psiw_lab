#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    printf("Start\n");
    switch (fork())
    {
    case -1:
        perror("Child process creation error");
        break;
    case 0: /* proces potomny */
        execlp("ls", "ls", "-a", NULL);
        perror("Program execution error");
        exit(1);
    default: /* proces macierzysty */
        if (wait(NULL) == -1)
            perror("Error while waiting for child process to end");
    }
    printf("End\n");
}
