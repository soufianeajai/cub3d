/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util5_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:17:32 by afanidi           #+#    #+#             */
/*   Updated: 2024/06/02 20:17:34 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "parsing.h"

void	fill_list(int dx[4], int dy[4])
{
	int	i;

	i = -1;
	while (++i < 2)
	{
		dx[i] = 0;
		dy[i + 2] = 0;
	}
	dx[i++] = -1;
	dx[i] = 1;
	dy[0] = -1;
	dy[1] = 1;
	return ;
}

int	check_point(t_point p, t_input *input, char **map)
{
	if (p.x < 0 || p.x >= input->w || p.y < 0 || p.y >= input->h
		|| map[(int)p.y][(int)p.x] != '0')
	{
		if (map[(int)p.y][(int)p.x] == '1' && p.x != 0 && p.y != 0
			&& p.x != input->w - 1 && p.y != input->h - 1)
			map[(int)p.y][(int)p.x] = 'y';
		return (1);
	}
	map[(int)p.y][(int)p.x] = 'x';
	return (0);
}

void	process_directions(t_input input, t_point p, t_point **queue, int *tail)
{
	int	i;
	int	dx[4];
	int	dy[4];
	int	nx;
	int	ny;

	i = -1;
	fill_list(dx, dy);
	while (++i < 4)
	{
		nx = p.x + dx[i];
		ny = p.y + dy[i];
		if (nx >= 0 && nx < input.w && ny >= 0 && ny < input.h)
		{
			if (*tail >= input.w * input.h)
			{
				free(*queue);
				*queue = NULL;
				return ;
			}
			(*queue)[(*tail)++] = (t_point){nx, ny};
		}
	}
}

void	flood_fill(t_input input, int x, int y, char **map)
{
	t_point	*queue;
	int		head;
	int		tail;
	t_point	p;

	head = 0;
	queue = malloc(input.w * input.h * sizeof(t_point));
	tail = 0;
	queue[tail++] = (t_point){x, y};
	while (head < tail)
	{
		p = queue[head++];
		if (check_point(p, &input, map))
			continue ;
		process_directions(input, p, &queue, &tail);
		if (queue == NULL)
			return ;
	}
	free(queue);
}

void	mise_a_jour_map(t_input *input)
{
	int	i;
	int	j;

	i = 0;
	while (i < input->h)
	{
		j = 0;
		while (j < input->w)
		{
			if (input->map[i][j] == 'x')
				input->map[i][j] = '0';
			if (input->map[i][j] == 'y')
				input->map[i][j] = '1';
			if (input->map[i][j] == '2')
				input->map[i][j] = '1';
			j++;
		}
		i++;
	}
}
