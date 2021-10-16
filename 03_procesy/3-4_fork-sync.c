#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    printf("Start\n");
    if (fork() == 0)
    {
        execlp("ls", "ls", "-a", NULL);
        perror("Error while executing a program");
        exit(1);
    }
    puts("Waiting for a child to die...");
    int status;
    wait(&status);
    printf("End, child exit status is %d\n", WEXITSTATUS(status));
}
