#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    printf("pid = %d, ppid = %d\n", getpid(), getppid());
    if (fork() == 0)
    { // child process
        printf("pid = %d, ppid = %d\n", getpid(), getppid());
        sleep(15);
        printf("pid = %d, ppid = %d\n", getpid(), getppid());
        exit(EXIT_SUCCESS);
    }
    exit(EXIT_SUCCESS);
}
