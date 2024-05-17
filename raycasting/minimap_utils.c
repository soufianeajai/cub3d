#include"../cub3d.h"

void draw_player(t_img *img, int x, int y, int color, t_game *game)
{
	int i;
	int j;
	int r;

	r = game->cube_size / 4;
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
	draw_direction(img, x, y, game, r*2);
}



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

void draw_direction(t_img *img, int x, int y, t_game *game, float length)
{
    int end_x;
    int end_y;

	end_x = x + (int)(length * cos(game->player.rotation_angle));
	end_y = y + (int)(length * sin(game->player.rotation_angle)); // - because the Y axe is down in screen
    draw_line(img, x, y, end_x, end_y);
}

void draw_square(t_game *game, int x, int y, int color)
{
	int i = 1;
	int j = 1;

	while (i < game->cube_size)
	{
		j = 1;
		while (j < game->cube_size)
		{
			my_mlx_pixel_put(&game->mlx.image, x + i, y + j, color);
			j++;
		}
		i++;
	}
}
// void draw_mini_square(t_game *game, int x, int y, int color)
// {
// 	int i = 1;
// 	int j = 1;

// 	while (i < MINI_CUBE_SIZE)
// 	{
// 		j = 1;
// 		while (j < MINI_CUBE_SIZE)
// 		{
// 			my_mlx_pixel_put(&game->mlx.minimap_image, x + i, y + j, color);
// 			j++;
// 		}
// 		i++;
// 	}
// }
void draw_mini_square(t_game *game, int x, int y, int color)
{
	// Drawing a square on the mini-map at (x, y) with the specified color
	int i;
	int j;

	i = 1;
	while (i < MINI_CUBE_SIZE)
	{
		j = 1;
		while (j < MINI_CUBE_SIZE)
		{
			my_mlx_pixel_put(&game->mlx.minimap_image, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void draw_player_mini(t_img *img, int x, int y, int color, t_game *game)
{
	int i;
	int j;
	int r;

	r = MINI_CUBE_SIZE / 4;
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
	draw_direction(img, x, y, game, r*2.5);
}