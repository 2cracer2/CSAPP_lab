# boomb_phase_1
反汇编
```
 objdump -d > obj.txt
 ```

找到phase_1位置,gdb中调试设置断点。
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