#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>


int main(void)
{
    char *str = getenv("HOME");
	printf("%s\n", str);
}