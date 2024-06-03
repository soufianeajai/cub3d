/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:00:20 by afanidi           #+#    #+#             */
/*   Updated: 2024/06/03 18:00:21 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

int	is_direction(char c)
{
	if (c == 'N')
		return (270);
	if (c == 'S')
		return (90);
	if (c == 'E')
		return (0);
	if (c == 'W')
		return (180);
	return (-1);
}
