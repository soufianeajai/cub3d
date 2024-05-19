#include"../cub3d.h"

float calculate_distance(float x1, float y1, float x2, float y2)
{
    return (sqrt((x2 - x1) * (x2 - y1) + (y2 - y1) * (y2 - y1)));
}
int init_ray(t_game *game, t_ray *ray, float ray_angle, int *map_y)
{
    int map_x;

    ray->start.x = game->player.x;
    ray->start.y = game->player.y;
    ray->d.x = cos(ray_angle);
    ray->d.y = sin(ray_angle);
    ray->delta_distance.x = fabs(1 / ray->d.x);
    ray->delta_distance.y = fabs(1 / ray->d.y);
    map_x = (int)(ray->start.x / game->cube_size);
    *map_y = (int)(ray->start.y / game->cube_size);
    ray->hit = 0;
    ray->wall_hit.x = 0;
    ray->wall_hit.y = 0;
    ray->distance = -1;
    return (map_x);
}
void handle_start_point(t_game *game, t_ray *ray, int map_x, int map_y)
{
    if (ray->d.x < 0) 
    {
        ray->step.x = -1;
        ray->side_distance.x = (ray->start.x - map_x * game->cube_size) * ray->delta_distance.x;
    }
    else if (ray->d.x >= 0)
    {
        ray->step.x = 1;
        ray->side_distance.x = ((map_x + 1) * game->cube_size - ray->start.x) * ray->delta_distance.x;
    }
    if (ray->d.y < 0)
    {
        ray->step.y = -1;
        ray->side_distance.y = (ray->start.y - map_y * game->cube_size) * ray->delta_distance.y;
    }
    else if (ray->d.y >= 0)
    {
        ray->step.y = 1;
        ray->side_distance.y = ((map_y + 1) * game->cube_size - ray->start.y) * ray->delta_distance.y;
    }
}
wall_orientation get_orientation(float step, axes axis)
{
    wall_orientation orientation;
    
    if (axis == X)
    {
        if (step == -1)
            orientation = WEST;
        else
            orientation = EAST;
    }
    else
    {
        if (step == -1)
            orientation = NORTH;
        else
            orientation = SOUTH;
    }
    return (orientation);
}
void update_axes(t_ray *ray, int *map_, axes axis)
{
    if (axis == X)
    {
        ray->side_distance.x += ray->delta_distance.x;
        *map_ += ray->step.x;
        ray->orientation = get_orientation(ray->step.x, axis);
    }
    else
    {
        ray->side_distance.y += ray->delta_distance.y;
        *map_ += ray->step.y;
        ray->orientation = get_orientation(ray->step.y, axis);
    }
}
void get_ray_length(t_ray *ray, t_game *game)
{
    ray->wall_hit.x = ray->start.x + (ray->side_distance.x - ray->delta_distance.x) * ray->d.x;
    ray->wall_hit.y = ray->start.y + (ray->side_distance.y - ray->delta_distance.y) * ray->d.y;
    ray->distance = calculate_distance(game->player.x, game->player.y, ray->wall_hit.x, ray->wall_hit.y);
}
t_ray cast_ray(t_game *game, float ray_angle)
{
    t_ray ray;
    int map_x;
    int map_y;
    
    map_x = init_ray(game, &ray, ray_angle, &map_y);
    handle_start_point(game, &ray, map_x, map_y);   
    while (!ray.hit) 
    {
        if (ray.side_distance.x < ray.side_distance.y)
            update_axes(&ray, &map_x, X);
        else
            update_axes(&ray, &map_y, Y);
        if (map_x >= 0 && map_x < game->map_width && map_y >= 0 && map_y < game->map_height)
        {
            if (game->map[map_y][map_x] == '1')
                ray.hit = 1;
        }
        else
            return (ray);
    }
    get_ray_length(&ray, game);
    return (ray);
}
// void render_walls(t_game *game, t_ray *rays, int colum_id)
// {

// }

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
        colum_id++;
    }
//    render_walls(game, &rays, colum_id);
}