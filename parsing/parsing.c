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
	str = ft_substr(line, i, ft_strlen(line) - i);
	return (str);
}

int	check_digits(char **str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (j < 3)
	{
		i = 0;
		while (white_space(str[0][i]))
			i++;
		while (str[j][i])
		{
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

int	is_texture(char *line, t_input *input)
{
	int	i;

	i = 0;
	while (white_space(line[i]))
		i++;
	if (line[i] && line[i + 1])
	{
		if (line[i] == 'N' && line[i + 1] == 'O' && !input->no)
			input->no = fill_elements(line, i + 2);
		else if (line[i] == 'S' && line[i + 1] == 'O' && !input->so)
			input->so = fill_elements(line, i + 2);
		else if (line[i] == 'W' && line[i + 1] == 'E' && !input->we)
			input->we = fill_elements(line, i + 2);
		else if (line[i] == 'E' && line[i + 1] == 'A' && !input->ea)
			input->ea = fill_elements(line, i + 2);
		else if (line[i] == 'F' && line[i + 1] == ' ' && input->f_color == -1)
			input->f_color = fill_rgb(line, i + 1);
		else if (line[i] == 'C' && input->c_color == -1)
			input->c_color = fill_rgb(line, i + 1);
		else
			return (0);
		return (1);
	}
	return (0);
}

int	all_elements_set(t_input *input)
{
	if (input->no && input->so && input->we && input->ea && input->f_color != -1
		&& input->c_color != -1)
		return (1);
	return (0);
}

void	fill_desc_map(char *line, t_input *input, int *index_start_map,
		int *error)
{
	if (is_texture(line, input) && *error == 0)
	{
		*index_start_map += 1;
		return ;
	}
	else
	{
		*error = 1;
		if (all_elements_set(input)) // last element set is map !!
		{
			if (input->W < ft_strlen(line))
				input->W = ft_strlen(line);
			input->H += 1;
		}
	}
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
			return (free(line), ft_free(map), close(fd), NULL);
		if (++i <= input->H && i != -2)
			map[i] = get_full_len(line, input, &i);
		map[i + 1] = NULL;
        if (i == -2)
            return (free(line), ft_free(map), close(fd), NULL);
		free(line);
	}
    
	return (close(fd), map);
}

int parsing_map(char **map, int H, int W)
{
    int i;
    int j;

    i = -1;
    

    while (map[++i])
    {
        j = -1;
        if (i == 0 || i == H - 1)
        {
            while (map[i][++j])
            {
                if (!is_wall(map[i][j]))
                {
                    printf("\nError : map[%d][%d] = %c\n",i,j,map[i][j]);
                    return (0);
                }
            }
        }
        else
        {
            while (map[i][++j] && map[i][j] == '2');
            if (map[i][j] != '1')
                return (0);
            j = W;
            while (map[i][--j] && map[i][j] == '2');
            if (map[i][j] != '1')
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
	// we have nomber line for map :
	printf("\n h = %d, w = %d, index_startmap : %d \n", input->H, input->W,
			index_start_map);
	if (input->H == 0 || index_start_map != 6)
		return (free_all_elements(input), 0);
	close(fd);
	input->map = fill_map(input, file, index_start_map);
	if (!input->map || parsing_map(input->map, input->H , input->W) == 0)
        return (free_all_elements(input), 0);
	return (1);
}
