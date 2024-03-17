#include "kernel/types.h"
#include "user/user.h"


int 
main(int argc, char *argv[])
{
    int slpt;
    if(argc != 2)
    {
        fprintf(2, "error: please slepp number\n");
        exit(1);
    }
    slpt = atoi(argv[1]);
    sleep(slpt);

    exit(0);
}