#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *str = getenv("HOME");
	printf("%s\n", str);
}