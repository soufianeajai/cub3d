#ifndef CUB3D_H
# define CUB3D_H
# include<fcntl.h>
# include "mlx.h"
# include<stdlib.h>
# include<math.h>
# include<stdio.h>
# include<unistd.h>
# include <stdbool.h>
# include "parsing/parsing.h"
# define HEIGHT 900
# define WIDTH 1500
# define FOV deg_to_rad(60)
# define NUM_RAYS WIDTH
# define ANGLE_INCREMENT (FOV / NUM_RAYS)
# define DISTANCE_TO_PP ((WIDTH / 2) / tan(FOV / 2))
# define MOVE_SPEED 15
# define ROTATION_SPEED deg_to_rad(8)
# define MINI_HEIGHT 130
# define MINI_WIDTH 180
# define MINI_CUBE_SIZE 12
# define RIGHT_ARROW 124
# define LEFT_ARROW 123
# define W_KEY 13
# define S_KEY 1
# define A_KEY 0
# define D_KEY 2
# define MAX_DISTANCE 300
# define NUM_DOORS 100

typedef enum {
    NORTH,
    SOUTH,
    EAST,
    WEST,
    DOOR,
} wall_orientation;

typedef enum {
  X,
  Y,
} axes;

typedef struct t_image {
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
  int   width;
  int   height;
  int   mini_cube;
}	t_img;

typedef struct s_mlx {
	int			type;
	void		*connect;
	void		*window;
  t_img   minimap_image;
	t_img		image;
  t_img		north_wall_image;
  t_img		south_wall_image;
  t_img		east_wall_image;
  t_img		west_wall_image;
  t_img		door_image;
}	t_mlx;


typedef struct s_player{
  float  x;
  float  y;
  int map_x;
  int map_y;
  int turn_direction;
  float rotation_angle;
  float walk_speed;
  float turn_speed;
} t_player;

typedef struct s_ray{
  float angle;
  float distance;
  bool is_wall;
  bool is_facing_down;
  bool is_facing_right;
  bool vertical_hit;
  float texture_offset;
  t_point wall_hit;
  wall_orientation orientation;
} t_ray;


typedef struct s_game{
  t_mlx mlx;
  t_player player;
  t_ray *rays;
  char  **map;
  int  map_width;
  int  map_height;
  int cube_size;
  int   c_color;
  int   f_color;
  t_point door;
  t_point doors[NUM_DOORS];
  int nb_doors;
  bool door_open;
  int last_mouse_x;
} t_game;

float calculate_distance(float x1, float y1, float x2, float y2);
int	ft_connect(t_mlx *mlx, t_input *input);
void	my_mlx_pixel_put(t_img *image, int x, int y, int color);
void	ft_error(void	*ptr, char *msg,t_input *input);
int mouse_move(int x, int y, t_game *game);
int	handle_keys(int keysym, t_game *game);
int	ft_close(int keysym, t_mlx *mlx);
int	ft_close2(t_mlx *mlx);
void	free_ptr(void *ptr);
int get_images(t_mlx *mlx, t_input *input);
t_game init_game(t_mlx mlx, t_input input);
int  get_image_from_xpm(void *mlx_ptr, char *path_xpm, t_img *img);
double deg_to_rad(double angle);
double rad_to_deg(double angle);
void read_matrix(t_input input);
void draw_square(t_game *game, int x, int y, int color);
void draw_direction(t_img *img, int x, int y, t_game *game, int length);
void draw_player(t_img *img, int x, int y, int color, t_game *game);
void draw_minimap(t_game *game);
void cast_all_rays(t_game *game);
void draw_line(t_img *img, int x, int y, int end_x, int end_y);
int get_cube_size(t_game game);
t_ray cast_ray(t_game *game, float ray_angle);
float normalize_angle(float angle);
int is_door(t_game *game, int x, int y);

#endif
