#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    mkfifo("kolFIFO", 0600);
    
    char buf[10];
    int pdesk = open("kolFIFO", O_RDONLY);
    if (pdesk == -1)
    {
        perror("Error while opening a FIFO to read");
        exit(1);
    }
    if (read(pdesk, buf, 10) == -1)
    {
        perror("Error while reading from FIFO");
        exit(1);
    }
    printf("Read from FIFO: %s\n", buf);
}
