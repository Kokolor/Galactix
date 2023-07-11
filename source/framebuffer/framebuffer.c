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
#include "framebuffer.h"

struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;
char *fbp;
int fbfd;
long screensize;

void init_framebuffer()
{
    fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1)
    {
        perror("Error occurred while opening /dev/fb0.");
        while (1)
            ;
    }

    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo))
    {
        perror("Error occurred while retrieving fixed screen information.");
        while (1)
            ;
    }
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo))
    {
        perror("Error occurred while retrieving variable screen information.");
        while (1)
            ;
    }

    screensize = vinfo.yres_virtual * finfo.line_length;

    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, (off_t)0);

    if ((intptr_t)fbp == -1)
    {
        perror("Error occurred during memory mapping.");
        while (1)
            ;
    }

    printf("Framebuffer Informations:\n");
    printf("   Framebuffer device: %s\n", "/dev/fb0");
    printf("   Resolution: %dx%d\n", vinfo.xres, vinfo.yres);
    printf("   Virtual Resolution: %dx%d\n", vinfo.xres_virtual, vinfo.yres_virtual);
    printf("   Bits per pixel: %d\n", vinfo.bits_per_pixel);
    printf("   Line length: %d\n", finfo.line_length);
}

int draw_rectangle(int x, int y, int w, int h, int opacity, struct Color color)
{
    if (x < 0 || y < 0 || w < 0 || h < 0)
    {
        return -1;
    }
    int i, j;
    for (i = x; i < x + w; i++)
    {
        for (j = y; j < y + h; j++)
        {
            long location = (i + vinfo.xoffset) * (vinfo.bits_per_pixel / 8) +
                            (j + vinfo.yoffset) * finfo.line_length;

            *(fbp + location) = color.blue;      // Blue
            *(fbp + location + 1) = color.green; // Green
            *(fbp + location + 2) = color.red;   // Red
            *(fbp + location + 3) = opacity;
        }
    }

    return 0;
}
