#include"../cub3d.h"

int calculate_distance(float x1, float y1, float x2, float y2)
{
    return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

float normalize_angle(float angle)
{
    angle = fmod(angle, 2 * M_PI);
    if (angle < 0)
        angle += 2 * M_PI;
    return angle;
}

t_point get_first_intersection(t_game *game, t_ray *ray, axes axis)
{
    t_point first_intersection;

    if (axis == Y)
    {
        first_intersection.y = floor(game->player.y / game->cube_size) * game->cube_size;
        if (ray->is_facing_down)
            first_intersection.y += game->cube_size;
        first_intersection.x = game->player.x + (first_intersection.y - game->player.y) / tan(ray->angle);
    }
    else
    {
        first_intersection.x = floor(game->player.x / game->cube_size) * game->cube_size;
        if (ray->is_facing_right)
            first_intersection.x += game->cube_size;
        first_intersection.y = game->player.y + (first_intersection.x - game->player.x) * tan(ray->angle);
    }
    return (first_intersection);
}

t_ray init_ray(float ray_angle)
{
    t_ray ray;

    ray.angle = normalize_angle(ray_angle);
    ray.distance = INT32_MAX;
    ray.hit = 0;
    ray.wall_hit.x = 0;
    ray.wall_hit.y = 0;
    ray.is_facing_down = (ray.angle > 0 && ray.angle < M_PI);
    ray.is_facing_right = (ray.angle < M_PI_2 || ray.angle > (3 * M_PI_2));
    return (ray);
}

t_point get_step(t_game *game, t_ray *ray, axes axis)
{
    t_point step;

    if (axis == Y)
    {
        step.y = game->cube_size;
        if (!ray->is_facing_down)
            step.y *= -1;
        step.x = game->cube_size / tan(ray->angle);
        if ((!ray->is_facing_right && step.x > 0) || (ray->is_facing_right && step.x < 0))
            step.x *= -1;
    }
    else
    {
        step.x = game->cube_size;
        if (!ray->is_facing_right)
            step.x *= -1;
        step.y = game->cube_size * tan(ray->angle);
        if ((!ray->is_facing_down && step.y > 0) || (ray->is_facing_down && step.y < 0))
            step.y *= -1;
    }
    return (step);
}

t_ray get_horizontal_intersection(t_game *game, t_ray ray)
{
    t_point next_intersection;
    t_point step;

    next_intersection = get_first_intersection(game, &ray, Y);
    step = get_step(game, &ray, Y);
    if (!ray.is_facing_down)
        next_intersection.y--;
    while (next_intersection.x >= 0 && next_intersection.x < game->map_width * game->cube_size &&
           next_intersection.y >= 0 && next_intersection.y < game->map_height * game->cube_size)
    {
        if (game->map[(int)(next_intersection.y / game->cube_size)][(int)(next_intersection.x / game->cube_size)] == '1')
        {
            ray.hit = 1;
            ray.wall_hit.x = next_intersection.x;
            ray.wall_hit.y = next_intersection.y;
            ray.distance = calculate_distance(game->player.x, game->player.y, ray.wall_hit.x, ray.wall_hit.y);
            ray.distance = ray.distance * cos(ray.angle - normalize_angle(game->player.rotation_angle));
            break;
        }
        next_intersection.x += step.x;
        next_intersection.y += step.y;
    }
    return (ray);
}

t_ray get_vertical_intersection(t_game *game, t_ray ray)
{
    t_point next_intersection;
    t_point step;

    next_intersection = get_first_intersection(game, &ray, X);
    step = get_step(game, &ray, X);
    if (!ray.is_facing_right)
        next_intersection.x--;
    while (next_intersection.x >= 0 && next_intersection.x < game->map_width * game->cube_size &&
           next_intersection.y >= 0 && next_intersection.y < game->map_height * game->cube_size)
    {
        if (game->map[(int)(next_intersection.y / game->cube_size)][(int)(next_intersection.x / game->cube_size)] == '1')
        {
            ray.hit = 1;
            ray.wall_hit.x = next_intersection.x;
            ray.wall_hit.y = next_intersection.y;
            ray.distance = calculate_distance(game->player.x, game->player.y, ray.wall_hit.x, ray.wall_hit.y);
            ray.distance = ray.distance * cos(ray.angle - normalize_angle(game->player.rotation_angle));
            break;
        }
        next_intersection.x += step.x;
        next_intersection.y += step.y;
    }
    return (ray);
}

t_ray cast_ray(t_game *game, float ray_angle)
{
    t_ray ray;
    t_ray horizontal_intersection;
    t_ray vertical_intersection;

    ray = init_ray(ray_angle);
    horizontal_intersection = get_horizontal_intersection(game, ray);
    vertical_intersection = get_vertical_intersection(game, ray);

    if (horizontal_intersection.distance < vertical_intersection.distance)
    {
        ray = horizontal_intersection;
        ray.vertical_hit = 0;
        if (ray.is_facing_down)
            ray.orientation = SOUTH;
        else
            ray.orientation = NORTH;
    }
    else
    {
        ray = vertical_intersection;
        ray.vertical_hit = 1;
        if (ray.is_facing_right)
            ray.orientation = EAST;
        else
            ray.orientation = WEST;
    }
    return (ray);
}

void black_screen(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (i < WIDTH)
    {
        j = 0;
        while (j < HEIGHT)
        {
            my_mlx_pixel_put(&game->mlx.image, i, j, 0x00000000);
            j++;
        }
        i++;
    }
}

void draw_rec(t_game *game, int start_x, int start_y, int width, int height, int color)
{
    int i;
    int j;

    i = 0;
    while (i < width)
    {
        j = 0;
        while (j < height)
        {
            if (start_x + i >= 0 && start_x + i < WIDTH && start_y + j >= 0 && start_y + j < HEIGHT)
                my_mlx_pixel_put(&game->mlx.image, start_x + i, start_y + j, color);
            j++;
        }
        i++;
    }
}

void cast_all_rays(t_game *game)
{
    float ray_angle;
    int column;
    int wall_height;

    column = 0;
    ray_angle = game->player.rotation_angle - (FOV / 2);
    black_screen(game);
    while (column < NUM_RAYS)
    {
        game->rays[column] = cast_ray(game, ray_angle);
        wall_height = (game->cube_size * DISTANCE_TO_PP)/ game->rays[column].distance;
        draw_rec(game, column * WALL_STRIP_WIDTH, (game->map_height * game->cube_size - wall_height) / 2, WALL_STRIP_WIDTH, wall_height, 0x00FFFFFF);
        ray_angle += ANGLE_INCREMENT;
        column++;
    }
    mlx_put_image_to_window(game->mlx.connect, game->mlx.window, game->mlx.image.ptr, 0, 0);
//    draw_map(game);
}