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

void draw_minimap(t_game *game)
{
	int start_x;
	int start_y;
	int x;
	int y;
	
	get_start_point(&start_x, &start_y, game->player_map_x, game->player_map_y);
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