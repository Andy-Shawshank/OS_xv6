#include "kernel/types.h"
#include "user.h"
#include <stddef.h>

int main(int argc, char* argv[]){
    int p[2];
    int c[2];
    pipe(p);
    pipe(c);
    char buff[8];
    int rc = fork();
    if(rc == 0){//子进程读,子进程写
        //sleep(1);
        close(p[1]);
        read(p[0],buff,4);//读四个字节
        printf("%d: received ping\n",getpid());
        close(p[0]);

        close(c[0]);
        write(c[1],"pong",4);
        close(c[1]);

    }
    else{//父进程写,父进程读
        close(p[0]);
        write(p[1],"ping",4);
        close(p[1]);

        close(c[1]);
        read(c[0],buff,4);//读四个字节
        printf("%d: received pong\n",getpid());
        close(c[0]);
    }
    exit(0);
}