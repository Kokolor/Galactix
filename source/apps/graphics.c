#include <stdio.h>
#include <framebuffer.h>

int main()
{
    if (open_framebuffer() == -1)
    {
        printf("Failed to open framebuffer.\n");
        return 1;
    }

    int resolution_x = 800;
    int resolution_y = 600;

    for (int x = 0; x < resolution_x; x++)
    {
        for (int y = 0; y < resolution_y; y++)
        {
            int red = (255 * (resolution_x - x)) / resolution_x;
            int blue = (255 * y) / resolution_y;
            int color = (red << 16) | blue;

            draw_pixel(x, y, color);
        }
    }

    close_framebuffer();

    return 0;
}
