#include <stdio.h>
#include <unistd.h>


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define BROWN "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define GRAY "\033[0;37m"
# define DARK_GRAY "\033[1;30m"
# define LIGHT_RED "\033[1;31m"
# define LIGHT_GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define LIGHT_BLUE "\033[1;34m"
# define LIGHT_PURPLE "\033[1;35m"
# define LIGHT_CYAN "\033[1;36m"
# define WHITE "\033[1;37m"
// # define PINK "\033[38;5;206m"
# define PINK "\033[1;38;5;206m"
# define PINK2 "\033[1;35m"
# define RESET "\033[0m"

# define COL1 "\033[30;1m"
# define COL2 "\033[31;1m"
# define COL3 "\033[32;1m"
# define COL4 "\033[33;1m"
# define COL5 "\033[34;1m"
# define COL6 "\033[35;1m"
# define COL7 "\033[36;1m"
# define COL8 "\033[37;1m"

char	*str_join(const char *s1, const char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = calloc(sizeof(char), (strlen(s1) + strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		j++;
		i++;
	}
	return (str);
}


int main(int argc, char *argv[]) {
	// int pid = fork();
	// if (pid == -1) {
	// 	printf("error\n");
	// 	exit(1);
	// }

	// int i = 0;
	// if (pid == 0) {
	// 	while (1) {
	// 		printf("i = %d\n", i);
	// 		usleep(50000);
	// 		i++;
	// 	}
	// } else {
	// 	wait(NULL);
	// }
	// return 0;
	// char * str = "\033[0;35mHello";
	// printf("%s\n", str);
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		printf("getcwd() error\n");
		exit(EXIT_FAILURE);
	}
	char *dir = strrchr(cwd, '/') + 1;
	// printf("%s%s%s", COL2, "Ms ", RESET);
	// printf("%s➜ %s", PINK, RESET);
	// printf("%s%s%s", LIGHT_CYAN, dir, RESET);
	// printf("%s$%s ", LIGHT_BLUE, RESET);
	char *str = "\033[31;1mMS \033[1;38;5;206m➜ \033[1;36m";
	char *end = "\033[1;34m$ \033[0m";
	str = str_join(str, dir);
	str = str_join(str, end);
	printf("%s\n", str);
	// printf("%s%s%s", COL2, "Ms ", RESET);
	// printf("%s➜ %s", PINK, RESET);
	// printf("%s%s%s", LIGHT_CYAN, dir, RESET);
	// printf("%s$%s ", LIGHT_BLUE, RESET);
}
