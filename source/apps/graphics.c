#include <stdio.h>
#include <framebuffer.h>

int main()
{
    if (open_framebuffer() == -1)
    {
        printf("Failed to open framebuffer.\n");
        return 1;
    }

    for (int x = 100; x < 200; x++)
    {
        for (int y = 100; y < 200; y++)
        {
            draw_pixel(x, y, 0x00FF00);
        }
    }

    close_framebuffer();

    return 0;
}
