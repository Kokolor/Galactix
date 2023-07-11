#include <stdio.h>
#include <stdlib.h>
#include <sys/mount.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <source> <target>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *source = argv[1];
    const char *target = argv[2];

    if (mount(source, target, "ext4", MS_RELATIME, "") == -1)
    {
        perror("mount");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
