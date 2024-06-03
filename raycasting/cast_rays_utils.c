/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 22:31:42 by afanidi           #+#    #+#             */
/*   Updated: 2024/06/03 22:31:43 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_point	get_best_door(t_game *game)
{
	t_point	door;
	float	distance;
	float	best_distance;
	int		i;

	i = 0;
	distance = calculate_distance(game->player.x / CUBE_SIZE, game->player.y
			/ CUBE_SIZE, game->doors[0].x, game->doors[0].y);
	door = game->doors[0];
	while (++i < game->nb_doors)
	{
		best_distance = calculate_distance(game->player.x / CUBE_SIZE,
				game->player.y / CUBE_SIZE, game->doors[i].x, game->doors[i].y);
		if (best_distance < distance)
		{
			distance = best_distance;
			door = game->doors[i];
		}
	}
	return (door);
}

t_ray	init_ray(float ray_angle)
{
	t_ray	ray;

	ray.angle = normalize_angle(ray_angle);
	ray.distance = INT32_MAX;
	ray.is_wall = 1;
	ray.wall_hit.x = 0;
	ray.wall_hit.y = 0;
	ray.is_facing_down = (ray.angle > 0 && ray.angle < M_PI);
	ray.is_facing_right = (ray.angle < M_PI_2 || ray.angle > (3 * M_PI_2));
	return (ray);
}

t_wall_orientation	set_orientation(t_ray *ray, t_axes axis)
{
	t_wall_orientation	orientation;

	if (axis == Y)
	{
		if (ray->is_facing_down)
			orientation = SOUTH;
		else
			orientation = NORTH;
	}
	else
	{
		if (ray->is_facing_right)
			orientation = EAST;
		else
			orientation = WEST;
	}
	if (!ray->is_wall)
		orientation = DOOR;
	return (orientation);
}

t_img	*get_orientation_texture(t_game *game, t_wall_orientation orientation)
{
	t_img	*texture;

	if (orientation == NORTH)
		texture = &game->mlx.north_wall_image;
	else if (orientation == SOUTH)
		texture = &game->mlx.south_wall_image;
	else if (orientation == EAST)
		texture = &game->mlx.east_wall_image;
	else if (orientation == WEST)
		texture = &game->mlx.west_wall_image;
	else
		texture = &game->mlx.door_image;
	return (texture);
}
