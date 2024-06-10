/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sajaite <sajaite@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 22:16:32 by sajaite           #+#    #+#             */
/*   Updated: 2024/06/10 22:30:17 by sajaite          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_collision(t_game *game, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / CUBE_SIZE);
	map_y = (int)(y / CUBE_SIZE);
	if (map_x >= 0 && map_x < game->map_width && map_y >= 0
		&& map_y < game->map_height)
		return (game->map[map_y][map_x] != '0');
	return (0);
}

void	handle_doors(t_game *game)
{
	float	distance_door;

	distance_door = 0;
	if (game->door.x > 0 && game->door.y > 0)
	{
		distance_door = calculate_distance(game->player.x / CUBE_SIZE,
				game->player.y / CUBE_SIZE, game->door.x, game->door.y);
		if (distance_door < 1.7)
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
}
