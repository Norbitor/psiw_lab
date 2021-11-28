#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    printf("Start - nazywam sie %s\n", argv[0]);
    execlp("ls", "ls", "-a", NULL);
    printf("End\n");
}
