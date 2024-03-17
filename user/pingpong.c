#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int p1[2], p2[2];
    pipe(p1);
    pipe(p2);
    int pid;
    if(fork() == 0){
        char buf[1];
        pid = getpid();
        close(p1[1]);

        read(p1[0], buf, sizeof(buf));
        printf("%d: received ping\n", pid);
        close(p1[0]);

        write(p2[1], &buf, 1);
        close(p2[1]);
        exit(0);
    }else{
        char buf[1];
        close(p1[0]);
        close(p2[1]);
        pid = getpid();

        write(p1[1], "z", 1);
        close(p1[1]);
        
        read(p2[0], &buf, sizeof(buf));
        close(p2[0]);

        wait(0);
        printf("%d: received pong\n", pid);
    }
    exit(0);
}