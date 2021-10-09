#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
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
    case 0: // child process
        close(1);
        pdesk = open("/tmp/fifo", O_WRONLY);
        if (pdesk == -1)
        {
            perror("Error while opening a FIFO to write");
            exit(1);
        }
        else if (pdesk != 1)
        {
            fprintf(stderr, "Wrong descriptor to write\n");
            exit(1);
        }
        execvp("ls", argv);
        perror("Error while executing ls");
        exit(1);
    default:
    { // parent process
        close(0);
        pdesk = open("/tmp/fifo", O_RDONLY);
        if (pdesk == -1)
        {
            perror("Error while opening a fifo to read");
            exit(1);
        }
        else if (pdesk != 0)
        {
            fprintf(stderr, "Wrong descriptor to read\n");
            exit(1);
        }
        execlp("tr", "tr", "a-z", "A-Z", NULL);
        perror("Error while executing tr");
        exit(1);
    }
    }
}
