#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/mount.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <errno.h>
#include "shell/shell.h"
#include "framebuffer/framebuffer.h"

int main()
{
    init_framebuffer();
    init_shell();

    while (1);

    munmap(fbp, screensize);
    close(fbfd);

    return 0;
}
