/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 22:32:03 by afanidi           #+#    #+#             */
/*   Updated: 2024/06/03 22:32:04 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_rectangle(t_game *game, int start_x, int height, int color)
{
	int	j;

	j = 0;
	while (j < height)
	{
		if (start_x >= 0 && start_x < WIDTH && j >= 0 && j < HEIGHT)
			my_mlx_pixel_put(&game->mlx.image, start_x, +j, color);
		j++;
	}
}

int	get_texture_pixel(t_img *texture, int x, int y)
{
	int		pixel_color;
	char	*pixel;

	pixel = texture->addr + (y * texture->line_len + x * (texture->bpp / 8));
	pixel_color = *(int *)pixel;
	return (pixel_color);
}

void	check_start_end(int *start, int *end, float *y, float step)
{
	if (*start < 0)
	{
		*y = -*start * step;
		*start = 0;
	}
	if (*end >= HEIGHT)
		*end = HEIGHT;
}

void	draw_textured_wall(t_game *game, int column, float wall_height,
		t_img *texture)
{
	t_point	texture_pos;
	int		start_y;
	int		end_y;
	int		y;
	float	step;

	texture_pos.x = (int)(game->rays[column].texture_offset / CUBE_SIZE
			* texture->width);
	start_y = (HEIGHT / 2) - (wall_height / 2);
	end_y = start_y + wall_height;
	step = (float)texture->height / wall_height;
	texture_pos.y = 0;
	check_start_end(&start_y, &end_y, &texture_pos.y, step);
	y = start_y;
	while (y < end_y)
	{
		my_mlx_pixel_put(&game->mlx.image, column, y, get_texture_pixel(texture,
				texture_pos.x, texture_pos.y));
		texture_pos.y += step;
		y++;
	}
}

void	draw_column(t_game *game, int column)
{
	float	wall_height;
	int		start_y;
	int		end_y;
	t_img	*texture;

	wall_height = (CUBE_SIZE / game->rays[column].distance)
		* game->distance_to_projection_plan;
	draw_rectangle(game, column, HEIGHT, game->f_color);
	start_y = (HEIGHT / 2) - (wall_height / 2);
	end_y = start_y + wall_height;
	if (start_y > 0)
		draw_rectangle(game, column, start_y, game->c_color);
	texture = get_orientation_texture(game, game->rays[column].orientation);
	draw_textured_wall(game, column, wall_height, texture);
}
