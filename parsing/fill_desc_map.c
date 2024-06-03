/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util4_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:16:45 by afanidi           #+#    #+#             */
/*   Updated: 2024/06/02 20:16:47 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	fill_desc_map(char *line, t_input *input, int *index_start_map,
		int *error)
{
	if (empty_line(line))
		return ;
	if (is_texture(line, input) == 1 && *error == 0)
	{
		*index_start_map += 1;
		return ;
	}
	else
	{
		if (is_not_map(line) == 1)
		{
			*index_start_map = 0;
			return ;
		}
		*error = 1;
		if (all_elements_set(input, 0) && *index_start_map == 6)
		{
			if (input->w < ft_strlen(line))
				input->w = ft_strlen(line);
			input->h += 1;
		}
	}
}

int	check_espace(t_input *input, int i, int j, char type)
{
	if (type == '2')
	{
		if (i < 0 || i >= input->h || j < 0 || j >= input->w)
			return (1);
		if (input->map[i][j] == '0')
			return (0);
	}
	else
	{
		if (input->map[i][j] == '2' || input->map[i][j] == '\0')
			return (0);
	}
	return (1);
}

int	is_not_map(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '1' || line[i] == '0' || is_direction(line[i]) != -1
			|| white_space(line[i]))
		{
			i++;
			continue ;
		}
		else
			return (1);
	}
	return (0);
}

int	all_elements_set(t_input *input, int flag)
{
	if (input->no && input->so && input->we && input->ea && input->f_color != -1
		&& input->c_color != -1)
	{
		if (flag == 0)
			return (1);
	}
	if (flag == 1)
	{
		if (input->pos_x != -1 && input->pos_y != -1 && input->direction != -1)
			return (1);
	}
	return (0);
}
