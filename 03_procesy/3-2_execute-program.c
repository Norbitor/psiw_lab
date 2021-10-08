#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    printf("Start\n");
    execlp("ls", "ls", "-a", NULL);
    printf("End\n");
}
