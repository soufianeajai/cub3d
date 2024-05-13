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
// !!!!!! i need to use game->player.x instead of game->player_map_x in all the draw_minimap function to handle moves 
void draw_minimap(t_game *game)
{
	int start_x;
	int start_y;
	int x = 0;
	int y = 0;
	get_start_point(&start_x, &start_y, game->player_map_x, game->player_map_y);
	printf("start x = %d | start y = %d\n", start_x, start_y);
	// printf("end x = %d | end y = %d", end_x, end_y);
	while (y < MINI_HEIGHT && (y/MINI_CUBE + start_y) < game->map_height)
	{
		x = 0;
		while (x < MINI_WIDTH && (x/MINI_CUBE + start_x) < game->map_width)
		{
			if (game->map[y/MINI_CUBE + start_y][x/MINI_CUBE + start_x] == '0')
 				draw_rectangle(&game->mlx.minimap_image, x, y, 0X00FFFFFF);
			if (game->map[y/MINI_CUBE + start_y][x/MINI_CUBE + start_x] == '1')
 				draw_rectangle(&game->mlx.minimap_image, x, y, 0X000000FF);
			x += MINI_CUBE;
		}
		y += MINI_CUBE;
	}
	draw_player(&game->mlx.minimap_image, (game->player_map_x - start_x)*MINI_CUBE, (game->player_map_y- start_y)*MINI_CUBE, 0X00FF0000, game);
	mlx_put_image_to_window(game->mlx.connect, game->mlx.window, game->mlx.minimap_image.ptr, 0, HEIGHT - MINI_HEIGHT);
}

void update_minimap(t_game *game)
{
	int y = (game->player.y / MINI_CUBE) - (MINI_HEIGHT / 2);
	int x = (game->player.x / MINI_CUBE) - (MINI_WIDTH / 2);

	if (y < 0)
		y = 0;
	if (x < 0)
		x = 0;
		while (y < MINI_HEIGHT)
	{
		x = 0;
		while (x < MINI_WIDTH)
		{
			if (game->map[y/MINI_CUBE][x/MINI_CUBE] == '0')
 				draw_rectangle(&game->mlx.minimap_image, x, y, 0X00FFFFFF);
			if (game->map[y/MINI_CUBE][x/MINI_CUBE] == '1')
 				draw_rectangle(&game->mlx.minimap_image, x, y, 0X000000FF);
			x += MINI_CUBE;
		}
		y += MINI_CUBE;
	}
	draw_player(&game->mlx.minimap_image, MINI_WIDTH/2, MINI_HEIGHT/2, 0X00FF0000, game);
	mlx_put_image_to_window(game->mlx.connect, game->mlx.window, game->mlx.minimap_image.ptr, 0, HEIGHT - MINI_HEIGHT);
}