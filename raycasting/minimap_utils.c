/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sajaite <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 22:16:21 by sajaite           #+#    #+#             */
/*   Updated: 2024/06/10 22:16:24 by sajaite          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	initialize_line(t_point *delta, t_point *signe, t_point start,
		t_point end)
{
	delta->x = abs((int)((int)end.x - (int)start.x));
	delta->y = abs((int)((int)end.y - (int)start.y));
	signe->x = 1;
	signe->y = 1;
	if ((int)end.x <= (int)start.x)
		signe->x = -1;
	if ((int)end.y <= (int)start.y)
		signe->y = -1;
}

void	draw_line(t_img *img, t_point start, t_point end)
{
	t_point	delta;
	t_point	signe;
	t_point	increment;
	float	step;
	int		i;

	i = 0;
	initialize_line(&delta, &signe, start, end);
	step = fmax(fabs(delta.y), fabs(delta.x));
	increment.x = signe.x * delta.x / step;
	increment.y = signe.y * delta.y / step;
	while (i <= step)
	{
		my_mlx_pixel_put(img, round(start.x), round(start.y), 0x00FF0000);
		start.x += increment.x;
		start.y += increment.y;
		i++;
	}
}

void	draw_square(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINI_CUBE_SIZE)
	{
		j = 0;
		while (j < MINI_CUBE_SIZE)
		{
			my_mlx_pixel_put(&game->mlx.minimap_image, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_player(t_game *game, t_point player)
{
	int		i;
	int		j;
	int		r;
	t_point	end;

	r = MINI_CUBE_SIZE / 4;
	i = -r;
	while (i < r)
	{
		j = -r;
		while (j < r)
		{
			if (i * i + j * j <= r * r)
				my_mlx_pixel_put(&game->mlx.minimap_image, player.x + i,
					player.y + j, 0x00FF0000);
			j++;
		}
		i++;
	}
	end.x = player.x + (int)(MINI_CUBE_SIZE * cos(game->player.rotation_angle));
	end.y = player.y + (int)(MINI_CUBE_SIZE * sin(game->player.rotation_angle));
	draw_line(&game->mlx.minimap_image, player, end);
}

int	is_door(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	if (x <= 0 || y <= 0 || x >= game->map_width || y >= game->map_height)
		return (0);
	while (i < game->nb_doors)
	{
		if (game->map[y][x] == '1' && (int)game->doors[i].x == x
			&& (int)game->doors[i].y == y)
			return (1);
		i++;
	}
	return (0);
}
