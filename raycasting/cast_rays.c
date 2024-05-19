#include"../cub3d.h"

float calculate_distance(float x1, float y1, float x2, float y2) {
    return sqrt((x2 - x1) * (x2 - y1) + (y2 - y1) * (y2 - y1));
}

t_ray cast_ray(t_game *game, float ray_angle)
{
    t_ray ray;
    return (ray);
}
float cast(Game *game, float ray_angle, WallOrientation *orientation) {
    float ray_x = game->player.x;
    float ray_y = game->player.y;
    float ray_dx = cos(ray_angle);
    float ray_dy = sin(ray_angle);

    float delta_dist_x = fabs(1 / ray_dx);
    float delta_dist_y = fabs(1 / ray_dy);

    int map_x = (int)(ray_x / game->cube_size);
    int map_y = (int)(ray_y / game->cube_size);

    int step_x, step_y;
    float side_dist_x, side_dist_y;

    if (ray_dx < 0) {
        step_x = -1;
        side_dist_x = (ray_x - map_x * game->cube_size) * delta_dist_x;
    } else {
        step_x = 1;
        side_dist_x = ((map_x + 1) * game->cube_size - ray_x) * delta_dist_x;
    }

    if (ray_dy < 0) {
        step_y = -1;
        side_dist_y = (ray_y - map_y * game->cube_size) * delta_dist_y;
    } else {
        step_y = 1;
        side_dist_y = ((map_y + 1) * game->cube_size - ray_y) * delta_dist_y;
    }

    int hit = 0;
    while (!hit) {
        if (side_dist_x < side_dist_y) {
            side_dist_x += delta_dist_x;
            map_x += step_x;
            *orientation = (step_x == -1) ? WEST : EAST;
        } else {
            side_dist_y += delta_dist_y;
            map_y += step_y;
            *orientation = (step_y == -1) ? NORTH : SOUTH;
        }

        if (map_x >= 0 && map_x < game->map.width && map_y >= 0 && map_y < game->map.height) {
            if (game->map.map[map_y][map_x] == '1') {
                hit = 1;
            }
        } else {
            return -1; // No wall found within bounds
        }
    }

    float hit_x = ray_x + (side_dist_x - delta_dist_x) * ray_dx;
    float hit_y = ray_y + (side_dist_y - delta_dist_y) * ray_dy;

    return calculate_distance(game->player.x, game->player.y, hit_x, hit_y);
}


void cast_all_rays(t_game *game)
{
    int colum_id;
    float ray_angle;
    t_ray  rays[NUM_RAYS + 1];
    int i;

    i = 0;
    colum_id = 0;
    ray_angle = game->player.rotation_angle - (FOV / 2);
    while (i < NUM_RAYS)
    {
        rays[i] = cast_ray(game, ray_angle);
        ray_angle += ANGLE_ANCREMENT;
        i += WALL_STRIP_WIDTH;
    }
}