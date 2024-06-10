/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sajaite <sajaite@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:42:51 by afanidi           #+#    #+#             */
/*   Updated: 2024/06/05 20:59:08 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_input	input;
	t_game	game;
	t_mlx	mlx;
	t_ray	rays[NUM_RAYS + 1];

	input = init_data();
	if (!check_argument(ac, av) || !parsing(av[1], &input))
		return (printf("Error\n"), 1);
	get_doors(&input);
	mlx = ft_connect(&input);
	game = init_game(mlx, input);
	game.input = input;
	game.rays = rays;
	cast_all_rays(&game);
	mlx_loop_hook(game.mlx.connect, track_mouse_position, &game);
	mlx_hook(game.mlx.window, DestroyNotify, StructureNotifyMask, ft_close,
		&game);
	mlx_hook(game.mlx.window, KeyPress, KeyPressMask, &handle_keys, &game);
	mlx_loop(game.mlx.connect);
	return (0);
}
