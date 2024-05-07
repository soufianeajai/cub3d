#include"cub3d.h"

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

void draw_minimap(t_mlx *mlx, t_game *game)
{
	int x = 0;
	int y = 0;
	while ((y < MINI_HEIGHT / MINI_CUBE) && y < game->map_height)
	{
		x = 0;
		while ((x < MINI_WIDTH / MINI_CUBE) && x < game->map_width)
		{
			if (game->map[y][x] == '1')
				draw_rectangle(&mlx->minimap_image, x * MINI_CUBE, y * MINI_CUBE, 0x00FFFFFF);
			if (game->map[y][x] == '2')
			 	draw_rectangle(&mlx->minimap_image, x * MINI_CUBE, y * MINI_CUBE, 0x000000F1);
			if (game->map[y][x] == '0')
				draw_rectangle(&mlx->minimap_image, x * MINI_CUBE, y * MINI_CUBE, 0x00000000);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->connect, mlx->window, mlx->minimap_image.ptr, 0, HEIGHT - MINI_HEIGHT);
}
int	main()
{
	t_game game;
	t_mlx	mlx;
	t_input input;

	input = parsing("map.cub");
	input.map[11][26] = '0';
	input.direction = deg_to_rad(90);
	read_matrix(input);
	ft_connect(&mlx);
	game = init_game(mlx, input);
	get_images(&mlx, &input);
	draw_minimap(&mlx, &game);
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

