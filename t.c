#include <stdio.h>
#include <unistd.h>


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Get the value of $PATH from the environment
    char *path = getenv("PATH");
    
    if (path == NULL) {
        fprintf(stderr, "Unable to retrieve the value of $PATH.\n");
        return 1;
    }

    // Print the $PATH value
    printf("%s\n", path);

    return 0;
}
