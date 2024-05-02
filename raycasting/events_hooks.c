
#include"../cub3d.h"

int	ft_close(int keysym, t_mlx *mlx)
{
	if (keysym == 53)
	{
		mlx_destroy_window(mlx->connect, mlx->window);
		mlx_destroy_image(mlx->connect, mlx->image.ptr);
		free_ptr(mlx->connect);
		exit(0);
	}
	return (0);
}

int	ft_close2(t_mlx *mlx)
{
	mlx_destroy_window(mlx->connect, mlx->window);
	mlx_destroy_image(mlx->connect, mlx->image.ptr);
	free_ptr(mlx->connect);
	exit(0);
	return (0);
}

int	handle_keys(int keysym, t_mlx *mlx)
{
	if (keysym == 124)
	{
		
	}
	else if (keysym == 123)
	{
		
	}
	else if (keysym == 126)
	{
		
	}
	else if (keysym == 125)
	{
		
	}
	mlx_put_image_to_window(mlx->connect, mlx->window, mlx->image.ptr, 0, 0);
	return (0);
}
