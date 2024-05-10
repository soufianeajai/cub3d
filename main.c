#include"cub3d.h"

int	main()
{
	t_game game;
	t_mlx	mlx;
	t_input input;

	input = parsing("map.cub");
	input.direction = deg_to_rad(input.direction);
	printf("%f\n", input.direction);
	read_matrix(input);
	ft_connect(&mlx);
	game = init_game(mlx, input);
	get_images(&mlx, &input);
	draw_minimap(&game);
 	mlx_key_hook(mlx.window, &ft_close, &mlx);
 	mlx_hook(mlx.window, 17,0, &ft_close2, &mlx);
	mlx_hook(mlx.window, 2, 0, &handle_keys, &game);
 	mlx_loop(mlx.connect);
	return (0);
}

t_game init_game(t_mlx mlx, t_input input)
{
	t_game game;

	game.mlx = mlx;
	game.player.x_dir = cos(input.direction);
	game.player.y_dir = sin(input.direction);
	game.player.direction = input.direction;
	game.player.x = input.pos_x;
	game.player.y = input.pos_y;
	game.map = input.map;
	game.map_height = input.height;
	game.map_width = input.width;
	game.c_color = input.c_color;
	game.f_color = input.f_color;
	return (game);
}

