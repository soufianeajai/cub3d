#include"../cub3d.h"

float calculate_distance(float x1, float y1, float x2, float y2)
{
    return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

// void handle_start_point(t_game *game, t_ray *ray, int map_x, int map_y)
// {
//     if (ray->d.x < 0) 
//     {
//         ray->step.x = -1;
//         ray->side_distance.x = (ray->start.x - map_x * game->cube_size) * ray->delta_distance.x;
//     }
//     else if (ray->d.x >= 0)
//     {
//         ray->step.x = 1;
//         ray->side_distance.x = ((map_x + 1) * game->cube_size - ray->start.x) * ray->delta_distance.x;
//     }
//     if (ray->d.y < 0)
//     {
//         ray->step.y = -1;
//         ray->side_distance.y = (ray->start.y - map_y * game->cube_size) * ray->delta_distance.y;
//     }
//     else if (ray->d.y >= 0)
//     {
//         ray->step.y = 1;
//         ray->side_distance.y = ((map_y + 1) * game->cube_size - ray->start.y) * ray->delta_distance.y;
//     }
// }
// wall_orientation get_orientation(float step, axes axis)
// {
//     wall_orientation orientation;
    
//     if (axis == X)
//     {
//         if (step == -1)
//             orientation = WEST;
//         else
//             orientation = EAST;
//     }
//     else
//     {
//         if (step == -1)
//             orientation = NORTH;
//         else
//             orientation = SOUTH;
//     }
//     return (orientation);
// }
// void update_axes(t_ray *ray, int *map_, axes axis)
// {
//     if (axis == X)
//     {
//         ray->side_distance.x += ray->delta_distance.x;
//         *map_ += ray->step.x;
//         ray->orientation = get_orientation(ray->step.x, axis);
//     }
//     else
//     {
//         ray->side_distance.y += ray->delta_distance.y;
//         *map_ += ray->step.y;
//         ray->orientation = get_orientation(ray->step.y, axis);
//     }
// }
// // void get_ray_length(t_ray *ray, t_game *game)
// // {
// //     ray->wall_hit.x = ray->start.x + (ray->side_distance.x - ray->delta_distance.x) * ray->d.x;
// //     ray->wall_hit.y = ray->start.y + (ray->side_distance.y - ray->delta_distance.y) * ray->d.y;
// //     ray->distance = calculate_distance(game->player.x, game->player.y, ray->wall_hit.x, ray->wall_hit.y);
// // }

// void get_ray_length(t_ray *ray, int map_x, int map_y)
// {
//     if (ray->hit)
//     {
//         if (ray->orientation == EAST || ray->orientation == WEST)
//             ray->distance = (map_x - ray->start.x + (1 - ray->step.x) / 2) / ray->d.x;
//         else
//             ray->distance = (map_y - ray->start.y + (1 - ray->step.y) / 2) / ray->d.y;
//         ray->wall_hit.x = ray->start.x + ray->distance * ray->d.x;
//         ray->wall_hit.y = ray->start.y + ray->distance * ray->d.y;
//     }
// }
// t_ray cast_ray(t_game *game, float ray_angle)
// {
//     t_ray ray;
//     int map_x;
//     int map_y;
    
//     map_x = init_ray(game, &ray, ray_angle, &map_y);
//     handle_start_point(game, &ray, map_x, map_y);   
//     while (!ray.hit) 
//     {
//         if (ray.side_distance.x < ray.side_distance.y)
//             update_axes(&ray, &map_x, X);
//         else
//             update_axes(&ray, &map_y, Y);
//         if (map_x >= 0 && map_x < game->map_width && map_y >= 0 && map_y < game->map_height)
//         {
//             if (game->map[map_y][map_x] == '1')
//                 ray.hit = 1;
//         }
//         // else
//         //     return (ray);
//     }
//     get_ray_length(&ray, map_x, map_y);
//     return (ray);
// }
// t_img *get_texture(wall_orientation orientation, t_game *game)
// {
//     t_img *texture;
     
//     texture = 0;
//     if (orientation == NORTH)
//         texture = &game->mlx.north_wall_image;
//     else if (orientation == SOUTH)
//         texture = &game->mlx.south_wall_image;
//     else if (orientation == EAST)
//         texture = &game->mlx.east_wall_image;
//     else if (orientation == WEST)
//         texture = &game->mlx.west_wall_image;   
//     return (texture);
// }

// unsigned int get_texture_color(t_img *texture, int x, int y)
// {
//     char *pixel;
//     pixel = texture->addr + (y * texture->line_len + x * (texture->bpp / 8));
//     return (*(unsigned int*)pixel);
// }


// // void render_wall(t_game *game, t_ray *ray, float ray_angle, int column)
// // {

// // }
// this is soo my angle wont be negative or more than 2 PI
float normalize_angle(float angle)
{
    angle = (int)angle % (int)(2 * M_PI);
    if (angle < 0)
        angle += (float)(2 * M_PI);
    return (angle);
}
// int init_ray(t_game *game, t_ray *ray, float ray_angle, int *map_y)
// {
//     int map_x;

//     ray->angle = ray_angle;
//     ray->distance = -1;
//     ray->hit = 0;
//     ray->start.x = game->player.x;
//     ray->start.y = game->player.y;
//     ray->d.x = cos(ray_angle);
//     ray->d.y = sin(ray_angle);
//     ray->step.x = 0;
//     ray->step.y = 0;
//     ray->delta_distance.x = fabs(1 / ray->d.x);
//     ray->delta_distance.y = fabs(1 / ray->d.y);
//     ray->side_distance.x = 0;
//     ray->side_distance.y = 0;
//     ray->wall_hit.x = 0;
//     ray->wall_hit.y = 0;
//     map_x = (int)(ray->start.x / game->cube_size);
//     *map_y = (int)(ray->start.y / game->cube_size);
//     return (map_x);
// }



t_ray init_ray(t_game *game, float ray_angle)
{
    t_ray ray;

    ray.angle = normalize_angle(ray_angle);
    ray.distance = 0;
    ray.hit = 0;
    ray.start.x = game->player.x;
    ray.start.y = game->player.y;
    ray.wall_hit.x = 0;
    ray.wall_hit.y = 0;
    ray.is_facing_down = 0;
    ray.is_facing_right = 0;
    if (ray.angle > 0 && ray.angle < M_PI)
        ray.is_facing_down = 1;
    if (ray.angle < M_PI_2 && ray.angle > (3 * M_PI_2))
        ray.is_facing_right = 1;
    ray.h_first_intersection.y = floor(ray.start.y / game->cube_size) * game->cube_size;
    if (ray.is_facing_down)
        ray.h_first_intersection.y += game->cube_size;
    ray.h_first_intersection.x = ray.start.x + (ray.h_first_intersection.y - ray.start.y) / tan(ray.angle);
    ray.h_step.y = game->cube_size;
    if (ray.is_facing_down == 0)
        ray.h_step.y *= -1;
    ray.h_step.x = ray.h_step.y / tan(ray_angle);
    if (ray.is_facing_right == 0 && ray.h_step.x > 0)
        ray.h_step.x *= -1;
    if (ray.is_facing_right && ray.h_step.x < 0)
        ray.h_step.x *= -1;
// vertical intersection
    ray.v_first_intersection.x = floor(ray.start.x / game->cube_size) * game->cube_size; // a revoir
    ray.v_first_intersection.y = ray.start.y + (ray.h_first_intersection.x - ray.start.x) * tan(ray.angle); // a revoir
    ray.v_step.x = game->cube_size;
    ray.v_step.y = ray.v_step.x * tan(ray_angle); 
    return (ray);
}
t_ray get_horizontal_distance(t_game *game, t_ray ray)
{
    float distance;
    t_point next_intersection;

    distance = 0;
    next_intersection.x = ray.h_first_intersection.x;
    next_intersection.y = ray.h_first_intersection.y;
    if (ray.is_facing_down == 0)
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
        }
        else
        {
            next_intersection.x += ray.h_step.x;
            next_intersection.y += ray.h_step.y;
        }
    }
    return (ray);
}
t_ray cast_ray(t_game *game, float ray_angle)
{
    t_ray ray;
    t_ray horizontal_intersection;
    t_ray vertical_intersection;

    ray = init_ray(game, ray_angle);
    horizontal_intersection = get_horizontal_distance(game, ray);

    return (ray);
}


void cast_all_rays(t_game *game)
{
    float ray_angle;
    t_ray  rays[NUM_RAYS + 1];
    int column;

    column = 0;
    ray_angle = game->player.rotation_angle - (FOV / 2);
    while (column < NUM_RAYS)
    {
        rays[column] = cast_ray(game, ray_angle);
        render_wall(game, &rays[column], ray_angle, column);
        ray_angle += ANGLE_ANCREMENT;
        column++;
    }
}