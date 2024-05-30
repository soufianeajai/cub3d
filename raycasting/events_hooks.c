
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

int is_collision(t_game *game, float x, float y)
{
    int map_x;
    int map_y;

	map_x = (int)(x / game->cube_size);
	map_y = (int)(y / game->cube_size);
	if (map_x >= 0 && map_x < game->map_width && map_y >= 0 && map_y < game->map_height)
    	return (game->map[map_y][map_x] != '0');
	return (0);
}
void handle_arrows(t_game *game, int keysym)
{
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
}
void handle_movements(t_game *game, int keysym, float *new_pos_x, float *new_pos_y)
{
	handle_arrows(game, keysym);
    if (keysym == W_KEY)
    {
        *new_pos_y += sin(game->player.rotation_angle) * MOVE_SPEED;
        *new_pos_x += cos(game->player.rotation_angle) * MOVE_SPEED;
    }
    else if (keysym == S_KEY)
    {
        *new_pos_y -= sin(game->player.rotation_angle) * MOVE_SPEED;
        *new_pos_x -= cos(game->player.rotation_angle) * MOVE_SPEED;
    }
    else if (keysym == A_KEY)
    {
        *new_pos_y += sin(game->player.rotation_angle - M_PI_2) * MOVE_SPEED;
        *new_pos_x += cos(game->player.rotation_angle - M_PI_2) * MOVE_SPEED;
    }
    else if (keysym == D_KEY)
    {
        *new_pos_y += sin(game->player.rotation_angle + M_PI_2) * MOVE_SPEED;
        *new_pos_x += cos(game->player.rotation_angle + M_PI_2) * MOVE_SPEED;
    }
}


int handle_keys(int keysym, t_game *game)
{
    float new_pos_x;
    float new_pos_y;
    float border;
    float distance_door;
    
	border = game->cube_size / 6;
    new_pos_x = game->player.x;
    new_pos_y = game->player.y;
   	handle_movements(game, keysym, &new_pos_x, &new_pos_y);
    if (new_pos_x > game->cube_size && new_pos_x < (game->map_width * game->cube_size) &&
        new_pos_y > game->cube_size && new_pos_y < (game->map_height * game->cube_size))
    {               
        if (!is_collision(game, new_pos_x - border, new_pos_y - border) &&
            !is_collision(game, new_pos_x + border, new_pos_y - border) &&
            !is_collision(game, new_pos_x - border, new_pos_y + border) &&
            !is_collision(game, new_pos_x + border, new_pos_y + border))
        {
            game->player.x = new_pos_x;
            game->player.y = new_pos_y;
        }
    }
    if (game->door.x > 0 && game->door.y > 0)
    {
        distance_door = calculate_distance(game->player.x/game->cube_size, game->player.y/game->cube_size, game->door.x, game->door.y);
        if (distance_door < M_PI - 1.14)
        {
            game->door_open = 1;
            game->map[(int)(game->door.y)][(int)(game->door.x)] = '0';
        }
        else
        {
            game->door_open = 0;
            game->map[(int)(game->door.y)][(int)(game->door.x)] = '1';
        }
    }

    //  if (game->door.x > 0 && game->door.y > 0)
    // {
    //     t_ray ray;
    //     ray = cast_ray(game, game->player.rotation_angle);
    //     distance_door = ray.distance;
    //     if (distance_door < game->cube_size || calculate_distance(game->player.x/game->cube_size, game->player.y/game->cube_size, game->door.x, game->door.y) < M_PI - 1.14)
    //     {
    //         game->door_open = 1;
    //         game->map[(int)(game->door.y)][(int)(game->door.x)] = '0';
    //     } 
    //     else
    //     {
    //         game->door_open = 0;
    //         game->map[(int)(game->door.y)][(int)(game->door.x)] = '1';
    //     }
    // }
    cast_all_rays(game);
    return (0);
}
