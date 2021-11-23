# boomb_phase_1

反汇编

```
 objdump -d > obj.txt
```

找到phase_1位置,gdb中调试设置断点。

```
gdb ./bomb
break phase_1
break explode_bomb
run
```

通过反汇编源码分析，为比较地址0x402400的值，通过x/s 0x402400或者 print (char *) 0x402400 打印出结果就得到了"Border relations with Canada have never been better."

或者编写脚本直接以二进制读写，将内存中地址直接打印

```
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int fd = open("bomb", O_RDONLY);
    char buf[100001];
    read(fd, buf, 100000);
    // printf("%s\n", buf + 0x2622); // DrEvil
    printf("%s\n", buf + 0x245e);
    return 0;
}
```

# boomb_phase_2

```
0000000000400efc <phase_2>:
  400efc:	55                   	push   %rbp
  400efd:	53                   	push   %rbx
  400efe:	48 83 ec 28          	sub    $0x28,%rsp
  400f02:	48 89 e6             	mov    %rsp,%rsi
  400f05:	e8 52 05 00 00       	callq  40145c <read_six_numbers>
  400f0a:	83 3c 24 01          	cmpl   $0x1,(%rsp)
  400f0e:	74 20                	je     400f30 <phase_2+0x34>
  400f10:	e8 25 05 00 00       	callq  40143a <explode_bomb>
  400f15:	eb 19                	jmp    400f30 <phase_2+0x34>
  400f17:	8b 43 fc             	mov    -0x4(%rbx),%eax
  400f1a:	01 c0                	add    %eax,%eax
  400f1c:	39 03                	cmp    %eax,(%rbx)
  400f1e:	74 05                	je     400f25 <phase_2+0x29>
  400f20:	e8 15 05 00 00       	callq  40143a <explode_bomb>
  400f25:	48 83 c3 04          	add    $0x4,%rbx
  400f29:	48 39 eb             	cmp    %rbp,%rbx
  400f2c:	75 e9                	jne    400f17 <phase_2+0x1b>
  400f2e:	eb 0c                	jmp    400f3c <phase_2+0x40>
  400f30:	48 8d 5c 24 04       	lea    0x4(%rsp),%rbx
  400f35:	48 8d 6c 24 18       	lea    0x18(%rsp),%rbp
  400f3a:	eb db                	jmp    400f17 <phase_2+0x1b>
  400f3c:	48 83 c4 28          	add    $0x28,%rsp
  400f40:	5b                   	pop    %rbx
  400f41:	5d                   	pop    %rbp
  400f42:	c3                   	retq   

```

由汇编代码得知，读取输入的六个数字来进行一系列判断是否引爆炸弹。 首先看**cmpl $0x1,(%rsp)**处，第一个数必须是1，不是炸弹就爆炸。

然后转跳构成循环，其中比较要求后一个数为前一个数的二倍，否则触发爆炸

```·
  400f25:	48 83 c3 04          	add    $0x4,%rbx
  400f29:	48 39 eb             	cmp    %rbp,%rbx
```

为判断循环结束条件：rbx+4 后，即基指针后移一位，如果rbx <= rbp 了，即到未达栈顶，继续循环，否则跳到add    $0x28,%rsp 之后出栈，释放栈帧

答案为：`1 2 4 8 16 32`
# boomb_phase_3
```
0000000000400f43 <phase_3>:
  400f43:	48 83 ec 18          	sub    $0x18,%rsp
  400f47:	48 8d 4c 24 0c       	lea    0xc(%rsp),%rcx
  400f4c:	48 8d 54 24 08       	lea    0x8(%rsp),%rdx
  400f51:	be cf 25 40 00       	mov    $0x4025cf,%esi
  400f56:	b8 00 00 00 00       	mov    $0x0,%eax
  400f5b:	e8 90 fc ff ff       	callq  400bf0 <__isoc99_sscanf@plt>
  400f60:	83 f8 01             	cmp    $0x1,%eax
  400f63:	7f 05                	jg     400f6a <phase_3+0x27>
  400f65:	e8 d0 04 00 00       	callq  40143a <explode_bomb>
  400f6a:	83 7c 24 08 07       	cmpl   $0x7,0x8(%rsp)
  400f6f:	77 3c                	ja     400fad <phase_3+0x6a>
  400f71:	8b 44 24 08          	mov    0x8(%rsp),%eax
  400f75:	ff 24 c5 70 24 40 00 	jmpq   *0x402470(,%rax,8)
  400f7c:	b8 cf 00 00 00       	mov    $0xcf,%eax
  400f81:	eb 3b                	jmp    400fbe <phase_3+0x7b>
  400f83:	b8 c3 02 00 00       	mov    $0x2c3,%eax
  400f88:	eb 34                	jmp    400fbe <phase_3+0x7b>
  400f8a:	b8 00 01 00 00       	mov    $0x100,%eax
  400f8f:	eb 2d                	jmp    400fbe <phase_3+0x7b>
  400f91:	b8 85 01 00 00       	mov    $0x185,%eax
  400f96:	eb 26                	jmp    400fbe <phase_3+0x7b>
  400f98:	b8 ce 00 00 00       	mov    $0xce,%eax
  400f9d:	eb 1f                	jmp    400fbe <phase_3+0x7b>
  400f9f:	b8 aa 02 00 00       	mov    $0x2aa,%eax
  400fa4:	eb 18                	jmp    400fbe <phase_3+0x7b>
  400fa6:	b8 47 01 00 00       	mov    $0x147,%eax
  400fab:	eb 11                	jmp    400fbe <phase_3+0x7b>
  400fad:	e8 88 04 00 00       	callq  40143a <explode_bomb>
  400fb2:	b8 00 00 00 00       	mov    $0x0,%eax
  400fb7:	eb 05                	jmp    400fbe <phase_3+0x7b>
  400fb9:	b8 37 01 00 00       	mov    $0x137,%eax
  400fbe:	3b 44 24 0c          	cmp    0xc(%rsp),%eax
  400fc2:	74 05                	je     400fc9 <phase_3+0x86>
  400fc4:	e8 71 04 00 00       	callq  40143a <explode_bomb>
  400fc9:	48 83 c4 18          	add    $0x18,%rsp
  400fcd:	c3                   	retq   
```

