#include"../cub3d.h"

void initialize_line(t_point *delta, t_point *signe, t_point start, t_point end)
{
	delta->x = abs((int)(end.x - start.x));
	delta->y = abs((int)(end.y - start.y));
	signe->x = 1;
	signe->y = 1;
	if ((int)end.x <= (int)start.x)
		signe->x = -1;
	if ((int)end.y <= (int)start.y)
		signe->y = -1;
}

// void draw_line(t_img *img, t_point start, t_point end)
// {
// 	t_point delta;
// 	t_point signe;
// 	int x;
// 	int y;
//     int err;
// 	int e2;

// 	initialize_line(&delta, &signe, start, end);
// 	err = (int)(delta.x - delta.y);
//     while ((int)start.x != (int)end.x || (int)start.y != (int)end.y)
// 	{
// 		x = (int)start.x;
// 		y = (int)start.y;
//         my_mlx_pixel_put(img, x,y, 0x00000000);
//         e2 = 2 * err;
//         if (e2 > (int)(-delta.y))
// 		{
//             err -= (int)delta.y;
//             start.x += (int)signe.x;
//         }
//         if (e2 < (int)delta.x)
// 		{
//             err += (int)delta.x;
//             start.y += (int)signe.y;
//         }
//     }
// }


// this is valid  with no norminette :
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
    draw_line(&game->mlx.minimap_image, player.x, player.y, end.x, end.y);
}
