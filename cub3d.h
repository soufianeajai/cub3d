/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sajaite <sajaite@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:43:37 by afanidi           #+#    #+#             */
/*   Updated: 2024/06/09 18:08:38 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <limits.h>
# include "parsing/parsing.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define HEIGHT 1000
# define WIDTH 1600
# define CUBE_SIZE 64
# define NUM_RAYS WIDTH
# define MOVE_SPEED 15
# define MINI_HEIGHT 132
# define MINI_WIDTH 180
# define MINI_CUBE_SIZE 12

typedef enum s_wall_orientation
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	DOOR,
}						t_wall_orientation;

typedef enum s_axes
{
	X,
	Y,
}						t_axes;

typedef struct t_image
{
	void				*ptr;
	char				*addr;
	int					bpp;
	int					line_len;
	int					endian;
	int					width;
	int					height;
	int					mini_cube;
}						t_img;

typedef struct s_mlx
{
	int					type;
	void				*connect;
	void				*window;
	t_img				minimap_image;
	t_img				image;
	t_img				north_wall_image;
	t_img				south_wall_image;
	t_img				east_wall_image;
	t_img				west_wall_image;
	t_img				door_image;
}						t_mlx;

typedef struct s_player
{
	float				x;
	float				y;
	int					turn_direction;
	float				rotation_angle;
}						t_player;

typedef struct s_ray
{
	float				angle;
	float				distance;
	bool				is_wall;
	bool				is_facing_down;
	bool				is_facing_right;
	bool				vertical_hit;
	float				texture_offset;
	t_point				wall_hit;
	t_wall_orientation	orientation;
}						t_ray;

typedef struct s_game
{
	t_mlx				mlx;
	t_player			player;
	t_ray				*rays;
	char				**map;
	int					map_width;
	int					map_height;
	int					c_color;
	int					f_color;
	t_point				door;
	t_point				doors[NBR_DOORS];
	int					nb_doors;
	bool				door_open;
	int					last_mouse_x;
	float				fov;
	double				angle_increment;
	float				distance_to_projection_plan;
	float				rotation_speed;
	float				move_speed;
	t_input				input;
}						t_game;

float					calculate_distance(float x1, float y1, float x2,
							float y2);
t_mlx					ft_connect(t_input *input);
void					my_mlx_pixel_put(t_img *image, int x, int y, int color);
void					ft_error(t_mlx *mlx, char *msg, t_input *input,
							int free_flag);
int						track_mouse_position(t_game *game);
int						mouse_move(int x, int y, t_game *game);
int						handle_keys(int keysym, t_game *game);
int						ft_close(t_game *game);
void					free_ptr(void *ptr);
int						get_images(t_mlx *mlx, t_input *input);
t_game					init_game(t_mlx mlx, t_input input);
int						get_image_from_xpm(void *mlx_ptr, char *path_xpm,
							t_img *img);
double					deg_to_rad(double angle);
double					rad_to_deg(double angle);
void					draw_square(t_game *game, int x, int y, int color);
void					draw_player(t_game *game, t_point player);
void					draw_minimap(t_game *game);
void					cast_all_rays(t_game *game);
t_ray					cast_ray(t_game *game, float ray_angle);
float					normalize_angle(float angle);
int						is_door(t_game *game, int x, int y);
int						get_texture_pixel(t_img *texture, int x, int y);
void					draw_line(t_img *img, t_point start, t_point end);
void					draw_rectangle(t_game *game, int start_x, int height,
							int color);
void					check_start_end(int *start, int *end, float *y,
							float step);
void					draw_textured_wall(t_game *game, int column,
							float wall_height, t_img *texture);
void					draw_column(t_game *game, int column);
t_img					*get_orientation_texture(t_game *game,
							t_wall_orientation orientation);
t_point					get_first_intersection(t_game *game, t_ray *ray,
							t_axes axis);
t_point					get_step(t_ray *ray, t_axes axis);
int						intersection_found(t_game *game, t_ray *ray,
							t_point next_intersection, t_point to_check);
t_ray					get_intersection(t_game *game, t_ray ray, t_axes axis);
void					check_direction(t_point *to_check, t_ray *ray,
							t_axes axis);
t_point					get_best_door(t_game *game);
t_ray					init_ray(float ray_angle);
t_wall_orientation		set_orientation(t_ray *ray, t_axes axis);
t_img					*get_orientation_texture(t_game *game,
							t_wall_orientation orientation);
void					handle_arrows(t_game *game, int keysym);
#endif
