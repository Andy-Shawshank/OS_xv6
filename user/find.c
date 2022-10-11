#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"
#include "kernel/fs.h"

// find 函数,文件夹和文件名作为独立参数
void
find(char *dir, char *file)
{   
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    // open() 函数打开路径，返回一个文件描述符，如果错误返回 -1
    if ((fd = open(dir, 0)) < 0)
    {
        fprintf(2, "find: cannot open %s\n", dir);
        return;
    }

    if (fstat(fd, &st) < 0)
    {
        fprintf(2, "find: cannot stat %s\n", dir);
        close(fd);
        return;
    }

    // 如果不是目录类型
    if (st.type != T_DIR)
    {
        // 报类型不是目录错误
        fprintf(2, "find: %s is not a directory\n", dir);
        close(fd);
        return;
    }

    // 如果路径过长放不入缓冲区，则报错提示
    if(strlen(dir) + 1 + DIRSIZ + 1 > sizeof buf)
    {
        fprintf(2, "find: directory too long\n");
        // 关闭文件描述符 fd
        close(fd);
        return;
    }
    // 将 dir 指向的字符串即绝对路径复制到 buf
    strcpy(buf, dir);
    // buf 是一个绝对路径，p 是一个文件名，通过加 "/" 前缀拼接在 buf 的后面
    p = buf + strlen(buf);
    *p++ = '/';
    // 读取 fd ，如果 read 返回字节数与 de 长度相等则循环
    while (read(fd, &de, sizeof(de)) == sizeof(de))
    {
        if(de.inum == 0)
            continue;
        // 不要递归 "." 和 "..."
        if (!strcmp(de.name, ".") || !strcmp(de.name, ".."))
            continue;
        // memmove，把 de.name 信息复制 p，其中 de.name 代表文件名
        memmove(p, de.name, DIRSIZ);
        // 设置文件名结束符
        p[DIRSIZ] = 0;
        if(stat(buf, &st) < 0)
        {
            fprintf(2, "find: cannot stat %s\n", buf);
            continue;
        }
        // 如果是目录类型，递归查找
        if (st.type == T_DIR)
        {
            find(buf, file);
        }
        // 如果是文件类型 并且 名称与要查找的文件名相同
        else if (st.type == T_FILE && !strcmp(de.name, file))
        {
            // 打印缓冲区存放的路径
            printf("%s\n", buf);
        } 
    }
}

int
main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(2, "wrong format of path\n");
        exit(-1);
    }
    // 调用 find 函数查找指定目录下的文件
    find(argv[1], argv[2]);
    exit(0);
}
