/*
 * @Author: Cracer 
 * @Date: 2021-11-26 20:58:38 
 * @Last Modified by: Cracer
 * @Last Modified time: 2021-11-26 23:36:19
 * 
 */

#include <stdio.h>

int fun(int a1, int a2, int x)
{
    int b = (a1 - a2) >> 31;
    int result = ((a1 - a2) + b) >> 1;
    b = result + a2;
    if (b == x)
        return 0;
    if (b < x)
    {
        result = fun(a1, b + 1, x);
        return result * 2 + 1;
    }
    else
    {
        result = fun(b - 1, a2, x);
        return result * 2;
    }
}

// int fun(int a1, int a2, int a3)
// {
//     int v3;     // ecx
//     int result; // rax

//     v3 = ((int)a3 - (int)a2) / 2 + a2;
//     if (v3 > (int)a1)
//         return 2 * (unsigned int)fun(a1, a2, (unsigned int)(v3 - 1));
//     result = 0LL;
//     if (v3 < (int)a1)
//         return 2 * (unsigned int)fun(a1, (unsigned int)(v3 + 1), a3) + 1;
//     return result;
// }

int main(void)

{
    printf("findx");
    for (int i = 0; i <= 0xe; i++)
    {
        if (fun(0xe, 0x0, i) == 0)
        {
            printf("%d\n", i);
            return 0;
        }
    }
    return 0;
}
