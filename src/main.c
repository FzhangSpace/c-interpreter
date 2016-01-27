#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

int token;
char *src, *old_src;
int poolsize;
int line;

/* 用于词法分析，获取下一个标记，它将自动忽略空白字符 */
void next() 
{
    token = *src++;
    return;
}

/* 用于解析一个表达式 */
void expression(int level)  
{
    //do nothing
}

/* 词法分析的入口,用于分析整个C语言程序 */
void program() 
{
    next();
    while (token > 0) {
        printf("token is : %c\n", token);
        next();
    }
}

/* 虚拟机的入口,用于解释目标代码 */
int eval() 
{
    //do nothing yet
    return 0;
}

int main(int argc, char **argv)
{
    int i, fd;
    argc--;
    argv++; /* 指到第二个参数 */
    
    poolsize = 256*1024;

    line = 1;
    
    /* 把文件的内容读到内存 */
    if ((fd = open(*argv, 0)) < 0) {
        printf("could not open(%s)\n", *argv);
        return -1;
    }

    if (!(src = old_src = malloc(poolsize))) {
        printf("could not malloc(%d) for source area\n", poolsize);
        return -1;
    }

    if ((i = read(fd, src, poolsize-1)) < 0) {
        printf("read() returned %d\n", i);
        return -1;
    }

    src[i] = 0;
    close(fd);

    /* 分析源码 */
    program();

    return eval();
}

