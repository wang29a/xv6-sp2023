#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

int
main(int argc, char *argv[])
{
    int i = 0;
    if(argc < 2){
        fprintf(2, "xargs need argement!\n");
        exit(-1);
    }
    char arg[MAXARG][64];
    for(i = 1; i < argc; i ++){
        // printf("#%s#", argv[i]);
        memmove(arg[i-1], argv[i], strlen(argv[i])*sizeof(char));
    }
    int ret = 0, idx = 0;
    char buf[256], b;
    while((ret = read(0, &b, 1)) > 0){
        buf[idx ++] = b;
        if(b == '\n'){
            buf[idx-1] = '\0';
            // printf("#%s#", buf);
            memmove(arg[i-1], buf, strlen(buf)*sizeof(char));
            i ++;
            idx = 0;
        }
        if(idx > 255){
            fprintf(2, "error: overflow buf\n");
            exit(-1);
        }
    }
    char *arv[MAXARG];
    for (int j = 0; j < i-1; j ++){
        // printf("#%s#", arg[j]);
        arv[j] = arg[j];
    }
    argv[i] = '\0';
    for (int j = 0; j < i-1; j ++){
        // printf("#%s#", arv[j]);
    }
    if(fork() == 0){
        exec(arv[0], arv);
        fprintf(2, "exec %s error\n", argv[1]);
    }
    wait(0);
    exit(0);
}