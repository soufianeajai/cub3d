#include"cub3d.h"
int check_argument(int ac, char **av)
{
	int fd;

	if (ac != 2)
		return (0);
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
		return (0);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

void read_matrix(t_input input)
{
    int i = 0;
    while(input.map[i] != NULL)
    {
        printf("%s", input.map[i]);
        printf("\n");
        i++;
    }
}

int	main(int ac , char **av)
{
	t_game game;
	t_mlx	mlx;
	t_input input;
	t_ray  rays[NUM_RAYS + 1];
	
	if (!check_argument(ac, av) || !parsing(av[1], &input))
		return (printf("Error\n"),1);
	
	get_doors(&input);
	//read_matrix(input);
	mlx = ft_connect(&input);
	game = init_game(mlx, input);
	game.rays = rays;
	cast_all_rays(&game);
	mlx_key_hook(game.mlx.window, &ft_close, &game.mlx);
	mlx_hook(game.mlx.window, 17,0, &ft_close2, &game.mlx);
	mlx_hook(game.mlx.window, 2, 0, &handle_keys, &game);
	mlx_hook(game.mlx.window, 6, 1L << 6,&mouse_move,&game);
	mlx_loop(game.mlx.connect);
	return (0);
}
t_game init_game(t_mlx mlx, t_input input)
{
	t_game game;

	game.mlx = mlx;
	game.map = input.map;
	game.map_height = input.h;
	game.map_width = input.w;
	game.c_color = input.c_color;
	game.f_color = input.f_color;
	game.player.x = (input.pos_x * CUBE_SIZE) + CUBE_SIZE / 2;
	game.player.y = (input.pos_y * CUBE_SIZE) + CUBE_SIZE / 2;
	game.player.turn_direction = 0;
	game.player.rotation_angle = deg_to_rad(input.direction);
	game.last_mouse_x = -1;
	game.door.x = -1;
	game.door.y = -1;
	if (input.nb_doors > 0)
	{
		game.door.x = input.door[0].x;
		game.door.y = input.door[0].y;
		game.nb_doors = input.nb_doors;
		ft_memcpy(game.doors, input.door, sizeof(t_point) * NUM_DOORS);
	}
	game.door_open = 0;
	return (game);
}
