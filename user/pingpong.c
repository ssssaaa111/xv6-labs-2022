#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define MSGSIZE 4

int main(void)
{
    char inbuf[10];
    int pid;
    int p1[2], p2[2];
    pipe(p1);
    pipe(p2);

    pid = fork();
    if (pid < 0)
    {
        printf("init: fork failed\n");
        exit(1);
    }
    if (pid == 0)
    {
        close(p1[0]);
        close(p2[1]);
        read(p2[0], inbuf, MSGSIZE);
        printf("%d: received %s\n", getpid(), inbuf);
        write(p1[1], "pong", MSGSIZE);
        close(p1[1]);
    }
    // must add  this else, or it will excute two times.......
    else 
    {
        close(p1[1]);
        close(p2[0]);
        write(p2[1], "ping", MSGSIZE);
        close(p2[1]);
        read(p1[0], inbuf, MSGSIZE);
        printf("%d: received %s\n", getpid(), inbuf);
    }

    exit(0);
}