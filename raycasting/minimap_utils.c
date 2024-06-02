#include"../cub3d.h"

void draw_line(t_img *img, int x, int y, int end_x, int end_y)
{
    int dx;
    int dy;
    int sx;
    int sy;
    int err;
	int e2;

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
        my_mlx_pixel_put(img, x, y, 0x00000000);
        e2 = 2 * err;
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
	int i = 0;
	float angle;
	angle = game->player.rotation_angle;
	while (i < NUM_RAYS)
	{
		end_x = x + (int)(length*cos(angle));
		end_y = y + (int)(length*sin(angle));
    	draw_line(img, x, y, end_x, end_y);
		i++;
	}
}

void draw_square(t_game *game, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	while (i < MINI_CUBE_SIZE)
	{
		j = 0;
		while (j < MINI_CUBE_SIZE)
		{
			my_mlx_pixel_put(&game->mlx.minimap_image, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void draw_player(t_img *img, int x, int y, int color, t_game *game)
{
	int i;
	int j;
	int r;

	r = MINI_CUBE_SIZE / 6;
	i = -r;
	while (i < r)
	{
		j = -r;
		while (j < r)
		{
			if (i * i + j * j <= r * r)
				my_mlx_pixel_put(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
	draw_direction(img, x, y, game, MINI_CUBE_SIZE);
}