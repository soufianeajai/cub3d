/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sajaite <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 22:17:32 by sajaite           #+#    #+#             */
/*   Updated: 2024/06/10 22:17:33 by sajaite          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_doors(t_game *game, t_input *input)
{
	game->door.x = -1;
	game->door.y = -1;
	if (input->nb_doors > 0)
	{
		game->door.x = input->door[0].x;
		game->door.y = input->door[0].y;
		game->nb_doors = input->nb_doors;
		ft_memcpy(game->doors, input->door, sizeof(t_point) * NBR_DOORS);
	}
	game->door_open = 0;
}

t_game	init_game(t_mlx mlx, t_input input)
{
	t_game	game;

	game.mlx = mlx;
	game.map = input.map;
	game.map_height = input.h;
	game.map_width = input.w;
	game.c_color = input.c_color;
	game.f_color = input.f_color;
	game.player.x = (input.pos_x * CUBE_SIZE) + CUBE_SIZE / 2;
	game.player.y = (input.pos_y * CUBE_SIZE) + CUBE_SIZE / 2;
	game.player.turn_direction = 0;
	game.player.rotation_angle = deg_to_rad(input.direction);
	game.last_mouse_x = -1;
	game.fov = deg_to_rad(60);
	game.angle_increment = (game.fov / NUM_RAYS);
	game.distance_to_projection_plan = (WIDTH / 2) / (tan(game.fov / 2));
	game.rotation_speed = deg_to_rad(3);
	game.move_speed = CUBE_SIZE / 5;
	init_doors(&game, &input);
	return (game);
}
