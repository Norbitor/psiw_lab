#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    printf("Start pid=%d, ppid=%d\n", getpid(), getppid());
    if (fork() == 0)
    {
        printf("Text from a child:  pid=%d, ppid=%d\n", getpid(), getppid());
    } else {
        printf("Text from a parent: pid=%d, ppid=%d\n", getpid(), getppid());
    }
    printf("End\n");
}
