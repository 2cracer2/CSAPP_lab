#include <stdio.h>
typedef unsigned char *pointer;
//size_t meaningof unsigned int
void show_bytes(pointer start, size_t len)
{
    size_t i;
    for (i = 0; i < len; i++)
    {
        printf("%p\t0x%.2x\n", start + i, start[i]);
    }
    printf("\n");
}

int main(void)
{
    int a = 15213;
    printf("int a = 15213;\n");
    show_bytes((pointer)&a, sizeof(int));
}