#include"../cub3d.h"

// void draw_minimap_borderr(t_game *game)
// {
//     draw_line(&game->mlx.minimap_image, 0,0, MINI_WIDTH, 0);
//     draw_line(&game->mlx.minimap_image, 0, MINI_HEIGHT - 1, MINI_WIDTH, MINI_HEIGHT - 1);
//     draw_line(&game->mlx.minimap_image, 0, 0, 0, MINI_HEIGHT);
//     draw_line(&game->mlx.minimap_image, MINI_WIDTH - 1, 0, MINI_WIDTH - 1, MINI_HEIGHT - 1);
// }

int is_door(t_game *game, int x, int y)
{
	int i;

	i = 0;
	if (x <= 0 || y <= 0 || x >= game->map_width || y >= game->map_height)
		return (0);
	while (i < NUM_DOORS)
	{
		if (game->map[y][x] == '1' && (int)game->doors[i].x == x && (int)game->doors[i].y == y)
			return (1);
		i++;
	}
	return (0);
}

void draw_minimap(t_game *game)
{
	int player_map_x;
	int player_map_y;
	int start_x;
	int start_y;
	int end_x;
	int end_y;
	int x;
	int y;

	player_map_x = (int)(game->player.x / game->cube_size);
	player_map_y = (int)(game->player.y / game->cube_size);
	start_x = player_map_x - (int)(MINI_WIDTH / MINI_CUBE_SIZE / 2);
	start_y = player_map_y - (int)(MINI_HEIGHT / MINI_CUBE_SIZE / 2);
	end_x = player_map_x + (int)(MINI_WIDTH / MINI_CUBE_SIZE / 2) + 1;
	end_y = player_map_y + (int)(MINI_HEIGHT / MINI_CUBE_SIZE / 2) + 1;
	y = start_y;
	while (y < end_y)
	{
		x = start_x;
		while (x < end_x)
		{
			if (y >= 0 && y < game->map_height && x >= 0 && x < game->map_width)
			{
				if (is_door(game, x, y))
					draw_square(game, (x - start_x) * MINI_CUBE_SIZE, (y - start_y) * MINI_CUBE_SIZE, 0x00000000);
				else if (game->map[y][x] == '1')
					draw_square(game, (x - start_x) * MINI_CUBE_SIZE, (y - start_y) * MINI_CUBE_SIZE, 0xFF000000);
				else if (game->map[y][x] == '0')
					draw_square(game, (x - start_x) * MINI_CUBE_SIZE, (y - start_y) * MINI_CUBE_SIZE, 0x00FFFFFF);
			}
			x++;
		}
		y++;
	}

	// Draw player position on the mini-map
	double player_mini_x = ((game->player.x / game->cube_size) - start_x) * MINI_CUBE_SIZE;
	double player_mini_y = ((game->player.y / game->cube_size) - start_y) * MINI_CUBE_SIZE;
	draw_player(&game->mlx.minimap_image, player_mini_x, player_mini_y, 0x00000000, game);

//	draw_minimap_borderr(game);
	mlx_put_image_to_window(game->mlx.connect, game->mlx.window, game->mlx.minimap_image.ptr, 0, HEIGHT - MINI_HEIGHT);
}
