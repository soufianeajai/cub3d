
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
	float new_pos_x;
	float new_pos_y;
	
	new_pos_x = game->player.x;
	new_pos_y = game->player.y;
	if (keysym == 124) // right arrow
	{
		game->player.turn_direction = +1;
		game->player.rotation_angle += ROTATION_SPEED * game->player.turn_direction;
	}
	else if (keysym == 123) // left arrow
	{
		game->player.turn_direction = -1;
		game->player.rotation_angle += ROTATION_SPEED * game->player.turn_direction;
	}
	else if (keysym == 13) // W key
	{
		new_pos_y += sin(game->player.rotation_angle) * MOVE_SPEED;
		new_pos_x += cos(game->player.rotation_angle) * MOVE_SPEED;
	}
	else if (keysym == 1) // S key (Backward)
	{
		new_pos_y -= sin(game->player.rotation_angle) * MOVE_SPEED;
		new_pos_x -= cos(game->player.rotation_angle) * MOVE_SPEED;
	}
	else if (keysym == 0) // A key (Left)
	{
		new_pos_y += sin(game->player.rotation_angle - M_PI_2) * MOVE_SPEED;
		new_pos_x += cos(game->player.rotation_angle - M_PI_2) * MOVE_SPEED;
	}
	else if (keysym == 2) // D key (Right)
	{
		new_pos_y += sin(game->player.rotation_angle + M_PI_2) * MOVE_SPEED;
		new_pos_x += cos(game->player.rotation_angle + M_PI_2) * MOVE_SPEED;
	}
	// Check for collisions with walls before updating position
	if (new_pos_x >= 0 && new_pos_x < game->map_width * game->cube_size &&
		new_pos_y >= 0 && new_pos_y < game->map_height * game->cube_size &&
		game->map[(int)(new_pos_y / game->cube_size)][(int)(new_pos_x / game->cube_size)] == '0')
	{
		game->player.x = new_pos_x;
		game->player.y = new_pos_y;
	}
	cast_all_rays(game);
//	draw_minimap(game);
	return (0);
}
