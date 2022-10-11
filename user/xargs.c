#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"
#include <stddef.h>

#define MAXN 1024

int
main(int argc, char *argv[])
{
    // 如果参数个数小于 2
    if (argc < 2) {
        fprintf(2, "command more than one argument at least\n");
        exit(1);
    }
    // 存放子进程 exec 的参数
    char * argvs[MAXARG];
    // 索引
    int index = 0;
    // 略去 xargs ，用来保存命令行参数
    for (int i = 1; i < argc; ++i) {
        argvs[index] = argv[i];
        index++;
    }
    // 缓冲区存放从管道读出的数据
    char buf[MAXN] = {"\0"};
    
    int n;

    while((n = read(0, buf, MAXN)) > 0 ) {
        // 临时缓冲区存放追加的参数
		char temp[MAXN] = {"\0"};
        // xargs 命令的参数后面再追加参数
        argvs[index] = temp;
        // 内循环获取追加的参数并创建子进程执行命令
        for(int i = 0; i < strlen(buf); ++i) {
            // 读取单个输入行，当遇到换行符时，创建子线程
            if(buf[i] == '\n') {
                // 创建子线程执行命令
                if (fork() == 0) {
                    exec(argv[1], argvs);
                }
                // 等待子线程执行完毕
                wait(NULL);
            } else {
                // 否则，读取管道的输出作为输入
                temp[i] = buf[i];
            }
        }
    }    
    exit(0);
}
