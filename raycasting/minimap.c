/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sajaite <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 22:16:40 by sajaite           #+#    #+#             */
/*   Updated: 2024/06/10 22:16:42 by sajaite          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	get_square_type(t_game *game, t_point start, int x, int y)
{
	if (y >= 0 && y < game->map_height && x >= 0 && x < game->map_width)
	{
		if (is_door(game, x, y))
			draw_square(game, (x - start.x) * MINI_CUBE_SIZE, (y - start.y)
				* MINI_CUBE_SIZE, 0x0000FF00);
		else if (game->map[(int)y][(int)x] == '1')
			draw_square(game, (x - start.x) * MINI_CUBE_SIZE, (y - start.y)
				* MINI_CUBE_SIZE, 0x00000000);
		else if (game->map[(int)y][(int)x] == '0')
			draw_square(game, (x - start.x) * MINI_CUBE_SIZE, (y - start.y)
				* MINI_CUBE_SIZE, 0x00FFFFFF);
	}
	else
		draw_square(game, (x - start.x) * MINI_CUBE_SIZE, (y - start.y)
			* MINI_CUBE_SIZE, 0x0000FFFF);
}

void	draw(t_game *game, t_point start)
{
	int	x;
	int	y;
	int	end_x;
	int	end_y;

	end_x = (int)((int)game->player.x / CUBE_SIZE) + (int)(MINI_WIDTH
			/ MINI_CUBE_SIZE / 2) + 1;
	end_y = (int)(((int)game->player.y / CUBE_SIZE) + (int)(MINI_HEIGHT
				/ MINI_CUBE_SIZE / 2)) + 1;
	y = (int)start.y - 1;
	while (++y < end_y)
	{
		x = (int)start.x - 1;
		while (++x < end_x)
			get_square_type(game, start, x, y);
	}
}

void	draw_minimap(t_game *game)
{
	t_point	start;
	t_point	mini_player;

	start.x = (int)(game->player.x / CUBE_SIZE) - (int)(MINI_WIDTH
			/ MINI_CUBE_SIZE / 2);
	start.y = (int)(game->player.y / CUBE_SIZE) - (int)(MINI_HEIGHT
			/ MINI_CUBE_SIZE / 2);
	draw(game, start);
	mini_player.x = ((game->player.x / CUBE_SIZE) - start.x) * MINI_CUBE_SIZE;
	mini_player.y = ((game->player.y / CUBE_SIZE) - start.y) * MINI_CUBE_SIZE;
	draw_player(game, mini_player);
	mlx_put_image_to_window(game->mlx.connect, game->mlx.window,
		game->mlx.minimap_image.ptr, 0, HEIGHT - MINI_HEIGHT);
}
