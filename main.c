
#include"cub3d.h"
#include <string.h>
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
	printf("The xpm file is invalid %s\n", path_xpm);
	// to free the memory
	exit(0);
  }
  img.addr = mlx_get_data_addr(img.ptr, &img.bpp, &img.line_len, &img.endian);
  return (img);
}
void read_matrix(t_input input)
{
	int i = 0;
	while(i < input.nbr_lines)
	{
		printf("%s", input.map[i]);
		printf("\n");
		i++;
	}
}
void copy_image(t_img *image, t_img wall_image, int x, int y)
{
	int i = 0;
	int j = 0;
	int color;
	while (i < wall_image.width)
	{
		j = 0;
		while (j < wall_image.height)
		{
			color = *(int *)(wall_image.addr + (j * wall_image.line_len + i * (wall_image.bpp / 8)));
			my_mlx_pixel_put(image, x + i, y + j, color);
			j++;
		}
		i++;
	}
}
void draw_set(t_mlx *mlx)
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
//	read_matrix(input);
	ft_connect(&mlx);
	game = init_game(mlx, input);
	get_images(&mlx, &input);
	draw_set(&mlx);
 	// mlx_put_image_to_window(mlx.connect, mlx.window, mlx.north_wall_image.ptr, 0, 0);
	// mlx_put_image_to_window(mlx.connect, mlx.window, mlx.south_wall_image.ptr, SIZE_CUBE, 0);
 	// mlx_put_image_to_window(mlx.connect, mlx.window, mlx.east_wall_image.ptr, 2*SIZE_CUBE, 0);
 	// mlx_put_image_to_window(mlx.connect, mlx.window, mlx.west_wall_image.ptr, 3*SIZE_CUBE, 0);
 	mlx_hook(mlx.window, 2, 1L << 2, &ft_close, &mlx);
 	mlx_hook(mlx.window, 17, 1L << 17, &ft_close2, &mlx);
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
	game.player_direction = input.direction;
	game.map = input.map;
	game.nbr_lines = input.nbr_lines;
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

