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