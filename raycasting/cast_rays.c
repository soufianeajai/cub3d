#include "../cub3d.h"

float	calculate_distance(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

float	normalize_angle(float angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

t_point	get_first_intersection(t_game *game, t_ray *ray, axes axis)
{
	t_point	first_intersection;

	if (axis == Y)
	{
		first_intersection.y = floor(game->player.y / game->cube_size)
			* game->cube_size;
		if (ray->is_facing_down)
			first_intersection.y += game->cube_size;
		first_intersection.x = game->player.x + (first_intersection.y
				- game->player.y) / tan(ray->angle);
	}
	else
	{
		first_intersection.x = floor(game->player.x / game->cube_size)
			* game->cube_size;
		if (ray->is_facing_right)
			first_intersection.x += game->cube_size;
		first_intersection.y = game->player.y + (first_intersection.x
				- game->player.x) * tan(ray->angle);
	}
	return (first_intersection);
}

t_ray	init_ray(float ray_angle)
{
	t_ray	ray;

	ray.angle = normalize_angle(ray_angle);
	ray.distance = INT32_MAX;
	ray.is_wall = 1;
	ray.wall_hit.x = 0;
	ray.wall_hit.y = 0;
	ray.is_facing_down = (ray.angle > 0 && ray.angle < M_PI);
	ray.is_facing_right = (ray.angle < M_PI_2 || ray.angle > (3 * M_PI_2));
	return (ray);
}

t_point	get_step(t_game *game, t_ray *ray, axes axis)
{
	t_point	step;

	if (axis == Y)
	{
		step.y = game->cube_size;
		if (!ray->is_facing_down)
			step.y *= -1;
		step.x = game->cube_size / tan(ray->angle);
		if ((!ray->is_facing_right && step.x > 0) || (ray->is_facing_right
				&& step.x < 0))
			step.x *= -1;
	}
	else
	{
		step.x = game->cube_size;
		if (!ray->is_facing_right)
			step.x *= -1;
		step.y = game->cube_size * tan(ray->angle);
		if ((!ray->is_facing_down && step.y > 0) || (ray->is_facing_down
				&& step.y < 0))
			step.y *= -1;
	}
	return (step);
}

t_ray	get_horizontal_intersection(t_game *game, t_ray ray)
{
    t_point next_intersection;
    t_point step;
    t_point to_check;
    int i;

    i = -1;
    next_intersection = get_first_intersection(game, &ray, Y);
    step = get_step(game, &ray, Y);
    while (next_intersection.x >= 0 && next_intersection.x < game->map_width * game->cube_size &&
           next_intersection.y >= 0 && next_intersection.y < game->map_height * game->cube_size)
    {
        to_check = next_intersection;
        if (!ray.is_facing_down)
            to_check.y--;
        if (game->map[(int)(to_check.y / game->cube_size)][(int)(to_check.x / game->cube_size)] == '1')
        {
			if (is_door(game, (int)(to_check.x / game->cube_size), (int)(to_check.y / game->cube_size)))
			{
				ray.is_wall = 0;
				if (game->door_open)
				game->door = game->doors[i];		
			}
            // if ((int)(to_check.y / game->cube_size) == game->door.y && (int)(to_check.x / game->cube_size) == game->door.x && !game->door_open)
            //     ray.is_wall = 0;

        // while (++i < game->nb_doors)
        // {
        //     if ((int)(to_check.y / game->cube_size) == game->doors[i].y && (int)(to_check.x / game->cube_size) == game->doors[i].x)
        //     {
        //         ray.is_wall = 0;
        //         ray.wall_hit.x = next_intersection.x;
        //         ray.wall_hit.y = next_intersection.y;
        //         ray.distance = calculate_distance(game->player.x, game->player.y, ray.wall_hit.x, ray.wall_hit.y);
        //         game->door = game->doors[i];
        //         break;
        //     }
        
            ray.wall_hit.x = next_intersection.x;
            ray.wall_hit.y = next_intersection.y;
            ray.distance = calculate_distance(game->player.x, game->player.y, ray.wall_hit.x, ray.wall_hit.y);
            break;
        }
        next_intersection.x += step.x;
        next_intersection.y += step.y;
    }
    return (ray);
}

t_ray	get_vertical_intersection(t_game *game, t_ray ray)
{
    t_point next_intersection;
    t_point step;
    t_point to_check;
    int i;

    i = -1;
    next_intersection = get_first_intersection(game, &ray, X);
    step = get_step(game, &ray, X);
    while (next_intersection.x >= 0 && next_intersection.x < game->map_width * game->cube_size &&
           next_intersection.y >= 0 && next_intersection.y < game->map_height * game->cube_size)
    {
        to_check = next_intersection;
        if (!ray.is_facing_right)
            to_check.x--;
        if (game->map[(int)(to_check.y / game->cube_size)][(int)(to_check.x / game->cube_size)] == '1')
        {
			if (is_door(game, (int)(to_check.x / game->cube_size), (int)(to_check.y / game->cube_size)))
			{

					ray.is_wall = 0;
				if (game->door_open)
				game->door = game->doors[i];		
			}

            // if ((int)(to_check.y / game->cube_size) == game->door.y && (int)(to_check.x / game->cube_size) == game->door.x && !game->door_open)
            //     ray.is_wall = 0;

        // while (++i < game->nb_doors)
        // {
        //     if ((int)(to_check.y / game->cube_size) == game->doors[i].y && (int)(to_check.x / game->cube_size) == game->doors[i].x)
        //     {
        //         ray.is_wall = 0;
        //         ray.wall_hit.x = next_intersection.x;
        //         ray.wall_hit.y = next_intersection.y;
        //         ray.distance = calculate_distance(game->player.x, game->player.y, ray.wall_hit.x, ray.wall_hit.y);
        //         game->door = game->doors[i];
        //         break;
        //     }
        // }



            ray.wall_hit.x = next_intersection.x;
            ray.wall_hit.y = next_intersection.y;
            ray.distance = calculate_distance(game->player.x, game->player.y, ray.wall_hit.x, ray.wall_hit.y);
            break;
        }
        next_intersection.x += step.x;
        next_intersection.y += step.y;
    }
    return (ray);
}
wall_orientation	get_orientation(t_ray *ray, axes axis)
{
	wall_orientation	orientation;

	if (axis == Y)
	{
		if (ray->is_facing_down)
			orientation = SOUTH;
		else
			orientation = NORTH;
	}
	else
	{
		if (ray->is_facing_right)
			orientation = EAST;
		else
			orientation = WEST;
	}
	if (!ray->is_wall)
		orientation = DOOR;
	return (orientation);
}
t_ray	cast_ray(t_game *game, float ray_angle)
{
	t_ray	ray;
	t_ray	horizontal_intersection;
	t_ray	vertical_intersection;

	ray = init_ray(ray_angle);
	horizontal_intersection = get_horizontal_intersection(game, ray);
	vertical_intersection = get_vertical_intersection(game, ray);
	if (horizontal_intersection.distance < vertical_intersection.distance)
	{
		ray = horizontal_intersection;
		ray.orientation = get_orientation(&ray, Y);
		ray.texture_offset = fmod(ray.wall_hit.x, game->cube_size);
	}
	else
	{
		ray = vertical_intersection;
		ray.vertical_hit = 1;
		ray.orientation = get_orientation(&ray, X);
		ray.texture_offset = fmod(ray.wall_hit.y, game->cube_size);
	}
	ray.distance = ray.distance * cos(ray.angle
			- (game->player.rotation_angle));
	return (ray);
}

void	draw_rectangle(t_game *game, int start_x, int height, int color)
{
	int	j;

	j = 0;
	while (j < height)
	{
		if (start_x >= 0 && start_x < WIDTH && j >= 0 && j < HEIGHT)
			my_mlx_pixel_put(&game->mlx.image, start_x, + j, color);
		j++;
	}
}

int	blend_colors(int pixel_color, float distance)
{
	float			factor;
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;

	factor = expf(-5.0 * (distance / WIDTH));
	red = ((pixel_color >> 16) % 256) * factor;
	green = ((pixel_color >> 8) % 256) * factor;
	blue = (pixel_color % 256) * factor;
	return ((red << 16) + (green << 8) + blue);
}

int	get_texture_pixel(t_img *texture, int x, int y, float distance)
{
	int		pixel_color;
	char	*pixel;

	pixel = texture->addr + (y * texture->line_len + x * (texture->bpp / 8));
	pixel_color = *(int *)pixel;
	pixel_color = blend_colors(pixel_color, distance);
	return (pixel_color);
}

t_img	*get_orientation_texture(t_game *game, wall_orientation orientation)
{
	t_img	*texture;

	if (orientation == NORTH)
		texture = &game->mlx.north_wall_image;
	else if (orientation == SOUTH)
		texture = &game->mlx.south_wall_image;
	else if (orientation == EAST)
		texture = &game->mlx.east_wall_image;
	else if (orientation == WEST)
		texture = &game->mlx.west_wall_image;
	else
		texture = &game->mlx.door_image;
	return (texture);
}

void	check_start_end(int *start, int *end, float *y, float step)
{
	if (*start < 0)
	{
		*y = -*start * step;
		*start = 0;
	}
	if (*end >= HEIGHT)
		*end = HEIGHT;
}
void	draw_textured_wall(t_game *game, int column, float wall_height,
		t_img *texture)
{
	t_point	texture_pos;
	int		start_y;
	int		end_y;
	int		y;
	float	step;

	texture_pos.x = (int)(game->rays[column].texture_offset / game->cube_size
			* texture->width);
	start_y = (game->map_height * game->cube_size / 2) - (wall_height / 2);
	end_y = start_y + wall_height;
	step = (float)texture->height / wall_height;
	texture_pos.y = 0;
	check_start_end(&start_y, &end_y, &texture_pos.y, step);
	y = start_y;
	while (y < end_y)
	{
		my_mlx_pixel_put(&game->mlx.image, column, y, get_texture_pixel(texture,
				texture_pos.x, texture_pos.y, game->rays[column].distance));
		get_texture_pixel(texture, texture_pos.x, texture_pos.y,
			game->rays[column].distance);
		texture_pos.y += step;
		y++;
	}
}

void	draw_column(t_game *game, int column)
{
	float	wall_height;
	t_img	*texture;

	wall_height = (game->cube_size / game->rays[column].distance)
		* DISTANCE_TO_PP;
	draw_rectangle(game, column, HEIGHT, game->f_color);
	draw_rectangle(game, column, (game->map_height * game->cube_size
			- wall_height) / 2, game->c_color);
	texture = get_orientation_texture(game, game->rays[column].orientation);
	draw_textured_wall(game, column, wall_height, texture);
}
t_point	get_best_door(t_game *game)
{
	t_point	door;
	float	distance;
	float	best_distance;
	int		i;

	i = 0;
	distance = calculate_distance(game->player.x / game->cube_size,
			game->player.y / game->cube_size, game->doors[0].x,
			game->doors[0].y);
	door = game->doors[0];
	while (++i < game->nb_doors)
	{
		best_distance = calculate_distance(game->player.x / game->cube_size,
				game->player.y / game->cube_size, game->doors[i].x,
				game->doors[i].y);
		if (best_distance < distance)
		{
			distance = best_distance;
			door = game->doors[i];
		}
	}
	return (door);
}

void	cast_all_rays(t_game *game)
{
	float	ray_angle;
	int		column;

    column = 0;
    ray_angle = (game->player.rotation_angle) - (FOV / 2);
    game->door = get_best_door(game);
    while (column < NUM_RAYS)
    {
        game->rays[column] = cast_ray(game, ray_angle);
        draw_column(game, column);
        ray_angle += ANGLE_INCREMENT;
        column++;
    }
    mlx_put_image_to_window(game->mlx.connect, game->mlx.window, game->mlx.image.ptr, 0, 0);
    draw_minimap(game);
}
