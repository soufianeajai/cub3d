
#include"cub3d.h"

int	main()
{
	t_mlx	mlx;

	
	
	
	
	
	
	// ft_parse(ac, av, &mlx);
	// draw_set(&mlx);
	ft_connect(&mlx);
	mlx_put_image_to_window(mlx.connect, mlx.window, mlx.image.ptr, 0, 0);
	mlx_hook(mlx.window, 2, 1L << 2, &ft_close, &mlx);
	mlx_hook(mlx.window, 17, 1L << 17, &ft_close2, &mlx);
//	mlx_key_hook(mlx.window, &handle_keys, &mlx);
//	mlx_mouse_hook(mlx.window, &handle_mouse, &mlx);
	mlx_loop(mlx.connect);
//	system("leaks fractol");
	return (0);
}
