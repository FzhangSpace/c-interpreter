#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

/* 用于读取源文件内容,词法分析,语法分析 */
int token;
char *src, *old_src;
int poolsize;
int line;

/* 模拟代码段/数据段以及栈 */
int *text, *old_text, *stack;
char *data;

/* 虚拟计算寄存器 */
int *pc, *bp, *sp, ax, cyle;
/*
	pc程序计数器 他存放的是内存地址,该地址中存放着下一条要执行的计算器指令
	sp指针寄存器 永远指向当前的栈顶. 
		注意的是由于栈是位于高地质并向低地址增长的,所以入栈是sp的值减小
	bp基址指针.  也是用于指向栈的某些位置,在调用函数是使用到它
	ax通用寄存器 在我们的虚拟机中,它用于存放一条指令执行后的结果
*/

/* CPU指令集 */
enum { LEA ,IMM ,JMP ,CALL,JZ  ,JNZ ,ENT ,ADJ ,LEV ,LI  ,LC  ,SI  ,SC  ,PUSH,
       OR  ,XOR ,AND ,EQ  ,NE  ,LT  ,GT  ,LE  ,GE  ,SHL ,SHR ,ADD ,SUB ,MUL ,DIV ,MOD ,
       OPEN,READ,CLOS,PRTF,MALC,MSET,MCMP,EXIT };


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
    int op, *tmp;
    while (1) {
    	switch (op)
    	{
		case IMM:	ax = *pc++; break;
		case LC:	ax = *(char*)ax; break;
		case LI:	ax = *(int*)ax; break;
		case SC:	ax = *(char *)*sp++ = ax; break;
		case SI:	*(int*)*sp++ = ax; break;
			
		case PUSH:	*--sp = ax; break;
		case JMP:	pc = (int*)*pc; break;
		
		case JZ:	pc = ax ? pc + 1 : (int*)*pc;	break;
		case JNZ:	pc = ax ? (int*)*pc : pc + 1; break;
			
		case CALL:	*--sp = (int)(pc+1); pc = (int*)*pc; break;
		case ENT:	*--sp = (int)bp; bp = sp; 
					sp = sp - *pc++; break;
		case ADJ:	sp = sp + *pc++; break;
		case LEV:	sp = bp; bp = (int*)*sp++; 
					pc = (int*)*sp++; break;
		
		case OR:	ax = *sp++ | ax; break;
		case XOR:	ax = *sp++ ^ ax; break;
		case AND: 	ax = *sp++ & ax; break;
		case EQ:	ax = *sp++ == ax; break;
		case NE:	ax = *sp++ != ax; break;
		case LT:	ax = *sp++ < ax; break;
		case LE:	ax = *sp++ <= ax; break;
		case GT:	ax = *sp++ > ax; break;
		case GE:	ax = *sp++ >= ax; break;
		case SHL:	ax = *sp++ << ax; break;
		case SHR:	ax = *sp++ >> ax; break;
		case ADD:	ax = *sp++ + ax; break;
		case SUB:	ax = *sp++ - ax; break;
		case MUL:	ax = *sp++ * ax; break;
		case DIV:	ax = *sp++ / ax; break;
		case MOD:	ax = *sp++ % ax; break;
			
		case EXIT:	printf("exit(%d)", *sp);	return *sp;
		case OPEN:	ax = open((char*)sp[1],sp[0]); break;
		case CLOS:	ax = close(*sp); break;
		case READ:	ax = read(sp[2], (char*)sp[1], *sp); break;
		case PRTF:	tmp = sp + pc[1];
					ax = printf((char*)tmp[-1], tmp[-2], tmp[-3], tmp[-4], tmp[-5], tmp[-6]);
					break;
		case MALC:	ax = (int)malloc(*sp); break;
		case MSET:	ax = (int)memset((char*)sp[2], sp[1], *sp); break;
		case MCMP:	ax = memcmp((char*)sp[2], (char*)sp[1], *sp); break;
		default:
			printf("unknown instruction:%d\n", op);
			return -1;
    	}
    }
    

    
    
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

    /* allcate memory for virtual machine */
    if (!(text = old_text = malloc(poolsize))) {
        printf("could not malloc(%d) for text area\n", poolsize);
        return -1;
    }
    if (!(data = malloc(poolsize))) {
        printf("could not malloc(%d) for data area\n", poolsize);
        return -1;
    }
    if (!(stack = malloc(poolsize))) {
        printf("could not malloc(%d) for stack area\n", poolsize);
        return -1;
    }
    memset(text, 0, poolsize);
    memset(data, 0, poolsize);
    memset(stack, 0, poolsize);
    
    /* 这是为了栈的增长方向是向下的,所以先把指针指向高地址 */
    bp = sp = (int*)((int)stack + poolsize);
    ax = 0;
  
    
    
    i = 0;
    text[i++] = IMM;
    text[i++] = 10;
    text[i++] = PUSH;
    text[i++] = IMM;
    text[i++] = 20;
    text[i++] = ADD;
    text[i++] = PUSH;
    text[i++] = EXIT;
    pc = text;
    

    /* 分析源码 */
    program();

    return eval();
}

