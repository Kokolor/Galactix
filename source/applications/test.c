#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("Hello, from C program!\n");

    for (int i = 0; i < argc; i++)
    {
        printf("Argument %d: %s\n", i, argv[i]);
    }

    return 0;
}
