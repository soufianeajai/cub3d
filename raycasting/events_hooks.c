
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
		game->player.direction += ROTAION_SPEED;
		game->player.x_dir = cos(game->player.direction);
		game->player.y_dir = sin(game->player.direction);
		draw_minimap(game);
	}
	else if (keysym == 123) //left arrow
	{
		game->player.direction -= ROTAION_SPEED;
		game->player.x_dir = cos(game->player.direction);
		game->player.y_dir = sin(game->player.direction);
		draw_minimap(game);
	}
	else if (keysym == 13) // W key
	{
		game->player.y += sin(game->player.direction) * MOVE_SPEED;
		draw_minimap(game);
	}
	else if (keysym == 0) // A key
	{
	//	game->player.x -= cos(game->player.direction) * MOVE_SPEED;
		draw_minimap(game);
	}
	else if (keysym == 1) // S key
	{
		game->player.y -= sin(game->player.direction) * MOVE_SPEED;
		draw_minimap(game);	
	}
	else if (keysym == 2) // D key
	{
	//	game->player.x += cos(game->player.direction) * MOVE_SPEED;
		draw_minimap(game);	
	}
	mlx_put_image_to_window(game->mlx.connect, game->mlx.window,game->mlx.minimap_image.ptr, 0, HEIGHT - MINI_HEIGHT);
	return (0);
}
