/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 19:02:21 by afanidi           #+#    #+#             */
/*   Updated: 2024/06/02 19:02:25 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**avance_line(int index_start_map, char *file, int *fd, int len)
{
	int		i;
	char	*line;
	char	**map;

	i = 0;
	*fd = open(file, O_RDONLY);
	map = malloc(sizeof(char *) * (len + 1));
	if (!map)
		return (NULL);
	while (i < index_start_map)
	{
		line = get_next_line(*fd);
		if (empty_line(line))
		{
			free(line);
			continue ;
		}
		free(line);
		i++;
	}
	return (map);
}

int	check_error_espace(char **map, int i, t_input *input)
{
	int	j;

	j = -1;
	while (map[i][++j])
	{
		if (map[i][j] == '2' || map[i][j] == '0')
		{
			if (!check_espace(input, i, j - 1, map[i][j])
				|| !check_espace(input, i, j + 1, map[i][j]) ||
				!check_espace(input, i - 1, j, map[i][j])
					|| !check_espace(input, i + 1, j, map[i][j]))
			{
				printf("\nError : map[%d][%d] = %c\n", i, j, map[i][j]);
				return (0);
			}
		}
	}
	return (1);
}

int	error_first_last_element(char **map, t_input *input, int i)
{
	int	j;

	j = 0;
	if (i == 0 || i == input->h - 1)
	{
		while (map[i][j])
			if (!is_wall(map[i][j++]))
				return (0);
	}
	return (1);
}

int	parsing(char *file, t_input *input)
{
	char	*line;
	int		fd;
	int		index_start_map;
	int		error;

	index_start_map = 0;
	error = 0;
	fd = open(file, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		fill_desc_map(line, input, &index_start_map, &error);
		free(line);
	}
	line = NULL;
	if (input->h == 0 || index_start_map != 6)
		return (close(fd), free_all_elements(input), 0);
	input->map = fill_map(input, file, index_start_map, line);
	if (!input->map || parsing_map(input->map, input) == 0
		|| !all_elements_set(input, 1))
		return (close(fd), free_all_elements(input), 0);
	return (close(fd), 1);
}
