#include"../cub3d.h"

void get_start_point(int *start_x, int *start_y, int player_x, int player_y)
{
	int x;
	int y;
	
	y = 0;
	x = 0;
	while (y < player_y - (MINI_MAP_HEIGHT/ 2))
		y++;
	while (x < player_x - (MINI_MAP_WIDTH / 2))
		x++;
	*start_x = x;
	*start_y = y;
}

void draw_rectangle(t_img *img, int x, int y, int color)
{
	int i = 1;
	int j = 1;

	while (i < MINI_CUBE)
	{
		j = 1;
		while (j < MINI_CUBE)
		{
			my_mlx_pixel_put(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

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
                my_mlx_pixel_put(img, centerX + i, centerY + j, color);
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
        my_mlx_pixel_put(img, x, y, 0x00000000);
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
	end_y = y - (int)(length * game->player.y_dir); // - because the Y axe is down in screen
    draw_line(img, x, y, end_x, end_y);
}

void draw_minimap(t_game *game)
{
	int start_x;
	int start_y;
	int x;
	int y;
	
	get_start_point(&start_x, &start_y, game->player.x, game->player.y);
	x = start_x;
	y = start_y;
	while ((y <= (MINI_MAP_HEIGHT/2 + game->player.y)) && y < game->map_height)
	{
		x = start_x;
		while ((x <= (MINI_MAP_WIDTH/2 + game->player.x)) && x < game->map_width)
		{
			if (game->map[y][x] == '0')
 				draw_rectangle(&game->mlx.minimap_image, (x - start_x)*MINI_CUBE, (y - start_y)*MINI_CUBE, 0X00FFFFFF);
			if (game->map[y][x] == '1')
 				draw_rectangle(&game->mlx.minimap_image, (x - start_x)*MINI_CUBE, (y - start_y)*MINI_CUBE, 0X000000FF);
			x++;
		}
		y++;
	}
	draw_player(&game->mlx.minimap_image, (game->player.x - start_x)*MINI_CUBE, (game->player.y- start_y)*MINI_CUBE, 0X00FF0000, game);
	mlx_put_image_to_window(game->mlx.connect, game->mlx.window, game->mlx.minimap_image.ptr, 0, HEIGHT - MINI_HEIGHT);
}