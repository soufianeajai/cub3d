#include"../cub3d.h"

void draw_map(t_game *game)
{
	int i;
	int j;
	int x;
	int y;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			x = j * game->cube_size;
			y = i * game->cube_size;
			if (game->map[i][j] == '1')
				draw_square(game, x, y, 0x00000000);
			else if (game->map[i][j] == '0')
				draw_square(game, x, y, 0x00FFFFFF);
			else if (game->map[i][j] == '2')
				draw_square(game, x, y, 0x000000FF);
			j++;
		}
		i++;
	}
	draw_player(&game->mlx.image, game->player.x, game->player.y, 0x00FF0000, game);
	mlx_put_image_to_window(game->mlx.connect, game->mlx.window, game->mlx.image.ptr, 0, 0);
}
void draw_minimap_borderr(t_game *game)
{
    draw_line(&game->mlx.minimap_image, 0,0, MINI_WIDTH, 0);
    draw_line(&game->mlx.minimap_image, 0, MINI_HEIGHT - 1, MINI_WIDTH, MINI_HEIGHT - 1);
    draw_line(&game->mlx.minimap_image, 0, 0, 0, MINI_HEIGHT);
    draw_line(&game->mlx.minimap_image, MINI_WIDTH - 1, 0, MINI_WIDTH - 1, MINI_HEIGHT - 1);
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
				if (game->map[y][x] == '1')
					draw_mini_square(game, (x - start_x) * MINI_CUBE_SIZE, (y - start_y) * MINI_CUBE_SIZE, 0x000000FF);
				else if (game->map[y][x] == '0')
					draw_mini_square(game, (x - start_x) * MINI_CUBE_SIZE, (y - start_y) * MINI_CUBE_SIZE, 0x00FFFFFF);
				else if (game->map[y][x] == '2')
					draw_mini_square(game, (x - start_x) * MINI_CUBE_SIZE, (y - start_y) * MINI_CUBE_SIZE, 0x000000FF);
			}
			x++;
		}
		y++;
	}

	// Draw player position on the mini-map
	double player_mini_x = ((game->player.x / game->cube_size) - start_x) * MINI_CUBE_SIZE;
	double player_mini_y = ((game->player.y / game->cube_size) - start_y) * MINI_CUBE_SIZE;
	draw_player_mini(&game->mlx.minimap_image, player_mini_x, player_mini_y, 0x00FF0000, game);

	draw_minimap_borderr(game);
	mlx_put_image_to_window(game->mlx.connect, game->mlx.window, game->mlx.minimap_image.ptr, 0, HEIGHT - MINI_HEIGHT);
}
