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
void draw(t_game *game, t_point start, t_point end)
{
	t_point point;
	point.y = start.y;
	while (point.y < end.y)
	{
		point.x = start.x;
		while (point.x < end.x)
		{
			if (point.y >= 0 && point.y < game->map_height && point.x >= 0 && point.x < game->map_width)
			{
				if (is_door(game, point.x, point.y))
					draw_square(game, (point.x - start.x) * MINI_CUBE_SIZE, (point.y - start.y) * MINI_CUBE_SIZE, 0x00000000);
				else if (game->map[(int)point.y][(int)point.x] == '1')
					draw_square(game, (point.x - start.x) * MINI_CUBE_SIZE, (point.y - start.y) * MINI_CUBE_SIZE, 0xFF000000);
				else if (game->map[(int)point.y][(int)point.x] == '0')
					draw_square(game, (point.x - start.x) * MINI_CUBE_SIZE, (point.y - start.y) * MINI_CUBE_SIZE, 0x00FFFFFF);
			}
			point.x++;
		}
		point.y++;
	}
}
void draw_minimap(t_game *game)
{
	t_point start;
	t_point end;
	t_point mini_player;

	start.x = (int)(game->player.x / CUBE_SIZE) - (int)(MINI_WIDTH / MINI_CUBE_SIZE / 2);
	start.y = (int)(game->player.y / CUBE_SIZE) - (int)(MINI_HEIGHT / MINI_CUBE_SIZE / 2);
	end.x = (int)(game->player.x / CUBE_SIZE) + (int)(MINI_WIDTH / MINI_CUBE_SIZE / 2) + 1;
	end.y = (int)(game->player.y / CUBE_SIZE)+ (int)(MINI_HEIGHT / MINI_CUBE_SIZE / 2) + 1;
	draw(game, start, end);
	mini_player.x = ((game->player.x / CUBE_SIZE) - start.x) * MINI_CUBE_SIZE;
	mini_player.y = ((game->player.y / CUBE_SIZE) - start.y) * MINI_CUBE_SIZE;
	draw_player(game, mini_player);
	mlx_put_image_to_window(game->mlx.connect, game->mlx.window, game->mlx.minimap_image.ptr, 0, HEIGHT - MINI_HEIGHT);
}
