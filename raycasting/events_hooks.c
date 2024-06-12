/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sajaite <sajaite@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 22:17:06 by sajaite           #+#    #+#             */
/*   Updated: 2024/06/12 03:03:53 by sajaite          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_close(t_game *game)
{
	mlx_destroy_image(game->mlx.connect, game->mlx.minimap_image.ptr);
	mlx_destroy_image(game->mlx.connect, game->mlx.image.ptr);
	mlx_destroy_image(game->mlx.connect, game->mlx.north_wall_image.ptr);
	mlx_destroy_image(game->mlx.connect, game->mlx.south_wall_image.ptr);
	mlx_destroy_image(game->mlx.connect, game->mlx.east_wall_image.ptr);
	mlx_destroy_image(game->mlx.connect, game->mlx.west_wall_image.ptr);
	mlx_destroy_image(game->mlx.connect, game->mlx.door_image.ptr);
	free_all_elements(&(game->input));
	mlx_destroy_window(game->mlx.connect, game->mlx.window);
	mlx_destroy_display(game->mlx.connect);
	free_ptr(game->mlx.connect);
	exit(1337);
	return (0);
}

int	track_mouse_position(t_game *game)
{
	int	x;
	int	y;
	int	dx;

	mlx_mouse_get_pos(game->mlx.connect, game->mlx.window, &x, &y);
	dx = (x - game->last_mouse_x);
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		if (game->last_mouse_x == -1)
			game->last_mouse_x = x;
		else if (x > game->last_mouse_x)
			game->player.turn_direction = +1;
		else if (x < game->last_mouse_x)
			game->player.turn_direction = -1;
		game->player.rotation_angle += game->rotation_speed * dx / 80;
	}
	else if (game->last_mouse_x != -1)
		game->player.rotation_angle += (game->rotation_speed
				* game->player.turn_direction)/4;
	game->last_mouse_x = x;
	cast_all_rays(game);
	return (0);
}

void	handle_arrows(t_game *game, int keysym)
{
	if (keysym == XK_Right)
	{
		game->player.turn_direction = +1;
		game->player.rotation_angle += game->rotation_speed
			* game->player.turn_direction;
	}
	else if (keysym == XK_Left)
	{
		game->player.turn_direction = -1;
		game->player.rotation_angle += game->rotation_speed
			* game->player.turn_direction;
	}
}

void	handle_movements(t_game *game, int keysym, float *new_pos_x,
		float *new_pos_y)
{
	handle_arrows(game, keysym);
	if (keysym == XK_w || keysym == XK_W)
	{
		*new_pos_y += sin(game->player.rotation_angle) * game->move_speed;
		*new_pos_x += cos(game->player.rotation_angle) * game->move_speed;
	}
	else if (keysym == XK_s || keysym == XK_S)
	{
		*new_pos_y -= sin(game->player.rotation_angle) * game->move_speed;
		*new_pos_x -= cos(game->player.rotation_angle) * game->move_speed;
	}
	else if (keysym == XK_a || keysym == XK_A)
	{
		*new_pos_y += sin(game->player.rotation_angle - M_PI_2)
			* game->move_speed;
		*new_pos_x += cos(game->player.rotation_angle - M_PI_2)
			* game->move_speed;
	}
	else if (keysym == XK_d || keysym == XK_D)
	{
		*new_pos_y += sin(game->player.rotation_angle + M_PI_2)
			* game->move_speed;
		*new_pos_x += cos(game->player.rotation_angle + M_PI_2)
			* game->move_speed;
	}
}

int	handle_keys(int keysym, t_game *game)
{
	t_point	new_pos;
	float	border;

	if (keysym == XK_Escape)
		ft_close(game);
	border = CUBE_SIZE / 6;
	new_pos.x = game->player.x;
	new_pos.y = game->player.y;
	handle_movements(game, keysym, &new_pos.x, &new_pos.y);
	if (new_pos.x > CUBE_SIZE && new_pos.x < (game->map_width * CUBE_SIZE)
		&& new_pos.y > CUBE_SIZE && new_pos.y < (game->map_height * CUBE_SIZE))
	{
		if (!is_collision(game, new_pos.x - border, new_pos.y - border)
			&& !is_collision(game, new_pos.x + border, new_pos.y - border)
			&& !is_collision(game, new_pos.x - border, new_pos.y + border)
			&& !is_collision(game, new_pos.x + border, new_pos.y + border))
		{
			game->player.x = new_pos.x;
			game->player.y = new_pos.y;
		}
	}
	handle_doors(game);
	cast_all_rays(game);
	return (0);
}
