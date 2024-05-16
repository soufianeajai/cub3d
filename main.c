#include"cub3d.h"

int	main()
{
//	t_game game;
	t_mlx	mlx;
	t_input input;

	input = parsing("map.cub");
	input.direction = deg_to_rad(input.direction);
	read_matrix(input);
	ft_connect(&mlx);
//	game = init_game(mlx, input);
	get_images(&mlx, &input);
//	draw_minimap(&game);
 	mlx_key_hook(mlx.window, &ft_close, &mlx);
 	mlx_hook(mlx.window, 17,0, &ft_close2, &mlx);
//	mlx_hook(mlx.window, 2, 0, &handle_keys, &game);
 	mlx_loop(mlx.connect);
	return (0);
}

t_game init_game(t_mlx mlx, t_input input)
{
	t_game game;

	game.mlx = mlx;
	game.player.rotation_angle = input.direction;
	game.player_map_x = input.pos_x;
	game.player_map_y = input.pos_y;
	// game.player.x = input.pos_x * SIZE_CUBE;
	// game.player.y = input.pos_y * SIZE_CUBE;
	game.mini_x = 0;
	game.mini_y = 0;
	game.map = input.map;
	game.map_height = input.height;
	game.map_width = input.width;
	game.c_color = input.c_color;
	game.f_color = input.f_color;
	return (game);
}

