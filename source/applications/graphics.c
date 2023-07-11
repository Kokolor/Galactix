#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../framebuffer/framebuffer.h"

int main()
{
    printf("1!\n");
    init_framebuffer();

    struct Color color = {0, 255, 75};
    draw_rectangle(0, 0, 145, 145, 100, color);
    draw_rectangle(165, 165, 145, 145, 100, color);
    printf("2!\n");

    return 0;
}
