/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_intersections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sajaite <sajaite@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 22:16:51 by sajaite           #+#    #+#             */
/*   Updated: 2024/06/10 22:32:07 by sajaite          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_point	get_first_intersection(t_game *game, t_ray *ray, t_axes axis)
{
	t_point	first_intersection;

	if (axis == Y)
	{
		first_intersection.y = floor(game->player.y / CUBE_SIZE) * CUBE_SIZE;
		if (ray->is_facing_down)
			first_intersection.y += CUBE_SIZE;
		first_intersection.x = game->player.x + (first_intersection.y
				- game->player.y) / tan(ray->angle);
	}
	else
	{
		first_intersection.x = floor(game->player.x / CUBE_SIZE) * CUBE_SIZE;
		if (ray->is_facing_right)
			first_intersection.x += CUBE_SIZE;
		first_intersection.y = game->player.y + (first_intersection.x
				- game->player.x) * tan(ray->angle);
	}
	return (first_intersection);
}

t_point	get_step(t_ray *ray, t_axes axis)
{
	t_point	step;

	if (axis == Y)
	{
		step.y = CUBE_SIZE;
		if (!ray->is_facing_down)
			step.y *= -1;
		step.x = CUBE_SIZE / tan(ray->angle);
		if ((!ray->is_facing_right && step.x > 0) || (ray->is_facing_right
				&& step.x < 0))
			step.x *= -1;
	}
	else
	{
		step.x = CUBE_SIZE;
		if (!ray->is_facing_right)
			step.x *= -1;
		step.y = CUBE_SIZE * tan(ray->angle);
		if ((!ray->is_facing_down && step.y > 0) || (ray->is_facing_down
				&& step.y < 0))
			step.y *= -1;
	}
	return (step);
}

int	intersection_found(t_game *game, t_ray *ray, t_point next_intersection,
		t_point to_check)
{
	if (game->map[(int)(to_check.y / CUBE_SIZE)][(int)(to_check.x
			/ CUBE_SIZE)] == '1')
	{
		if (is_door(game, (int)(to_check.x / CUBE_SIZE), (int)(to_check.y
			/ CUBE_SIZE)))
			ray->is_wall = 0;
		ray->wall_hit.x = next_intersection.x;
		ray->wall_hit.y = next_intersection.y;
		ray->distance = calculate_distance(game->player.x, game->player.y,
				ray->wall_hit.x, ray->wall_hit.y);
		return (1);
	}
	return (0);
}

t_ray	get_intersection(t_game *game, t_ray ray, t_axes axis)
{
	t_point	next_inter;
	t_point	step;
	t_point	to_check;
	int		i;

	i = -1;
	next_inter = get_first_intersection(game, &ray, axis);
	step = get_step(&ray, axis);
	while (next_inter.x >= 0 && next_inter.x < game->map_width * CUBE_SIZE
		&& next_inter.y >= 0 && next_inter.y < game->map_height * CUBE_SIZE)
	{
		to_check = next_inter;
		check_direction(&to_check, &ray, axis);
		if (intersection_found(game, &ray, next_inter, to_check))
		{
			game->door = game->doors[i];
			break ;
		}
		next_inter.x += step.x;
		next_inter.y += step.y;
	}
	return (ray);
}

void	check_direction(t_point *to_check, t_ray *ray, t_axes axis)
{
	if (axis == Y && !ray->is_facing_down)
		to_check->y--;
	else if (axis == X && !ray->is_facing_right)
		to_check->x--;
}
