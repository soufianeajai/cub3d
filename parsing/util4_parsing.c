#include "parsing.h"

void	fill_desc_map(char *line, t_input *input, int *index_start_map,
		int *error)
{
	if (is_texture(line, input)== 1 && *error == 0)
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
		if (all_elements_set(input) && *index_start_map == 6) // last element set is map !!
		{
			if (input->W < ft_strlen(line))
				input->W = ft_strlen(line);
			input->H += 1;
		}
	}
}
int	check_espace(t_input *input, int i, int j, char type)
{
	
	if (type == '2')
	{
		if (i < 0 || i >= input->H || j < 0 || j >= input->W)
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

int	all_elements_set(t_input *input)
{
	if (input->no && input->so && input->we && input->ea && input->f_color != -1
		&& input->c_color != -1)
		return (1);
	return (0);
}
