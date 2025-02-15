/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sajaite <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 22:17:00 by sajaite           #+#    #+#             */
/*   Updated: 2024/06/10 22:17:01 by sajaite          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_door_image(t_mlx *mlx)
{
	if (!get_image_from_xpm(mlx->connect, "./maps/door.xpm", &mlx->door_image))
	{
		mlx_destroy_image(mlx->connect, mlx->north_wall_image.ptr);
		mlx_destroy_image(mlx->connect, mlx->south_wall_image.ptr);
		mlx_destroy_image(mlx->connect, mlx->east_wall_image.ptr);
		mlx_destroy_image(mlx->connect, mlx->west_wall_image.ptr);
		return (0);
	}
	return (1);
}

int	get_images(t_mlx *mlx, t_input *input)
{
	if (!get_image_from_xpm(mlx->connect, input->no, &mlx->north_wall_image))
		return (0);
	if (!get_image_from_xpm(mlx->connect, input->so, &mlx->south_wall_image))
	{
		mlx_destroy_image(mlx->connect, mlx->north_wall_image.ptr);
		return (0);
	}
	if (!get_image_from_xpm(mlx->connect, input->ea, &mlx->east_wall_image))
	{
		mlx_destroy_image(mlx->connect, mlx->north_wall_image.ptr);
		mlx_destroy_image(mlx->connect, mlx->south_wall_image.ptr);
		return (0);
	}
	if (!get_image_from_xpm(mlx->connect, input->we, &mlx->west_wall_image))
	{
		mlx_destroy_image(mlx->connect, mlx->north_wall_image.ptr);
		mlx_destroy_image(mlx->connect, mlx->south_wall_image.ptr);
		mlx_destroy_image(mlx->connect, mlx->east_wall_image.ptr);
		return (0);
	}
	return (get_door_image(mlx));
}

int	get_image_from_xpm(void *mlx_ptr, char *path_xpm, t_img *img)
{
	img->ptr = mlx_xpm_file_to_image(mlx_ptr, path_xpm, &img->width,
			&img->height);
	if (!img->ptr)
		return (0);
	img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->line_len,
			&img->endian);
	return (1);
}

void	my_mlx_pixel_put(t_img *image, int x, int y, int color)
{
	char	*pixel;
	int		offset;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		offset = y * image->line_len + x * (image->bpp / 8);
		pixel = image->addr + offset;
		*(int *)pixel = color;
	}
}
