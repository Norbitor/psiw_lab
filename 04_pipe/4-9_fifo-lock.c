#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <ctype.h>

#define MAX 512

int main(int argc, char *argv[])
{
    int pdesk;

    if (mkfifo("/tmp/fifo", 0600) == -1)
    {
        perror("Error while creating a FIFO");
        exit(1);
    }

    if (fork() == 0)
    { // child process
        close(1);
        open("/tmp/fifo", O_WRONLY);
        execvp("ls", argv);
        perror("Error executing ls");
        exit(1);
    }
    else
    { // parent process
        char buf[MAX];
        int lb, i;

        wait(0);
        pdesk = open("/tmp/fifo", O_RDONLY);
        while ((lb = read(pdesk, buf, MAX)) > 0)
        {
            for (i = 0; i < lb; i++)
                buf[i] = toupper(buf[i]);
            write(1, buf, lb);
        }
    }
}