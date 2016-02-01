# c-interpreter
simple interpreter of C. Inspired by c4 and largely based on it.

source:http://blog.jobbole.com/97332/


##step02:
source:http://blog.jobbole.com/97359/

###�Ĵ���
	
	PC ���������������ŵ���һ���ڴ��ַ���õ�ַ�д���� ��һ�� Ҫִ�еļ����ָ�
	SP ָ��Ĵ�������Զָ��ǰ��ջ����ע���������ջ��λ�ڸߵ�ַ����͵�ַ�����ģ�������ջʱ SP ��ֵ��С��
	BP ��ַָ�롣Ҳ������ָ��ջ��ĳЩλ�ã��ڵ��ú���ʱ��ʹ�õ�����
	AX ͨ�üĴ��������ǵ�������У������ڴ��һ��ָ��ִ�к�Ľ����
	
	
###ָ�	
	
```c
enum { LEA ,IMM ,JMP ,CALL,JZ  ,JNZ ,ENT ,ADJ ,LEV ,LI  ,LC  ,SI  ,SC  ,PUSH,
       OR  ,XOR ,AND ,EQ  ,NE  ,LT  ,GT  ,LE  ,GE  ,SHL ,SHR ,ADD ,SUB ,MUL ,DIV ,MOD ,
       OPEN,READ,CLOS,PRTF,MALC,MSET,MCMP,EXIT };
``` 

####MOV
	
	�����ݷŽ��Ĵ������ڴ��ַ,����C�ĸ�ֵ
	�÷�  MOV source dest
	��ʾ��source�����ݷ���dest��,���ǿ���ʹһ����,�Ĵ���,����һ���ڴ��ַ
	
	��Ϊ���ǵ������ֻ��һ���Ĵ���,�ټ���ʶ������������ǱȽ�����,
	Ϊ�˼򻯲���,��MOVָ��ֽ��5��ָ��
		- IMM <num>  ��<num>����Ĵ���ax��
		- LC 	����Ӧ��ַ�е��ַ�����ax��,Ҫ��ax�д�ŵ�ַ
		- LI	����Ӧ��ַ�е���������ax��,Ҫ��ax�д�ŵ�ַ
		- SC	��ax�е�������Ϊ�ַ�������ַ��,Ҫ��ջ����ŵ�ַ.
		- SI  	��ax�е�������Ϊ����������ַ��,Ҫ��ջ����ŵ�ַ

####PUSH

	��ֵ��Ĵ���,�������ǵ��������,���������ǽ�ax��ֵ����ջ��.
	��Ҫ��Ϊ�˼һ��������ʵ��,��������Ҳֻ��һ���Ĵ���ax

####JMP
	
	JMP <addr> ����תָ��,�������ؽ���ǰ��PC�Ĵ�������Ϊָ����<addr>

####JZ/JNZ
	
	Ϊ��ʵ��if���,������Ҫ�����ж���ص�ָ��
	��������ֻ���������򵥵��ж�,�����(ax)Ϊ���Ϊ������µ���ת

####�Ӻ������� CALL/ENT/ADJ/LEV
	
	���Ƚ���CALL <addr>��RETָ��,CALL����������ת����ַΪ<addr>���Ӻ���,RET�����ڴ��Ӻ����з���
	�������ǲ�ֱ��ʹ��RETָ��,���Ǻ���ʹ��LEVָ���������
	
	��ʵ�ʵ��ú���ʱ������Ҫ���Ǻ����ĵ�ַ����Ҫ������δ��ݲ�������η��ؽ����
	��������Լ��������Ӻ����з��ؽ������ô���ڷ���ʱ������ ax �У���������һ��ֵ��Ҳ������һ����ַ

####ENT
	
	ENT <size> ֵ����enter,����ʵ��"make new call frame"�Ĺ���
	���Ǳ��浱ǰָ��,ͬʱ��ջ�ϱ���һ���ռ�,���Դ�žֲ�����.
	
####ADJ
	
	ADJ <size> ����ʵ�� "remove arguments from frame"
	�ڽ������Ӻ���ʱ,ѹ��ջ�е��������,����������Ϊ���ǵ�ADDָ�������
	
####LEV
	
	��ִ�����Ӻ���֮��,�����µ���֮ǰ�����Ӻ�����λ��
	
####LEA
	
	������Ϊ�����Ӻ����еõ������Ӻ����Ĳ���
	
####�����ָ�

	OR  XOR  AND  EQ  NE  LT  LE  GT  GE  
	SHL  SHR  ADD  SUB  MUL  DIV  MOD
	
####���ú���

	��������������Ҫ�õ��ĺ����У�exit, open, close, read, printf, malloc, memset ��memcmp
	
###���Դ������:
	
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







