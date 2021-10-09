#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    int pdesk;

    if (mkfifo("/tmp/fifo", 0600) == -1)
    {
        perror("Error while creating a FIFO");
        exit(1);
    }

    switch (fork())
    {
    case -1:
        perror("Error while creating a process");
        exit(1);
    case 0:
        pdesk = open("/tmp/fifo", O_WRONLY);
        if (pdesk == -1)
        {
            perror("Error while opening a FIFO to write");
            exit(1);
        }
        if (write(pdesk, "Hallo!", 7) == -1)
        {
            perror("Error while writing to FIFO");
            exit(1);
        }
        exit(0);
    default:
    {
        char buf[10];

        pdesk = open("/tmp/fifo", O_RDONLY);
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
    }
}
