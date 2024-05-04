
#include"cub3d.h"
void read_matrix(t_input *input)
{
	int i = 0;
	while(i < input->nbr_lines)
	{
		printf("%s,,", input->map[i]);
		printf("\n");
		i++;
	}
	printf("--> %s-**", input->map[i]);
}

int	main()
{
	t_input *input;
	
	input = parsing("map.cub");
	if(!input)
		return (1);
	read_matrix(input);
	return (0);
}
