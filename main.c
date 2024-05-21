#include"cub3d.h"

int	main()
{
	t_game game;
	t_mlx	mlx;
	t_input input;

	input = parsing("map.cub");
//	read_matrix(input);
	ft_connect(&mlx);
	get_images(&mlx, &input);
	game = init_game(mlx, input);
//	draw_minimap(&game);
 	cast_all_rays(&game);
	mlx_key_hook(mlx.window, &ft_close, &mlx);
 	mlx_hook(mlx.window, 17,0, &ft_close2, &mlx);
	mlx_hook(mlx.window, 2, 0, &handle_keys, &game);
 	mlx_loop(mlx.connect);
	return (0);
}

int get_cube_size(t_game game)
{
	float scale_x;
	float scale_y;
	float cube_size;

	scale_x = (float)WIDTH / (float)game.map_width;
	scale_y = (float)HEIGHT / (float)game.map_height;
	if (scale_x < scale_y)
		cube_size = scale_x;
	else
		cube_size = scale_y;
	return ((int)cube_size);
}

t_game init_game(t_mlx mlx, t_input input)
{
	t_game game;

	game.mlx = mlx;
	game.map = input.map;
	game.map_height = input.height;
	game.map_width = input.width;
	game.c_color = input.c_color;
	game.f_color = input.f_color;
	game.cube_size = get_cube_size(game);
	game.player.map_x = input.pos_x;
	game.player.map_y = input.pos_y;
	game.player.x = (input.pos_x * game.cube_size) + game.cube_size / 2;
	game.player.y = (input.pos_y * game.cube_size) + game.cube_size / 2;
	game.player.width = game.cube_size / 3;
	game.player.height = game.cube_size / 3;
	game.player.turn_direction = 0;
	game.player.x_walk_dir = 0;
	game.player.y_walk_dir = 0;
	game.player.walk_speed = game.cube_size / 2;
	game.player.turn_speed = deg_to_rad(45);
	game.player.rotation_angle = deg_to_rad(input.direction);
	return (game);
}

