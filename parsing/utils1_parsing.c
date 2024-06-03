/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 19:48:35 by afanidi           #+#    #+#             */
/*   Updated: 2024/06/02 19:48:36 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

t_input	init_data(void)
{
	t_input	input;

	input.door_x = -1;
	input.door_y = -1;
	input.pos_x = -1;
	input.pos_y = -1;
	input.direction = -1;
	input.h = 0;
	input.w = 0;
	input.no = NULL;
	input.so = NULL;
	input.we = NULL;
	input.ea = NULL;
	input.f_color = -1;
	input.c_color = -1;
	input.map = NULL;
	return (input);
}

void	free_all_elements(t_input *input)
{
	free(input->no);
	input->no = NULL;
	free(input->so);
	input->so = NULL;
	free(input->we);
	input->we = NULL;
	free(input->ea);
	input->ea = NULL;
	if (input->map)
		ft_free(input->map);
}

void	set_player(t_input *input, int deg, int x, int y)
{
	if (deg == -1)
		return ;
	input->direction = deg;
	input->pos_x = x;
	input->pos_y = y;
}

char	*get_full_len(char *line, t_input *input, int *position)
{
	char	*new_line;
	int		i;

	i = 0;
	new_line = malloc(input->w + 1);
	if (!new_line)
		return (NULL);
	while (line[i])
	{
		if (is_direction(line[i]) != -1 && input->direction != -1)
			return (free(new_line), *position = -2, NULL);
		set_player(input, is_direction(line[i]), i, *position);
		if (is_direction(line[i]) != -1)
			new_line[i] = '0';
		else
			new_line[i] = line[i];
		i++;
	}
	while (i < input->w)
		new_line[i++] = '2';
	new_line[i] = '\0';
	return (replace_spaces(new_line));
}
