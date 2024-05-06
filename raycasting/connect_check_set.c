#include"../cub3d.h"

int	ft_connect(t_mlx *mlx)
{
	mlx->connect = mlx_init();
	if (!mlx->connect)
	{
		perror("Problem in the display connection");
		exit(1);
	}
	mlx->window = mlx_new_window(mlx->connect, WIDTH, HEIGHT, "CUB3D");
	if (!mlx->window)
		ft_error(mlx->connect, "Problem in creating the window");
	mlx->image.ptr = mlx_new_image(mlx->connect, WIDTH, HEIGHT);
	if (!mlx->image.ptr)
	{
		mlx_destroy_window(mlx->connect, mlx->window);
		ft_error(mlx->connect, "Problem in Allocating the image");
	}
	mlx->image.addr = mlx_get_data_addr(mlx->image.ptr, \
			&(mlx->image.bpp), &(mlx->image.line_len), &(mlx->image.endian));
	return (0);
}

void	ft_error(void	*ptr, char *msg)
{
	free_ptr(ptr);
	perror(msg);
	exit(1);
}



