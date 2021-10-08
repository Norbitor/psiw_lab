#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int pid1, pid2, status;

    pid1 = fork();
    if (pid1 == 0)
    { // child process
        exit(7);
    }
    // parent process
    printf("I have a child with ID: %d\n", pid1);
    pid2 = wait(&status);
    printf("Process %d exit status: %x\n", pid2, status);
}
