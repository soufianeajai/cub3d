#include"cub3d.h"

// void draw_minimap(t_mlx *mlx, t_game *game, int player_x, int player_y)
// {
// 	int start_x;
// 	int start_y;
// 	int x = 0;
// 	int y = 0;
	
// 	get_start_point(&start_x, &start_y, player_x, player_y);
// 	x = start_x;
// 	// /printf("start_x %d --- | player_x %d\n", start_x, player_x);
// 	// printf("start_y %d --- | player_y %d\n", start_y, player_y);
// 	// printf("++++ %d\n", MINI_HEIGHT / MINI_CUBE);
// 	// printf("---- %d\n", MINI_WIDTH / MINI_CUBE);
// 	while (x < (MINI_HEIGHT / MINI_CUBE))
// 	{
// 		y = start_y;
// 		while (y < (MINI_WIDTH / MINI_CUBE) + start_y)
// 		{
// 			if (game->map[x][y] == '0')
// 				draw_rectangle(&mlx->minimap_image, x, y, 0x00FFFFFF);
// 			if (game->map[x][y] == '1')
// 				draw_rectangle(&mlx->minimap_image, x, y, 0x00F00FFF);
// 			if (game->map[x][y] == '2')
// 				draw_rectangle(&mlx->minimap_image, x, y, 0x00FF0000);
// 			if (game->map[x][y] == 'Z')
// 				draw_rectangle(&mlx->minimap_image, x, y, 0x000000FF);
// 			y++;
// 		}
// 		x++;
// 	}

// 	mlx_put_image_to_window(mlx->connect, mlx->window, mlx->minimap_image.ptr, WIDTH/2, HEIGHT/2);
// }


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
	int x = 0;
	int y = 0;
	
	get_start_point(&start_x, &start_y, player_x, player_y);
	x = start_x;
	y = start_y;
	// printf("MINI_MAP_HEIGHT %d\n", MINI_MAP_HEIGHT);
	// printf("MINI_MAP_WIDTH %d\n", MINI_MAP_WIDTH);
	printf("start_x %d --- | player_x %d   |  final_x %d\n", start_x, player_x, MINI_MAP_WIDTH/2 + player_x);
	printf("start_y %d --- | player_y %d |  final_y %d\n", start_y, player_y, MINI_MAP_HEIGHT/2 + player_y);

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
			if (game->map[y][x] == '0')
 				printf("0");
			if (game->map[y][x] == '1')
 				printf("1");
			if (game->map[y][x] == '2')
 				printf("2");
			if (game->map[y][x] == 'Z')
 				printf("Z");
			x++;
			// if (x > start_x + 1)
			//   	break;
		}
		printf("\n");
//		printf("y = %d | (MINI_MAP_H/2 + player_y + 1) = %d\n", y, (MINI_MAP_HEIGHT/2 + player_y + 1));
//		break;
		y++;
	}

	mlx_put_image_to_window(mlx->connect, mlx->window, mlx->minimap_image.ptr, WIDTH/2, HEIGHT/2);
}
int	main()
{
	t_game game;
	t_mlx	mlx;
	t_input input;

	input = parsing("map.cub");
	input.map[11][26] = '0';
	input.direction = deg_to_rad(90);
	input.map[9][10] = 'Z';
	read_matrix(input);
	ft_connect(&mlx);
	game = init_game(mlx, input);
	get_images(&mlx, &input);
	draw_minimap(&mlx, &game, 9, 10);
 	mlx_hook(mlx.window, 2, 0, &ft_close, &mlx);
 	mlx_hook(mlx.window, 17,0, &ft_close2, &mlx);
	mlx_key_hook(mlx.window, &handle_keys, &mlx);
 	mlx_loop(mlx.connect);
	return (0);
}

t_game init_game(t_mlx mlx, t_input input)
{
	t_game game;

	game.mlx = mlx;
	game.player.x = input.pos_x;
	game.player.y = input.pos_y;
	game.map = input.map;
	game.map_height = input.height;
	game.map_width = input.width;
	game.c_color = input.c_color;
	game.f_color = input.f_color;
	return (game);
}

