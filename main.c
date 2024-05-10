
#include"cub3d.h"

void get_images(t_mlx *mlx, t_input *input)
{
	mlx->north_wall_image = get_image_from_xpm(mlx->connect, input->no);
	mlx->south_wall_image = get_image_from_xpm(mlx->connect, input->so);
	mlx->east_wall_image = get_image_from_xpm(mlx->connect, input->ea);
	mlx->west_wall_image = get_image_from_xpm(mlx->connect, input->we);
}

t_img  get_image_from_xpm(void *mlx_ptr, char *path_xpm)
{
  t_img img;

  img.ptr = mlx_xpm_file_to_image(mlx_ptr, path_xpm, &img.width, &img.height);
  if (!img.ptr)
  {
	printf("The xpm file is invalid\n");
	// to free the memory
	exit(0);
  }
  img.addr = mlx_get_data_addr(img.ptr, &img.bpp, &img.line_len, &img.endian);
  return (img);
}
void read_matrix(t_input input)
{
	int i = 0;
	while(i < input.H)
	{
		if (input.map[i])
		printf("\n");
		i++;
	}
	printf("-> H=%d, W=%d, X= %d ,Y= %d, direction = %f\n", input.H,input.W,input.pos_x,input.pos_y,input.direction);
}

int check_argument(int ac, char **av)
{
	int fd;

	if (ac != 2)
	{
		printf("Error\n");
		return (0);
	}
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
	{
		printf("Error\n");
		return (0);
	}
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		printf("Error\n");
		return (0);
	}
	close(fd);
	return (1);
}

int	main(int ac, char **av)
{
	// t_game game;
	// t_mlx	mlx;
	t_input input;
	if (!check_argument(ac, av) || !parsing(av[1],&input))
	{
		system("leaks cub3d");
		return (1);
	}
		read_matrix(input);
	
// add parsing here and give in input struct
// 	ft_connect(&mlx);
// 	get_images(&mlx, &input);
// 	game = init_game(mlx, input);
// //	draw_set(&mlx);
// 	mlx_put_image_to_window(mlx.connect, mlx.window, mlx.image.ptr, 0, 0);
// 	mlx_hook(mlx.window, 2, 1L << 2, &ft_close, &mlx);
// 	mlx_hook(mlx.window, 17, 1L << 17, &ft_close2, &mlx);
// //	mlx_key_hook(mlx.window, &handle_keys, &mlx);
// //	mlx_mouse_hook(mlx.window, &handle_mouse, &mlx);
// 	mlx_loop(mlx.connect);
	return (0);
}

t_game init_game(t_mlx mlx, t_input input)
{
	t_game game;

	game.mlx = mlx;
	game.player_pos.x = input.pos_x;
	game.player_pos.y = input.pos_y;
	game.player_direction = input.direction;
	game.map = input.map;
	game.nbr_lines = input.H;
	game.c_color = input.c_color;
	game.f_color = input.f_color;
	game.alpha_angle = 0;
	game.projection_plane_center.x = WIDTH / 2;
	game.projection_plane_center.y = HEIGHT / 2;
	game.distance_projection_plane = (game.projection_plane_center.x / tan(FOV / 2));
	game.angle_between_rays = FOV / WIDTH;
	game.rays_per_fov = WIDTH;
	game.angle_ray = game.player_direction - (FOV / 2);
	return (game);
}

