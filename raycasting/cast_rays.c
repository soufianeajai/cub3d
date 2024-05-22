#include"../cub3d.h"

float calculate_distance(float x1, float y1, float x2, float y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

float normalize_angle(float angle)
{
    angle = fmod(angle, 2 * M_PI);
    if (angle < 0)
        angle += 2 * M_PI;
    return angle;
}

t_ray init_ray(t_game *game, float ray_angle)
{
    t_ray ray;

    ray.angle = normalize_angle(ray_angle);
    ray.distance = INFINITY;
    ray.hit = 0;
    ray.start.x = game->player.x;
    ray.start.y = game->player.y;
    ray.wall_hit.x = 0;
    ray.wall_hit.y = 0;
    ray.is_facing_down = (ray.angle > 0 && ray.angle < M_PI);
    ray.is_facing_right = (ray.angle < M_PI_2 || ray.angle > (3 * M_PI_2));
    // Horizontal intersection
    ray.h_first_intersection.y = floor(ray.start.y / game->cube_size) * game->cube_size;
    if (ray.is_facing_down)
        ray.h_first_intersection.y += game->cube_size;
    ray.h_first_intersection.x = ray.start.x + (ray.h_first_intersection.y - ray.start.y) / tan(ray.angle);
    ray.h_step.y = game->cube_size * (ray.is_facing_down ? 1 : -1);
    ray.h_step.x = game->cube_size / tan(ray.angle);
    if ((!ray.is_facing_right && ray.h_step.x > 0) || (ray.is_facing_right && ray.h_step.x < 0))
        ray.h_step.x *= -1;
    // Vertical intersection
    ray.v_first_intersection.x = floor(ray.start.x / game->cube_size) * game->cube_size;
    if (ray.is_facing_right)
        ray.v_first_intersection.x += game->cube_size;
    ray.v_first_intersection.y = ray.start.y + (ray.v_first_intersection.x - ray.start.x) * tan(ray.angle);
    ray.v_step.x = game->cube_size * (ray.is_facing_right ? 1 : -1);
    ray.v_step.y = game->cube_size * tan(ray.angle);
    if ((!ray.is_facing_down && ray.v_step.y > 0) || (ray.is_facing_down && ray.v_step.y < 0))
        ray.v_step.y *= -1;
    return ray;
}

t_ray get_horizontal_intersection(t_game *game, t_ray ray)
{
    t_point next_intersection;

    next_intersection.x = ray.h_first_intersection.x;
    next_intersection.y = ray.h_first_intersection.y;
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
            ray.distance = calculate_distance(ray.start.x, ray.start.y, ray.wall_hit.x, ray.wall_hit.y);
            break;
        }
        next_intersection.x += ray.h_step.x;
        next_intersection.y += ray.h_step.y;
    }
    return ray;
}

t_ray get_vertical_intersection(t_game *game, t_ray ray)
{
    t_point next_intersection;

    next_intersection.x = ray.v_first_intersection.x;
    next_intersection.y = ray.v_first_intersection.y;
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
            ray.distance = calculate_distance(ray.start.x, ray.start.y, ray.wall_hit.x, ray.wall_hit.y);
            break;
        }
        next_intersection.x += ray.v_step.x;
        next_intersection.y += ray.v_step.y;
    }
    return ray;
}

t_ray cast_ray(t_game *game, float ray_angle)
{
    t_ray ray;
    t_ray horizontal_intersection;
    t_ray vertical_intersection;

    ray = init_ray(game, ray_angle);
    horizontal_intersection = get_horizontal_intersection(game, ray);
    vertical_intersection = get_vertical_intersection(game, ray);

    if (horizontal_intersection.distance < vertical_intersection.distance)
    {
        ray = horizontal_intersection;
        ray.vertical_hit = 0;
    }
    else
    {
        ray = vertical_intersection;
        ray.vertical_hit = 1;
    }
    return ray;
}

void cast_all_rays(t_game *game)
{
    float ray_angle;
    int column;

    column = 0;
    ray_angle = game->player.rotation_angle - (FOV / 2);
    while (column < NUM_RAYS)
    {
        game->rays[column] = cast_ray(game, ray_angle);
        ray_angle += ANGLE_INCREMENT;
        column++;
    }
    draw_map(game);
}