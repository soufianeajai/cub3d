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
void draw_minimap(t_mlx *mlx, t_game *game, int player_y, int player_x)
{
	int start_x;
	int start_y;
	int x;
	int y;
	
	get_start_point(&start_x, &start_y, player_x, player_y);
	x = start_x;
	y = start_y;
	while ((y <= (MINI_MAP_HEIGHT/2 + player_y)) && y < game->map_height)
	{
		x = start_x;
		while ((x <= (MINI_MAP_WIDTH/2 + player_x)) && x < game->map_width)
		{
			if (game->map[y][x] == '0')
 				draw_rectangle(&mlx->minimap_image, (x - start_x)*MINI_CUBE, (y - start_y)*MINI_CUBE, 0X00FFFFFF);
			if (game->map[y][x] == '1')
 				draw_rectangle(&mlx->minimap_image, (x - start_x)*MINI_CUBE, (y - start_y)*MINI_CUBE, 0X000000FF);
			if (game->map[y][x] == '2')
 				draw_rectangle(&mlx->minimap_image, (x - start_x)*MINI_CUBE, (y - start_y)*MINI_CUBE, 0X0000FF00);
			if (game->map[y][x] == 'Z')
 				draw_rectangle(&mlx->minimap_image, (x - start_x)*MINI_CUBE, (y - start_y)*MINI_CUBE, 0X00FF0000);
			x++;
		}
		y++;
	}

	mlx_put_image_to_window(mlx->connect, mlx->window, mlx->minimap_image.ptr, WIDTH/2, HEIGHT/2);
}