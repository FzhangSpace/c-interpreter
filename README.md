# c-interpreter
simple interpreter of C. Inspired by c4 and largely based on it.

source:http://blog.jobbole.com/97332/


##step02:
source:http://blog.jobbole.com/97359/

###寄存器
	
	PC 程序计数器，它存放的是一个内存地址，该地址中存放着 下一条 要执行的计算机指令。
	SP 指针寄存器，永远指向当前的栈顶。注意的是由于栈是位于高地址并向低地址增长的，所以入栈时 SP 的值减小。
	BP 基址指针。也是用于指向栈的某些位置，在调用函数时会使用到它。
	AX 通用寄存器，我们的虚拟机中，它用于存放一条指令执行后的结果。
	
	
###指令集	
	
```c
enum { LEA ,IMM ,JMP ,CALL,JZ  ,JNZ ,ENT ,ADJ ,LEV ,LI  ,LC  ,SI  ,SC  ,PUSH,
       OR  ,XOR ,AND ,EQ  ,NE  ,LT  ,GT  ,LE  ,GE  ,SHL ,SHR ,ADD ,SUB ,MUL ,DIV ,MOD ,
       OPEN,READ,CLOS,PRTF,MALC,MSET,MCMP,EXIT };
``` 

####MOV
	
	将数据放进寄存器或内存地址,类似C的赋值
	用法  MOV source dest
	表示将source的内容放在dest中,它们可以使一个数,寄存器,或是一个内存地址
	
	因为我们的虚拟机只有一个寄存器,再加上识别参数的类型是比较困难,
	为了简化操作,将MOV指令分解成5个指令
		- IMM <num>  将<num>放入寄存器ax中
		- LC 	将对应地址中的字符载入ax中,要求ax中存放地址
		- LI	将对应地址中的整数载入ax中,要求ax中存放地址
		- SC	将ax中的数据作为字符存放入地址中,要求栈顶存放地址.
		- SI  	将ax中的数据作为整数存放入地址中,要求栈顶存放地址

####PUSH

	将值或寄存器,而在我们的虚拟机中,它的作用是将ax的值放入栈中.
	主要是为了家伙虚拟机的实现,并且我们也只有一个寄存器ax

####JMP
	
	JMP <addr> 是跳转指令,无条件地将当前的PC寄存器设置为指定的<addr>

####JZ/JNZ
	
	为了实现if语句,我们需要条件判断相关的指令
	我们这里只是先两个简单的判断,即结果(ax)为零或为零情况下的跳转

####子函数调用 CALL/ENT/ADJ/LEV
	
	首先介绍CALL <addr>和RET指令,CALL的作用是跳转到地址为<addr>的子函数,RET则用于从子函数中返回
	不过我们不直接使用RET指令,我们后面使用LEV指令来替代它
	
	在实际调用函数时，不仅要考虑函数的地址，还要考虑如何传递参数和如何返回结果。
	这里我们约定，如果子函数有返回结果，那么就在返回时保存在 ax 中，它可以是一个值，也可以是一个地址

####ENT
	
	ENT <size> 值得是enter,用于实现"make new call frame"的功能
	就是保存当前指针,同时在栈上保留一定空间,用以存放局部变量.
	
####ADJ
	
	ADJ <size> 用于实现 "remove arguments from frame"
	在将调用子函数时,压入栈中的数据清除,本质上是因为我们的ADD指令功能有限
	
####LEV
	
	在执行完子函数之后,将重新调到之前调用子函数的位置
	
####LEA
	
	作用是为了在子函数中得到传入子函数的参数
	
####运算符指令集

	OR  XOR  AND  EQ  NE  LT  LE  GT  GE  
	SHL  SHR  ADD  SUB  MUL  DIV  MOD
	
####内置函数

	编译器中我们需要用到的函数有：exit, open, close, read, printf, malloc, memset 及memcmp
	
###测试代码解析:
	
```c
int main(int argc, char *argv[])
{
    ax = 0;
    ...
 
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
 
    ...
    program();
}
```







