
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


// int	handle_keys(int keysym, t_game *game)
// {

// 	int new_pos_x = 0;
// 	int new_pos_y = 0;

// 	if (keysym == 124) // right arrow
// 	{
// 		game->player.direction -= ROTAION_SPEED;
// 		game->player.x_dir = cos(game->player.direction);
// 		game->player.y_dir = sin(game->player.direction);
// 		draw_minimap(game);
// 	}
// 	else if (keysym == 123) //left arrow
// 	{
// 		game->player.direction += ROTAION_SPEED;
// 		game->player.x_dir = cos(game->player.direction);
// 		game->player.y_dir = sin(game->player.direction);
// 		draw_minimap(game);
// 	}
// 	else if (keysym == 13) // W key
// 	{
// 		new_pos_y = sin(game->player.direction) * MOVE_SPEED;
// 		new_pos_x = cos(game->player.direction) * MOVE_SPEED;
// 		printf("new pos y %d\n", new_pos_y);
// 		// if (game->player.x < 0 || game->player.x >= game->map_width || new_pos_y < 0 || new_pos_y >= game->map_height)
// 		// 	return (0);
// 		// if (game->map[new_pos_y/MINI_CUBE][new_pos_x/MINI_CUBE] == '0')
// 		// {
// 			game->player.y += new_pos_y;
// 			game->player.x += new_pos_x;
// 		// }
// 		update_minimap(game);
// 	}
// 	// else if (keysym == 0) // A key
// 	// {
// 	// 	if (new_pos_x < 0 || new_pos_x >= game->map_width || y < 0 || y >= game->map_height)
// 	// 		return (0);
// 	// 	new_pos_x -= cos(game->player.direction) * MOVE_SPEED;
// 	// 	if (game->map[y][new_pos_x] == '0')
// 	// 		game->player.x = new_pos_x;
// 	// 	draw_minimap(game);
// 	// }
// 	// else if (keysym == 1) // S key
// 	// {
// 	// 	if (x < 0 || x >= game->map_width || new_pos_y < 0 || new_pos_y >= game->map_height)
// 	// 		return (0);
// 	// 	new_pos_y -= sin(game->player.direction) * MOVE_SPEED;
// 	// 	if (game->map[new_pos_y][x] == '0')
// 	// 		game->player.y = new_pos_y;
// 	// 	draw_minimap(game);	
// 	// }
// 	// else if (keysym == 2) // D key
// 	// {
// 	// 	if (new_pos_x < 0 || new_pos_x >= game->map_width || y < 0 || y >= game->map_height)
// 	// 		return (0);
// 	// 	new_pos_x += cos(game->player.direction) * MOVE_SPEED;
// 	// 	if (game->map[y][new_pos_x] == '0')
// 	// 		game->player.x = new_pos_x;
// 	// 	draw_minimap(game);	
// 	// }
// 	mlx_put_image_to_window(game->mlx.connect, game->mlx.window,game->mlx.minimap_image.ptr, 0, HEIGHT - MINI_HEIGHT);
// 	return (0);
// }
