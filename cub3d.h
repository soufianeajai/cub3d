#ifndef CUB3D_H
# define CUB3D_H
# include<fcntl.h>
# include "mlx.h"
# include<stdlib.h>
# include<math.h>
# include<stdio.h>
# include<unistd.h>
# include "parsing/parsing.h"
# define HEIGHT 640
# define WIDTH 1024
# define FOV deg_to_rad(60)
# define NUM_RAYS WIDTH
# define ANGLE_ANCREMENT (FOV / NUM_RAYS)
# define DISTANCE_TO_PP ((WIDTH / 2) / tan(FOV / 2))
# define MOVE_SPEED 10
# define ROTATION_SPEED deg_to_rad(10)
# define MINI_HEIGHT 216
# define MINI_WIDTH 216
# define MINI_CUBE_SIZE 24

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
}	t_mlx;

typedef struct s_player{
  float  x;
  float  y;
  int map_x;
  int map_y;
  float width;
  float height;
  int x_walk_dir;
  int y_walk_dir;
  int turn_direction;
  float rotation_angle;
  float walk_speed;
  float turn_speed;
} t_player;

typedef struct s_ray{
  double angle;
  double distance;
  int hit;
  int wall_hit_x;
  int wall_hit_y;
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
} t_game;

int	ft_connect(t_mlx *mlx);
void	my_mlx_pixel_put(t_img *image, int x, int y, int color);
void	ft_error(void	*ptr, char *msg);
int	handle_keys(int keysym, t_game *game);
int	ft_close(int keysym, t_mlx *mlx);
int	ft_close2(t_mlx *mlx);
void	free_ptr(void *ptr);
void get_images(t_mlx *mlx, t_input *input);
t_game init_game(t_mlx mlx, t_input input);
t_img  get_image_from_xpm(void *mlx_ptr, char *path_xpm);
void copy_image(t_img *image, t_img wall_image, int x, int y);
double deg_to_rad(double angle);
double rad_to_deg(double angle);
void read_matrix(t_input input);
void get_start_point(int *start_x, int *start_y, int player_x, int player_y);
void draw_square(t_game *game, int x, int y, int color);
void draw_map(t_game *game);
void draw_direction(t_img *img, int x, int y, t_game *game, float length);
void draw_player(t_img *img, int x, int y, int color, t_game *game);
void draw_minimap(t_game *game);
void draw_player_mini(t_img *img, int x, int y, int color, t_game *game);
void draw_mini_square(t_game *game, int x, int y, int color);
#endif
