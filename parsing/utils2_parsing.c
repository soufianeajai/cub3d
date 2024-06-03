/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util3_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:16:13 by afanidi           #+#    #+#             */
/*   Updated: 2024/06/02 20:16:15 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!white_space(line[i]))
			return (0);
		i++;
	}
	return (1);
}

char	*fill_elements(char *line, int i)
{
	int		j;
	char	*str;

	j = i;
	if (empty_line(line))
		return (NULL);
	while (white_space(line[i]))
		i++;
	if (j == i)
		return (NULL);
	str = ft_substr(line, i, ft_strlen(line) - i - 1);
	return (str);
}

int	check_digits(char **str)
{
	int	i;
	int	j;
	int	flag;

	j = 0;
	i = 0;
	while (j < 3)
	{
		i = 0;
		flag = 0;
		while (str[j][i])
		{
			while (white_space(str[j][i]) && flag == 0)
				i++;
			flag = 1;
			if (!ft_isdigit(str[j][i]) && str[j][i] != '\n')
				return (0);
			i++;
		}
		j++;
	}
	return (1);
}

int	fill_rgb(char *line, int i)
{
	long	r;
	long	g;
	long	b;
	char	**tab;
	int		j;

	tab = ft_split(line + i, ',', &j);
	if (!tab || j != 3 || !check_digits(tab))
	{
		ft_free(tab);
		return (-1);
	}
	r = ft_atoi(tab[0]);
	g = ft_atoi(tab[1]);
	b = ft_atoi(tab[2]);
	if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255)
	{
		ft_free(tab);
		return ((int)((r << 16) + (g << 8) + b));
	}
	ft_free(tab);
	return (-1);
}
