
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


int mouse_move(int x, int y, t_game *game)
{
	int dx = 0;
	dx = (x - game->last_mouse_x);
    if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT )
	{
		dx = (x - game->last_mouse_x);
		if (game->last_mouse_x == -1)
			game->last_mouse_x = x;
		else if (x > game->last_mouse_x)
			game->player.turn_direction = +1;
		else if (x < game->last_mouse_x)
			game->player.turn_direction = -1;
    	game->player.rotation_angle += ROTATION_SPEED*dx/80;
		game->last_mouse_x = x;
	}
	else if (game->last_mouse_x != -1)
	{
		dx = (x - game->last_mouse_x);
		game->player.rotation_angle += ROTATION_SPEED*game->player.turn_direction;
		cast_all_rays(game);
		game->last_mouse_x = x;
	}
	cast_all_rays(game);
    return (0);
}

int	handle_keys(int keysym, t_game *game)
{
	float new_pos_x;
	float new_pos_y;
	int map_x;
	int map_y;
	new_pos_x = game->player.x;
	new_pos_y = game->player.y;
	if (keysym == RIGHT_ARROW)
	{
		game->player.turn_direction = +1;
		game->player.rotation_angle += ROTATION_SPEED * game->player.turn_direction;
	}
	else if (keysym == LEFT_ARROW)
	{
		game->player.turn_direction = -1;
		game->player.rotation_angle += ROTATION_SPEED * game->player.turn_direction;
	}
	else if (keysym == W_KEY)
	{
		new_pos_y += sin(game->player.rotation_angle) * MOVE_SPEED;
		new_pos_x += cos(game->player.rotation_angle) * MOVE_SPEED;
	}
	else if (keysym == S_KEY)
	{
		new_pos_y -= sin(game->player.rotation_angle) * MOVE_SPEED;
		new_pos_x -= cos(game->player.rotation_angle) * MOVE_SPEED;
	}
	else if (keysym == A_KEY)
	{
		new_pos_y += sin(game->player.rotation_angle - M_PI_2) * MOVE_SPEED;
		new_pos_x += cos(game->player.rotation_angle - M_PI_2) * MOVE_SPEED;
	}
	else if (keysym == D_KEY)
	{
		new_pos_y += sin(game->player.rotation_angle + M_PI_2) * MOVE_SPEED;
		new_pos_x += cos(game->player.rotation_angle + M_PI_2) * MOVE_SPEED;
	}
	map_x = (int)(new_pos_x / game->cube_size);
    map_y = (int)(new_pos_y / game->cube_size);
    if (new_pos_x > game->cube_size && new_pos_x < (game->map_width * game->cube_size) &&
        new_pos_y > game->cube_size && new_pos_y < (game->map_height * game->cube_size) &&
        game->map[map_y][map_x] == '0')
    {
        game->player.x = new_pos_x;
        game->player.y = new_pos_y;
    }
    cast_all_rays(game);
    return (0);
}
