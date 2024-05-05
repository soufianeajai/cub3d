
#ifndef CUB3D_H
# define CUB3D_H
# include<fcntl.h>
# include<mlx.h>
# include<stdlib.h>
# include<math.h>
# include<stdio.h>
# include<unistd.h>
#include "parsing/parsing.h"
# define HEIGHT 1024
# define WIDTH 1024
# define PI	3.1416
# define SIZE_CUBE 64
# define FOV 60
# define PLAYER_HEIGHT 32


typedef struct t_image {
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
  int   width;
  int   height;
}	t_img;

typedef struct s_mlx {
	int			type;
	void		*connect;
	void		*window;
	t_img		image;
  t_img		north_wall_image;
  t_img		south_wall_image;
  t_img		east_wall_image;
  t_img		west_wall_image;
}	t_mlx;

typedef struct s_point{
  int x;
  int y;
} t_point;

typedef struct s_game{
  t_mlx mlx;
  t_point player_pos;
  double player_direction;
  t_point projection_plane_center;
  double distance_projection_plane;
  double alpha_angle;
  int   rays_per_fov;
  double view_distance;
  double angle_between_rays;
  double angle_ray;
  char  **map;
  int   nbr_lines;
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

#endif
