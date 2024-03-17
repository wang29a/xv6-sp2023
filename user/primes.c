#include "kernel/types.h"
#include "user/user.h"

int check(int n)
{
    int i;
    for(i = 2; i < n; i ++){
        if(n%i == 0){
            return 0;
        }
    }
    return 1;
}

void sub(int fp[2]) __attribute__((noreturn));

void
sub(int fp[2])
{
    close(fp[1]);
    int num, mod, sp[2], ret;
    pipe(sp);
    if(fp[0] < 13 && fork() == 0){
        sub(sp);
    }
    close(sp[0]);
    read(fp[0], &mod, sizeof(int));

    printf("prime %d\n", mod);
    while((ret = read(fp[0], &num, sizeof(int))) > 0){
        if(num %mod != 0) {
            write(sp[1], &num, sizeof(int));
        }
    }
    close(sp[1]);
    close(fp[0]);
    wait(0);
    exit(0);
}

int
main()
{
    int x;
    int p[2];
    pipe(p);
    if(fork() == 0){
        sub(p);
    }
    close(p[0]);
    for (x = 2; x <= 35; x ++){
        write(p[1], &x, sizeof(4));
    }
    close(p[1]);

    int status;
    if (wait(&status), status != 0){
        fprintf(2, "son process error\n");
        exit(-1);
    }
    exit(0);
}