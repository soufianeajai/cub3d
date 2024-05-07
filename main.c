#include"cub3d.h"

void draw(t_mlx *mlx)
{
	int x = 0;
	int y = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			copy_image(&mlx->image, mlx->east_wall_image, x, y);
			y += SIZE_CUBE;
		}
		x += SIZE_CUBE;
	}
	mlx_put_image_to_window(mlx->connect, mlx->window, mlx->image.ptr, 0, 0);
}
int	main()
{
	t_game game;
	t_mlx	mlx;
	t_input input;

	input = parsing("map.cub");
	input.map[11][26] = '0';
	input.direction = deg_to_rad(90);
//	read_matrix(input);
	ft_connect(&mlx);
	game = init_game(mlx, input);
	get_images(&mlx, &input);
	draw(&mlx);
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
	game.player_pos.x = input.pos_x;
	game.player_pos.y = input.pos_y;
	game.map = input.map;
	game.c_color = input.c_color;
	game.f_color = input.f_color;
	game.alpha_angle = 0;
	game.projection_plane_center.x = WIDTH / 2;
	game.projection_plane_center.y = HEIGHT / 2;
	game.distance_projection_plane = (game.projection_plane_center.x / tan(FOV / 2));
	game.angle_between_rays = FOV / WIDTH;
	game.rays_per_fov = WIDTH;
	return (game);
}