rsp+0xc与rsp+0x8的值分别给rcx与rdx，下一行将一个地址值复制给了esi，接着将eax置为0，下一步调用了库函数sscanf，想到sscanf中的参数中需要一个格式化字符串，那么esi中的这个地址值就很有可能存放了这个字符串.
在gdb中用**x/s 0x4025cf** 打印出这个值为0x4025cf:       "%d %d"，即读入两个整型值
在gdb中进行验证（在执行`phase_3`中）随便输入 3 8

```·
(gdb) x /32xb $rsp
```

显示结果为

```·
0x7ffffffedc18: 0xc9    0x0f    0x40    0x00    0x00    0x00    0x00    0x00
0x7ffffffedc20: 0x10    0x22    0x40    0x00    0x00    0x00    0x00    0x00
0x7ffffffedc28: 0x03    0x00    0x00    0x00    0x08    0x00    0x00    0x00
0x7ffffffedc30: 0x00    0x00    0x00    0x00    0x00    0x00    0x00    0x00
```

即可以确定第一个值为`rsp+0x8`，第二个值为`rsp+0xc`
后面11行将`rsp+0x8`中存放的值与`0x7`进行比较，如果大于`0x7`则跳到`400fad`的位置：

```·
  400f6a:	83 7c 24 08 07       	cmpl   $0x7,0x8(%rsp)
  400f6f:	77 3c                	ja     400fad <phase_3+0x6a>
```

400fad的位置就会触发炸弹

后面`rsp+0x8`中存放的值复制入`eax`，之后再进行一个跳转，跳转到的地址为`0x402470(,%rax,8)`，这就是一个典型的`switch`语句的实现：直接跳转到索引*位移的指令位置

```·
400f71:	8b 44 24 08          	mov    0x8(%rsp),%eax
400f75:	ff 24 c5 70 24 40 00 	jmpq   *0x402470(,%rax,8)
```

可将switch语句转换出来：

```
x = 0
400f7c:	b8 cf 00 00 00       	mov    $0xcf,%eax
400f81:	eb 3b                	jmp    400fbe <phase_3+0x7b>
x = 2
400f83:	b8 c3 02 00 00       	mov    $0x2c3,%eax
400f88:	eb 34                	jmp    400fbe <phase_3+0x7b>
x = 3
400f8a:	b8 00 01 00 00       	mov    $0x100,%eax
400f8f:	eb 2d                	jmp    400fbe <phase_3+0x7b>
x = 4
400f91:	b8 85 01 00 00       	mov    $0x185,%eax
400f96:	eb 26                	jmp    400fbe <phase_3+0x7b>
x = 5
400f98:	b8 ce 00 00 00       	mov    $0xce,%eax
400f9d:	eb 1f                	jmp    400fbe <phase_3+0x7b>
x = 6
400f9f:	b8 aa 02 00 00       	mov    $0x2aa,%eax
400fa4:	eb 18                	jmp    400fbe <phase_3+0x7b>
x = 7
400fa6:	b8 47 01 00 00       	mov    $0x147,%eax
400fab:	eb 11                	jmp    400fbe <phase_3+0x7b>

400fad:	e8 88 04 00 00       	callq  40143a <explode_bomb>
400fb2:	b8 00 00 00 00       	mov    $0x0,%eax
400fb7:	eb 05                	jmp    400fbe <phase_3+0x7b>
x = 1
400fb9:	b8 37 01 00 00       	mov    $0x137,%eax
400fbe:	3b 44 24 0c          	cmp    0xc(%rsp),%eax
400fc2:	74 05                	je     400fc9 <phase_3+0x86>

400fc4:	e8 71 04 00 00       	callq  40143a <explode_bomb>
400fc9:	48 83 c4 18          	add    $0x18,%rsp
400fcd:	c3                   	retq   
```

