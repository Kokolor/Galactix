#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

extern struct fb_var_screeninfo vinfo;
extern struct fb_fix_screeninfo finfo;
extern char *fbp;
extern int fbfd;
extern long screensize;

struct Color
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

void init_framebuffer();
int draw_rectangle(int x, int y, int w, int h, int opacity, struct Color color);

#endif