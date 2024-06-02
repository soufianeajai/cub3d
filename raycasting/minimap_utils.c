#include"../cub3d.h"

void initialize_line(t_point *delta, t_point *signe, t_point start, t_point end)
{
	delta->x = abs((int)(end.x - start.x));
	delta->y = abs((int)(end.y - start.y));
	signe->x = 1;
	signe->y = 1;
	if (end.x <= start.x)
		signe->x = -1;
	if (end.y <= start.y)
		signe->y = -1;
}

void draw_line(t_img *img, t_point start, t_point end)
{
	t_point delta;
	t_point signe;
    int err;
	int e2;

	initialize_line(&delta, &signe, start, end);
	err = (int)(delta.x - delta.y);
    while (start.x != end.x || start.y != end.y)
	{
        my_mlx_pixel_put(img, (int)start.x, (int)start.y, 0x00000000);
        e2 = 2 * err;
        if (e2 > (int)-delta.y)
		{
            err -= (int)delta.y;
            start.x += signe.x;
        }
        if (e2 < (int)delta.x)
		{
            err += (int)delta.x;
            start.y += signe.y;
        }
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

void draw_player(t_game *game, t_point player)
{
	int i;
	int j;
	int r;
	t_point end;

	r = MINI_CUBE_SIZE / 6;
	i = -r;
	while (i < r)
	{
		j = -r;
		while (j < r)
		{
			if (i * i + j * j <= r * r)
				my_mlx_pixel_put(&game->mlx.minimap_image, player.x + i, player.y + j, 0x00000000);
			j++;
		}
		i++;
	}
	end.x = player.x + (int)(MINI_CUBE_SIZE*cos(game->player.rotation_angle));
	end.y = player.y + (int)(MINI_CUBE_SIZE*sin(game->player.rotation_angle));
    draw_line(&game->mlx.minimap_image, player, end);
}
