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

int main(void)

{
    printf("findx");
    for (int i = 0; i <= 0xe; i++)
    {
        if (fun(0xe, 0, i) == 0)
        {
            printf("%d\n", i);
            return 0;
        }
    }
    return 0;
}
