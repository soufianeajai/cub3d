#include"../cub3d.h"

int is_door(t_game *game, int x, int y)
{
	int i;

	i = 0;
	if (x <= 0 || y <= 0 || x >= game->map_width || y >= game->map_height)
		return (0);
	while (i < game->nb_doors)
	{
		if (game->map[y][x] == '1' && (int)game->doors[i].x == x && (int)game->doors[i].y == y)
			return (1);
		i++;
	}
	return (0);
}
void draw(t_game *game, t_point start)
{
	int x;
	int y;
	int end_x;
	int end_y;

	end_x = (int)((int)game->player.x / CUBE_SIZE) + (int)(MINI_WIDTH / MINI_CUBE_SIZE / 2) + 1;
	end_y = (int)(((int)game->player.y / CUBE_SIZE)+ (int)(MINI_HEIGHT / MINI_CUBE_SIZE / 2)) + 1;
	y = (int)start.y - 1;
	while (++y < end_y)
	{
		x = (int)start.x - 1;
		while (++x < end_x)
		{
			if (y >= 0 && y < game->map_height && x >= 0 && x < game->map_width)
			{
				if (is_door(game, x, y))
					draw_square(game, (x - start.x) * MINI_CUBE_SIZE, (y - start.y) * MINI_CUBE_SIZE, 0x00000000);
				else if (game->map[(int)y][(int)x] == '1')
					draw_square(game, (x - start.x) * MINI_CUBE_SIZE, (y - start.y) * MINI_CUBE_SIZE, 0xFF000000);
				else if (game->map[(int)y][(int)x] == '0')
					draw_square(game, (x - start.x) * MINI_CUBE_SIZE, (y - start.y) * MINI_CUBE_SIZE, 0x00FFFFFF);
			}
		}
	}
}
void copy_image(t_game *game)
{
	int x;
	int y;
	int color;

	y = 0;
	while (y < MINI_HEIGHT)
	{
		x = 0;
		while (x < MINI_WIDTH)
		{
			color = get_texture_pixel(&game->mlx.minimap_image, x, y);
			my_mlx_pixel_put(&game->mlx.image, x, y + HEIGHT - MINI_HEIGHT, color);
			x++;
		}
		y++;
	}
}
void draw_minimap(t_game *game)
{
	t_point start;
	t_point mini_player;

	start.x = (int)(game->player.x / CUBE_SIZE) - (int)(MINI_WIDTH / MINI_CUBE_SIZE / 2);
	start.y = (int)(game->player.y / CUBE_SIZE) - (int)(MINI_HEIGHT / MINI_CUBE_SIZE / 2);
	draw(game, start);
	mini_player.x = ((game->player.x / CUBE_SIZE) - start.x) * MINI_CUBE_SIZE;
	mini_player.y = ((game->player.y / CUBE_SIZE) - start.y) * MINI_CUBE_SIZE;
	draw_player(game, mini_player);
	copy_image(game);
//	mlx_put_image_to_window(game->mlx.connect, game->mlx.window, game->mlx.image.ptr, 0, 0);
}
