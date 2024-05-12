#include"../cub3d.h"

void draw_player(t_img *img, int x, int y, int color, t_game *game)
{
	int radius;
    int centerX;
    int centerY;
	int i;
	int j;
    radius = MINI_CUBE / 3;
	centerX = x + (MINI_CUBE / 2);
	centerY = y + (MINI_CUBE / 2);

	j = -radius;
    while (j <= radius)
	{
		i = -radius;
		while (i <= radius)
		{
			if (i * i + j * j <= radius * radius)
                my_mlx_pixel_put(img, (centerX + i), (centerY + j), color);
			i++;
		}
		j++;
	}
	draw_direction(img, centerX, centerY, game, MINI_CUBE);
}
void draw_line(t_img *img, int x, int y, int end_x, int end_y)
{
    int dx;
    int dy;
    int sx;
    int sy;
    int err;

	dx = abs(end_x - x);
	dy = abs(end_y - y);
	err = dx - dy;
	if (end_x > x)
		sx = 1;
	else
		sx = -1;
	if (end_y > y)
		sy = 1;
	else	
		sy = -1;
    while (x != end_x || y != end_y)
	{
        my_mlx_pixel_put(img, x, y, 0x00FF0000);
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }
}

void draw_direction(t_img *img, int x, int y, t_game *game, int length)
{
    int end_x;
    int end_y;

	end_x = x + (int)(length * game->player.x_dir);
	end_y = y + (int)(length * game->player.y_dir); // - because the Y axe is down in screen
    draw_line(img, x, y, end_x, end_y);
}