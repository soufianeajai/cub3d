/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_check_set.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 22:31:51 by afanidi           #+#    #+#             */
/*   Updated: 2024/06/03 22:31:54 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_mlx	ft_connect(t_input *input)
{
	t_mlx	mlx;

	mlx.connect = mlx_init();
	if (!mlx.connect)
		ft_error(&mlx, "Problem in the display connection", input, 0);
	mlx.window = mlx_new_window(mlx.connect, WIDTH, HEIGHT, "CUB3D0x999");
	if (!mlx.window)
		ft_error(&mlx, "Problem in creating the window", input, 1);
	mlx.image.ptr = mlx_new_image(mlx.connect, WIDTH, HEIGHT);
	mlx.minimap_image.ptr = mlx_new_image(mlx.connect, MINI_WIDTH, MINI_HEIGHT);
	if (!mlx.image.ptr || !mlx.minimap_image.ptr)
		ft_error(mlx.connect, "Problem in Allocating the image", input, 2);
	mlx.image.addr = mlx_get_data_addr(mlx.image.ptr, &(mlx.image.bpp),
			&(mlx.image.line_len), &(mlx.image.endian));
	mlx.minimap_image.addr = mlx_get_data_addr(mlx.minimap_image.ptr,
			&(mlx.minimap_image.bpp), &(mlx.minimap_image.line_len),
			&(mlx.minimap_image.endian));
	if (get_images(&mlx, input) == 0)
		ft_error(mlx.connect, "Problem in getting the images", input, 2);
	return (mlx);
}

void	ft_error(t_mlx *mlx, char *msg, t_input *input, int free_flag)
{
	free_all_elements(input);
	if (free_flag == 1)
		free_ptr(mlx->connect);
	else if (free_flag == 2)
	{
		if (mlx->image.ptr)
			mlx_destroy_image(mlx->connect, mlx->image.ptr);
		if (mlx->minimap_image.ptr)
			mlx_destroy_image(mlx->connect, mlx->minimap_image.ptr);
		mlx_destroy_window(mlx->connect, mlx->window);
		free_ptr(mlx->connect);
	}
	mlx_destroy_display(mlx->connect);
	perror(msg);
	exit(1);
}
