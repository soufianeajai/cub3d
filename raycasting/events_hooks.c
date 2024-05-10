
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

int	handle_keys(int keysym, t_game *game)
{
	if (keysym == 124) // right arrow
	{
		game->player.direction -= 0.5;
		// update(game);
		// draw_minimap(&game);
	}
	else if (keysym == 123) //left arrow
	{
		game->player.direction += 0.5;
	}
	else if (keysym == 13) // W key
	{
		
	}
	else if (keysym == 0) // A key
	{
		
	}
	else if (keysym == 1) // S key
	{

	}
	else if (keysym == 2) // D key
	{

	}
	mlx_put_image_to_window(game->mlx.connect, game->mlx.window,game->mlx.minimap_image.ptr, 0, HEIGHT - MINI_HEIGHT);
	return (0);
}
