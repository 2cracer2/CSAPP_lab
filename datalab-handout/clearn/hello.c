#include <stdio.h>
#include <stdbool.h>
int main(void)
{
	printf("Hello World\n");
	printf("%d", 4 + 6 % 2);
	printf("Hello World\n");
	printf("Hello World\a");
	printf("%6.2f", 0.2 + 0.3);
	bool t = (0.1 + 0.2 == 0.3);
	if (t)
		printf("Everything is OK.\n");
	return 0;
}
