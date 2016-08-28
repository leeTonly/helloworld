#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void printUsage(void)
{
    printf("Usage: pwd");
}

int main(int argc, char const *argv[])
{
    char path[1024];

    memset(path, 0x00, sizeof(path));

    if(argc != 1) {
        printUsage();
        return -1;
    }

    getcwd(path, sizeof(path));

    printf("%s\n", path);

    return 0;
}
~            