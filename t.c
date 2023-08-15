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


int main(int argc, char *argv[]) {
    char *str = malloc(sizeof(char) * 999999999999999999);
    if (str == NULL) {
        perror("malloc");
        return EXIT_FAILURE; // Return the error code
    }

    // Continue with your code here

    free(str);

    return 0; // Return success
}