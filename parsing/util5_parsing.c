#include "parsing.h"
// for 'y' = map[i][j]  we need to : 
// map[i][j - 1] or map[i][j +1] = y -> map[i-1][j] == '0' && map[i+1][j] == 'x' or inverse
// map[i + 1][j] or map[i - 1][j] = y ->  map[i][j - 1] == '0' && map[i][j + 1] == 'x' or inverse


int is_valid_door(t_input input, int i, int j)
{
    if (i == 0 || j == 0)
        return (0);
    if ((input.map[i][j - 1] == '0' && input.map[i][j + 1] == 'x') || (input.map[i][j - 1] == 'x' && input.map[i][j + 1] == '0'))
        if (input.map[i + 1][j] == 'y' && input.map[i - 1][j] == 'y')
            return (1);
    if ((input.map[i - 1][j] == '0' && input.map[i + 1][j] == 'x') || (input.map[i + 1][j] == 'x' && input.map[i - 1][j] == '0'))
        if (input.map[i][j + 1] == 'y' && input.map[i][j - 1] == 'y')
            return (1);
    return (0);
}
int get_position_door(t_input input, int *x, int *y, char **map)
{
	int i;
	int j;

	i = 0;
    flood_fill(input, input.pos_x, input.pos_y, map);
	while (i < input.H)
	{
		j = 0;
		while (j < input.W)
		{
			if (input.map[i][j] == 'y' && is_valid_door(input, i, j))
			{
				*x = j;
				*y = i;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
void flood_fill(t_input input, int x, int y, char **map)
{
    if (x < 0 || x >= input.W || y < 0 || y >= input.H || map[y][x] != '0')
    {
		if (map[y][x] == '1' && x != 0 && y != 0 && x != input.W - 1 && y != input.H - 1)
			map[y][x] = 'y';
        return;
    }
    map[y][x] = 'x';
    flood_fill(input, x, y - 1,map);
    flood_fill(input, x, y + 1,map);
    flood_fill(input, x - 1, y,map);
    flood_fill(input, x + 1, y,map);
}

void mise_a_jour_map(t_input input)
{
    int i;
    int j;

    i = 0;
    while (i < input.H)
    {
        j = 0;
        while (j < input.W)
        {
            if (input.map[i][j] == 'x')
                input.map[i][j] = '0';
            if (input.map[i][j] == 'y')
                input.map[i][j] = '1';
            j++;
        }
        i++;
    }
}

int	main(int ac , char **av)
{
	// t_game game;
	// t_mlx	mlx;
	// t_ray  rays[NUM_RAYS + 1];
	t_input input;

	if (!check_argument(ac, av) || !parsing(av[1],&input))
	{
		printf("Map Error\n");
		system("leaks cub3d");
		return (1);
	}
	get_position_door(input, &input.door_x, &input.door_y,input.map);
	mise_a_jour_map(input);
	printf("door x = %d door y = %d\n",input.door_x,input.door_y);
	read_matrix(input);
	// ft_connect(&mlx, &input);
	// game = init_game(mlx, input);
	// game.rays = rays;
 	// cast_all_rays(&game);
	// mlx_key_hook(mlx.window, &ft_close, &mlx);
	// // free input
 	// mlx_hook(mlx.window, 17,0, &ft_close2, &mlx);
	// // free input
	// mlx_hook(mlx.window, 2, 0, &handle_keys, &game);
	// mlx_hook(mlx.window, 6, 1L << 6,&mouse_move,&game);
 	// mlx_loop(mlx.connect);
	return (0);
}