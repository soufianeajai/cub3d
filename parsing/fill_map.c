/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:00:30 by afanidi           #+#    #+#             */
/*   Updated: 2024/06/03 18:00:35 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**fill_map(t_input *input, char *file, int index_start_map, char *line)
{
	int		fd;
	int		i;
	char	**map;

	i = -1;
	map = avance_line(index_start_map, file, &fd, input->h);
	while (map != NULL)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (empty_line(line))
		{
			free(line);
			continue ;
		}
		if (is_not_map(line))
			return (free(line), ft_free(map), close(fd), NULL);
		if (++i <= input->h && i != -2)
			map[i] = get_full_len(line, input, &i);
		if (i == -2)
			return (free(line), ft_free(map), close(fd), NULL);
		free(line);
	}
	return (map[i + 1] = NULL, close(fd), map);
}

int	parsing_map(char **map, t_input *input)
{
	int	i;

	i = -1;
	while (map[++i])
	{
		if (error_first_last_element(map, input, i) == 0)
			return (0);
		else
		{
			if (check_error_espace(map, i, input) == 0)
				return (0);
		}
	}
	return (1);
}

int	is_texture(char *line, t_input *input)
{
	int	i;

	i = 0;
	while (white_space(line[i]))
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O' && !input->no)
		return (input->no = fill_elements(line, i + 2), 1);
	if (line[i] == 'S' && line[i + 1] == 'O' && !input->so)
		return (input->so = fill_elements(line, i + 2), 1);
	if (line[i] == 'W' && line[i + 1] == 'E' && !input->we)
		return (input->we = fill_elements(line, i + 2), 1);
	if (line[i] == 'E' && line[i + 1] == 'A' && !input->ea)
		return (input->ea = fill_elements(line, i + 2), 1);
	if (line[i] == 'F' && line[i + 1] == ' ' && input->f_color == -1)
		return (input->f_color = fill_rgb(line, i + 1), 1);
	if (line[i] == 'C' && input->c_color == -1)
		return (input->c_color = fill_rgb(line, i + 1), 1);
	return (0);
}
