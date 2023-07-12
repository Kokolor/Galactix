#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <linux/fb.h>
#include "framebuffer.h"

static int fb_fd = -1;

static char *fb_ptr = MAP_FAILED;

static long screensize = 0;
static int xres = 0;
static int yres = 0;
static int bpp = 0;

int open_framebuffer()
{
    fb_fd = open("/dev/fb0", O_RDWR);
    if (fb_fd == -1)
    {
        return -1;
    }

    struct fb_var_screeninfo vinfo;
    if (ioctl(fb_fd, FBIOGET_VSCREENINFO, &vinfo) == -1)
    {
        close(fb_fd);
        return -1;
    }

    struct fb_fix_screeninfo finfo;
    if (ioctl(fb_fd, FBIOGET_FSCREENINFO, &finfo) == -1)
    {
        close(fb_fd);
        return -1;
    }

    xres = vinfo.xres;
    yres = vinfo.yres;
    bpp = vinfo.bits_per_pixel;

    screensize = finfo.line_length * yres;
    fb_ptr = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fb_fd, 0);
    if (fb_ptr == MAP_FAILED)
    {
        close(fb_fd);
        return -1;
    }

    return 0;
}

void draw_pixel(int x, int y, int color)
{
    if (fb_ptr != MAP_FAILED && x >= 0 && x < xres && y >= 0 && y < yres)
    {
        unsigned int offset = (x + y * xres) * (bpp / 8);

        *((unsigned int *)(fb_ptr + offset)) = color;
    }
}

void draw_rectangle(int x, int y, int width, int height, int color)
{
    int xend = x + width;
    int yend = y + height;

    for (int i = y; i < yend; i++)
    {
        for (int j = x; j < xend; j++)
        {
            draw_pixel(j, i, color);
        }
    }
}

void close_framebuffer()
{
    if (fb_ptr != MAP_FAILED)
    {
        munmap(fb_ptr, screensize);
    }
    if (fb_fd != -1)
    {
        close(fb_fd);
    }
}