而每个分支都将一个数复制到了`eax`中，也就是说只要根据不同的第一个参数的值读入对应的第二个参数就可以了，所以我们可以随意选择一个x值 比如x=0，第二个值赋值为0xcf即207

**即最终结果可以为 0 207**
# boomb_phase_4
```
000000000040100c <phase_4>:
  40100c:	48 83 ec 18          	sub    $0x18,%rsp
  401010:	48 8d 4c 24 0c       	lea    0xc(%rsp),%rcx
  401015:	48 8d 54 24 08       	lea    0x8(%rsp),%rdx
  40101a:	be cf 25 40 00       	mov    $0x4025cf,%esi
  40101f:	b8 00 00 00 00       	mov    $0x0,%eax
  401024:	e8 c7 fb ff ff       	callq  400bf0 <__isoc99_sscanf@plt>
  401029:	83 f8 02             	cmp    $0x2,%eax
  40102c:	75 07                	jne    401035 <phase_4+0x29>
  40102e:	83 7c 24 08 0e       	cmpl   $0xe,0x8(%rsp)
  401033:	76 05                	jbe    40103a <phase_4+0x2e>
  401035:	e8 00 04 00 00       	callq  40143a <explode_bomb>
  40103a:	ba 0e 00 00 00       	mov    $0xe,%edx
  40103f:	be 00 00 00 00       	mov    $0x0,%esi
  401044:	8b 7c 24 08          	mov    0x8(%rsp),%edi
  401048:	e8 81 ff ff ff       	callq  400fce <func4>
  40104d:	85 c0                	test   %eax,%eax
  40104f:	75 07                	jne    401058 <phase_4+0x4c>
  401051:	83 7c 24 0c 00       	cmpl   $0x0,0xc(%rsp)
  401056:	74 05                	je     40105d <phase_4+0x51>
  401058:	e8 dd 03 00 00       	callq  40143a <explode_bomb>
  40105d:	48 83 c4 18          	add    $0x18,%rsp
  401061:	c3                   	retq   
  ```
  前面部分与上题类似也是要求输入两个整数,
  sscanf的返回值应该是2，否则引爆；然后接下来第一个值与0xe比较，必须小于0xe，否则引爆；接下来把0xe赋给`edx`、0x0赋给`esi`，`rsp+0x8`的值赋给`edi`；再调用`func4`函数。以及后面`func4` 返回值不为0也爆炸，和rsp+0xc的值不为0也爆炸。

```·
0000000000400fce <func4>:
  400fce:	48 83 ec 08          	sub    $0x8,%rsp
  400fd2:	89 d0                	mov    %edx,%eax
  400fd4:	29 f0                	sub    %esi,%eax
  400fd6:	89 c1                	mov    %eax,%ecx
  400fd8:	c1 e9 1f             	shr    $0x1f,%ecx
  400fdb:	01 c8                	add    %ecx,%eax
  400fdd:	d1 f8                	sar    %eax
  400fdf:	8d 0c 30             	lea    (%rax,%rsi,1),%ecx
  400fe2:	39 f9                	cmp    %edi,%ecx
  400fe4:	7e 0c                	jle    400ff2 <func4+0x24>
  400fe6:	8d 51 ff             	lea    -0x1(%rcx),%edx
  400fe9:	e8 e0 ff ff ff       	callq  400fce <func4>
  400fee:	01 c0                	add    %eax,%eax
  400ff0:	eb 15                	jmp    401007 <func4+0x39>
  400ff2:	b8 00 00 00 00       	mov    $0x0,%eax
  400ff7:	39 f9                	cmp    %edi,%ecx
  400ff9:	7d 0c                	jge    401007 <func4+0x39>
  400ffb:	8d 71 01             	lea    0x1(%rcx),%esi
  400ffe:	e8 cb ff ff ff       	callq  400fce <func4>
  401003:	8d 44 00 01          	lea    0x1(%rax,%rax,1),%eax
  401007:	48 83 c4 08          	add    $0x8,%rsp
  40100b:	c3                   	retq   
```

形式上func4为递归结构，转换出来为：

```·
int fun(int a1, int a2, int x){
    int b = (a1 - a2) >> 31;
    int result = ((a1-a2) + b) >> 1;
    b = result + a2;
    if(b == x) return 0;
    if(b < x) {
        result = fun(a1, b + 1, x);
        return result * 2 + 1;
    }else{
        result = fun(b - 1, a2, x);
        return result * 2;
    }
}
```