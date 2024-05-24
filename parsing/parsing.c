#include "parsing.h"

int	is_texture(char *line, t_input *input)
{
	int	i;

	i = 0;
	while (white_space(line[i]))
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O' && !input->no)
		return (input->no = fill_elements(line, i + 2),1);
	if (line[i] == 'S' && line[i + 1] == 'O' && !input->so)
		return (input->so = fill_elements(line, i + 2),1);
	if (line[i] == 'W' && line[i + 1] == 'E' && !input->we)
		return (input->we = fill_elements(line, i + 2),1);
	if (line[i] == 'E' && line[i + 1] == 'A' && !input->ea)
		return (input->ea = fill_elements(line, i + 2),1);
	if (line[i] == 'F' && line[i + 1] == ' ' && input->f_color == -1)
		return (input->f_color = fill_rgb(line, i + 1),1);
	if (line[i] == 'C' && input->c_color == -1)
		return (input->c_color = fill_rgb(line, i + 1),1);
	return (0);
}

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

char	**fill_map(t_input *input, char *file, int index_start_map)
{
	int		fd;
	char	*line;
	int		i;
	char	**map;

	i = -1;
	map = avance_line(index_start_map, file, &fd, input->H);
	while ((line = get_next_line(fd)) && map != NULL)
	{
		if (empty_line(line))
		{
			free(line);
			continue ;
		}
		if (is_not_map(line))
			return (free(line), ft_free(map), close(fd), printf("1HHHHHHHH\n"),NULL);
		if (++i <= input->H && i != -2)
			map[i] = get_full_len(line, input, &i);
		map[i + 1] = NULL;
		if (i == -2)
			return (free(line), ft_free(map), close(fd),printf("2HHHHHHHH\n"), NULL);
		free(line);
	}
	return (close(fd), map);
}



/*
				!is_valid_in_map(input, i - 1, j - 1, &check)
					|| !is_valid_in_map(input, i + 1, j - 1, &check) ||
				!is_valid_in_map(input, i - 1, j + 1, &check)
					|| !is_valid_in_map(input, i + 1, j + 1, &check)
*/

int	check_Error_espace(char **map, int i, t_input *input)
{
	int	j;

	j = -1;
	while (map[i][++j])
	{
		if (map[i][j] == '2' || map[i][j] == '0')
		{
			if (!check_espace(input, i, j - 1,map[i][j])
				|| !check_espace(input, i, j + 1,map[i][j]) ||
				!check_espace(input, i - 1, j,map[i][j])
					|| !check_espace(input, i + 1, j,map[i][j]))
			{
				printf("\nError : map[%d][%d] = %c\n", i, j, map[i][j]);
				return (0);
			}
		}
	}
	return (1);
}


int	parsing_map(char **map, t_input *input)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		if (i == 0 || i == input->H - 1)
		{
			while (map[i][++j])
				if (!is_wall(map[i][j]))
					return (0);
		}
		else
		{
			while (map[i][++j] && map[i][j] == '2')
				;
			if (map[i][j] != '1')
				return (0);
			j = input->W;
			while (map[i][--j] && map[i][j] == '2')
				;
			if (map[i][j] != '1')
				return (0);
			if (check_Error_espace(map, i, input) == 0)
				return (0);
		}
	}
	return (1);
}

int	parsing(char *file, t_input *input)
{
	char	*line;
	int		fd;
	int		index_start_map;
	int		error;

	error = 0;
	index_start_map = 0;
	fd = init_Data(input, file);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (empty_line(line))
		{
			free(line);
			continue ;
		}
		fill_desc_map(line, input, &index_start_map, &error);
		free(line);
	}
	if (input->H == 0 || index_start_map != 6)
		return (free_all_elements(input), 0);
	close(fd);
	input->map = fill_map(input, file, index_start_map);
	if (!input->map || parsing_map(input->map, input) == 0 || !all_elements_set(input,1))
		{
			printf("HHHHHHHH\n");
			return (free_all_elements(input), 0);}
		
	return (1);
}
