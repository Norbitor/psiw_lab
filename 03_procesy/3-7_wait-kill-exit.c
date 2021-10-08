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
        sleep(10);
        exit(7);
    }
    // parent process
    printf("I have a child with ID: %d\n", pid1);
    kill(pid1, 9);
    pid2 = wait(&status);
    printf("Process %d end status: %x\n", pid2, status);
}
