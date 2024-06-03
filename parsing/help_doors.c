/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_doors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:00:12 by afanidi           #+#    #+#             */
/*   Updated: 2024/06/03 18:00:13 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "parsing.h"

int	white_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

int	get_position_door(t_input input, int *x, int *y, char **map)
{
	int	i;
	int	j;

	i = 0;
	flood_fill(input, input.pos_x, input.pos_y, map);
	while (i < input.h)
	{
		j = 0;
		while (j < input.w)
		{
			if (input.map[i][j] == 'y' && is_valid_door(input, i, j))
			{
				*x = j;
				*y = i;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	is_valid_door(t_input input, int i, int j)
{
	if (i == 0 || j == 0)
		return (0);
	if ((input.map[i][j - 1] == '0' && input.map[i][j + 1] == 'x')
		|| (input.map[i][j - 1] == 'x' && input.map[i][j + 1] == '0'))
	{
		if (input.map[i + 1][j] == 'y' && input.map[i - 1][j] == 'y')
			return (1);
	}
	if ((input.map[i - 1][j] == '0' && input.map[i + 1][j] == 'x')
		|| (input.map[i + 1][j] == '0' && input.map[i - 1][j] == 'x'))
	{
		if (input.map[i][j + 1] == 'y' && input.map[i][j - 1] == 'y')
			return (1);
	}
	return (0);
}

void	get_doors(t_input *input)
{
	int	x;
	int	y;
	int	i;

	i = -1;
	input->nb_doors = 0;
	while (input->nb_doors < NUM_DOORS)
	{
		if (!get_position_door(*input, &x, &y, input->map))
			break ;
		input->door[input->nb_doors].x = x;
		input->door[input->nb_doors].y = y;
		input->map[y][x] = '0';
		input->nb_doors++;
		mise_a_jour_map(input);
	}
	mise_a_jour_map(input);
	while (++i < input->nb_doors)
		input->map[(int)input->door[i].y][(int)input->door[i].x] = '1';
}
