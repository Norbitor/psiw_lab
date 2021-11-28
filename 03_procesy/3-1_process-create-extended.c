#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    printf("Start pid=%d, ppid=%d\n", getpid(), getppid());
    if (fork() == 0)
    { // code executed by a child
        printf("Text from a child:  pid=%d, ppid=%d\n", getpid(), getppid());
    } else { // code executed by a parent
        printf("Text from a parent: pid=%d, ppid=%d\n", getpid(), getppid());
    }
    // mutual code
    printf("End pid=%d, ppid=%d\n", getpid(), getppid());
}
