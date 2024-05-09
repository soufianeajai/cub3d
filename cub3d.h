
#ifndef CUB3D_H
# define CUB3D_H
# include<fcntl.h>
# include<mlx.h>
# include<stdlib.h>
# include<math.h>
# include<stdio.h>
# include<unistd.h>
# include "parsing/parsing.h"
# define HEIGHT 640
# define WIDTH 1024
# define SIZE_CUBE 64
# define MINI_HEIGHT 108
# define MINI_WIDTH 108
# define MINI_CUBE 12
# define MINI_MAP_WIDTH (MINI_WIDTH / MINI_CUBE)
# define MINI_MAP_HEIGHT (MINI_HEIGHT / MINI_CUBE)
# define FOV deg_to_rad(60)
# define NUM_RAYS WIDTH
# define PLAYER_HEIGHT 32
# define ANGLE_ANCREMENT (FOV / NUM_RAYS)
# define DISTANCE_TO_PP ((WIDTH / 2) / tan(FOV / 2))


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
  int x;
  int y;
  int x_dir;
  int y_dir;
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
  int   c_color;
  int   f_color;
} t_game;

int	ft_connect(t_mlx *mlx);
void	my_mlx_pixel_put(t_img *image, int x, int y, int color);
void	ft_error(void	*ptr, char *msg);
int	handle_keys(int keysym, t_mlx *mlx);
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

#endif
