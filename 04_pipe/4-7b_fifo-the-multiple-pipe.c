#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    int pdesk;

    if (mkfifo("/tmp/fifo1", 0600) == -1)
    {
        perror("Error while creating a FIFO1");
        exit(1);
    }
    if (mkfifo("/tmp/fifo2", 0600) == -1)
    {
        perror("Error while creating a FIFO2");
        exit(1);
    }

    switch (fork())
    {
    case -1:
        perror("Error while creating a process");
        exit(1);
    case 0: // child process
        close(1);
        pdesk = open("/tmp/fifo1", O_WRONLY);
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
        execlp("ps", "ps", "-ef", NULL);
        perror("Error while executing ls");
        exit(1);
    default:
    { // parent process
        switch(fork())
        {
        case -1:
            perror("Error while creating a process");
            exit(1);
        case 0:
            close(0);
            pdesk = open("/tmp/fifo1", O_RDONLY);
            close(1);
            open("/tmp/fifo2", O_WRONLY);
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
            execlp("tr", "tr", "-s", " ", NULL);
            perror("Error while executing tr");
            exit(1);
        default:
            close(0);
            pdesk = open("/tmp/fifo2", O_RDONLY);
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
            execlp("cut", "cut", "-f2", "-d ", NULL);
            perror("Error while executing cut");
            exit(1);
        }
    }
    }
}
