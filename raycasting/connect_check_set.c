#include"../cub3d.h"

t_mlx	ft_connect(t_input *input)
{
	t_mlx mlx;
	
	mlx.connect = mlx_init();
	if (!mlx.connect)
	{
		perror("Problem in the display connection");
		exit(1);
	}
	mlx.window = mlx_new_window(mlx.connect, WIDTH, HEIGHT, "CUB3D0x999");
	if (!mlx.window)
		ft_error(mlx.connect, "Problem in creating the window", input);
	mlx.image.ptr = mlx_new_image(mlx.connect, WIDTH, HEIGHT);
	mlx.minimap_image.ptr = mlx_new_image(mlx.connect, MINI_WIDTH, MINI_HEIGHT);
	if (!mlx.image.ptr || !mlx.minimap_image.ptr)
	{
		mlx_destroy_window(mlx.connect, mlx.window);
		ft_error(mlx.connect, "Problem in Allocating the image", input);
	}
	mlx.image.addr = mlx_get_data_addr(mlx.image.ptr, \
			&(mlx.image.bpp), &(mlx.image.line_len), &(mlx.image.endian));
	mlx.minimap_image.addr = mlx_get_data_addr(mlx.minimap_image.ptr, &(mlx.minimap_image.bpp), &(mlx.minimap_image.line_len), &(mlx.minimap_image.endian));
	if (get_images(&mlx, input) == 0)
	{
		mlx_destroy_window(mlx.connect, mlx.window);
		ft_error(mlx.connect, "Problem in getting the images",input);
	}
	return (mlx);
}

void	ft_error(void	*ptr, char *msg, t_input *input)
{
	free_all_elements(input);
	free_ptr(ptr);
	perror(msg);
	exit(1);
}



