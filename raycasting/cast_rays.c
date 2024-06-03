#include "../cub3d.h"

t_ray	cast_ray(t_game *game, float ray_angle)
{
	t_ray	ray;
	t_ray	horizontal_intersection;
	t_ray	vertical_intersection;

	ray = init_ray(ray_angle);
	horizontal_intersection = get_intersection(game, ray, Y);
	vertical_intersection = get_intersection(game, ray, X);
	if (horizontal_intersection.distance < vertical_intersection.distance)
	{
		ray = horizontal_intersection;
		ray.orientation = set_orientation(&ray, Y);
		ray.texture_offset = fmod(ray.wall_hit.x, CUBE_SIZE);
	}
	else
	{
		ray = vertical_intersection;
		ray.vertical_hit = 1;
		ray.orientation = set_orientation(&ray, X);
		ray.texture_offset = fmod(ray.wall_hit.y, CUBE_SIZE);
	}
	ray.distance = ray.distance * cos(game->player.rotation_angle - ray.angle);
	return (ray);
}

void	cast_all_rays(t_game *game)
{
	float	ray_angle;
	int		column;

	column = 0;
	ray_angle = (game->player.rotation_angle) - (game->fov / 2);
	game->door = get_best_door(game);
	while (column < NUM_RAYS)
	{
		game->rays[column] = cast_ray(game, ray_angle);
		draw_column(game, column);
		ray_angle += game->angle_increment;
		column++;
	}
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx.connect, game->mlx.window,
		game->mlx.image.ptr, 0, 0);
}
