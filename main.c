#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>


int main(void)
{
	const char* paths[] = {"hello", "world", "!"};

	int i = 0;
	while (paths[i])
	{
		printf("%s\n", paths[i]);
		i++;
	}
}