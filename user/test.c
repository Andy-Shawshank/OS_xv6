
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(int argc, char* argv[]){
    
    /*int p[2];
    int c[2];
    pipe(p);
    pipe(c);
    char buff[8];
    int rc = fork();
    if(rc == 0){//子进程读,子进程写
        //sleep(1);
        close(p[1]);
        int read_len = read(p[0],buff,4);//读四个字节
        printf("%d\n",read_len);//打印最终读了多少
        printf("%c\n",buff[1]);      
        close(p[0]);

        close(c[0]);
        write(c[1],"shit",4);
        close(c[1]);

    }
    else{//父进程写,父进程读
        close(p[0]);
        write(p[1],"test",4);
        close(p[1]);

        close(c[1]);
        int read_len = read(c[0],buff,4);//读四个字节
        printf("%d\n",read_len);//打印最终读了多少
        printf("%c\n",buff[1]);      
        close(c[0]);

        wait(NULL);
        printf("i am father\n");


    }
    int test[2] = dup(p);
    close(test[1]);
    int read_len = read(test[0],buff,4);//读四个字节
    printf("%d\n",read_len);//打印最终读了多少        
    printf("%c\n",buff[1]);      
    close(test[0]);
    exit(0);*/


    
    /*int p[2];
    pipe(p);
    int init[34]={2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35};
    int buff1[34];
    int buff2[34];
    printf("%d \n",p[0]);
    printf("%d \n",p[1]);
    int result = dup(p[0]);
    //把2~35写进管道
    close(p[0]);
    write(p[1],init,136);
    close(p[1]);*/
    //在读管道之前dup文件描述符能起到保存的作用吗
    //test一下连续读的结果,结果表明并非读一次数据就全无
    /*printf("dup后的fd是:%d \n",result);
    
    
    
    read(result,buff1,4);
    read(result,buff2,4);
    printf("%d \n",buff1[0]);
    printf("%d \n",buff2[0]);*/

    /*int rc = fork();
    if(rc == 0){//child
        //让子进程读,父进程更新可行吗
        close(p[1]);
        int read_len = read(p[0],init);
    }
    else{//parent

    }*/

    //研究一下dup怎么用


int child_pid;
if((child_pid=fork())==0){
while(1);
printf("forbidden zone\n");
exit(0);
}
else{
while(getc(stdin)){
    wait(0);
exit(0);
}
}
}
