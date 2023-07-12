#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

int open_framebuffer();
void draw_pixel(int x, int y, int color);
void close_framebuffer();

#endif
