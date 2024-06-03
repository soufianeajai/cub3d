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

int	init_data(t_input *input, char *file, int *error, int *index_start_map)
{
	*error = 0;
	*index_start_map = 0;
	input->door_x = -1;
	input->door_y = -1;
	input->pos_x = -1;
	input->pos_y = -1;
	input->direction = -1;
	input->h = 0;
	input->w = 0;
	input->no = NULL;
	input->so = NULL;
	input->we = NULL;
	input->ea = NULL;
	input->f_color = -1;
	input->c_color = -1;
	input->map = NULL;
	return (open(file, O_RDONLY));
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

char	*replace_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (white_space(line[i]) || line[i] == '\n')
			line[i] = '2';
		i++;
	}
	return (line);
}

void	free_tab_len(char **tab, int len)
{
	int	i;

	i = 0;
	len = 0;
	while (i < len)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

int	is_wall(char c)
{
	if (c == '1' || c == '2')
		return (1);
	return (0);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*s1;

	s1 = (char *)dst;
	i = 0;
	while (i < n)
	{
		*(char *)s1 = *(char *)src;
		s1++;
		src++;
		i++;
	}
	return (dst);
}
