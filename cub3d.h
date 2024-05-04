
#ifndef CUB3D_H
# define CUB3D_H

# include<mlx.h>
# include<stdlib.h>
# include<math.h>
# include<stdio.h>
# include<unistd.h>
# define HEIGHT 1024
# define WIDTH 1024
# define PI	3.1416
# define SIZE_CUBE 64

typedef struct s_input {
  char  *no;
  char  *so;
  char  *we;
  char  *ea;
  int    c_color;
  int    f_color;
  double  direction;
  char  **map;
  int    pos_x;
  int    pos_y;
  int   nbr_lines;
}  t_input;

typedef struct t_image {
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_mlx {
	int			type;
	void		*connect;
	void		*window;
	t_img		image;

}	t_mlx;

int	ft_connect(t_mlx *mlx);
void	my_mlx_pixel_put(t_img *image, int x, int y, int color);
void	ft_error(void	*ptr, char *msg);
int	handle_keys(int keysym, t_mlx *mlx);
int	ft_close(int keysym, t_mlx *mlx);
int	ft_close2(t_mlx *mlx);
void	free_ptr(void *ptr);

#endif
