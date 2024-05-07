#include"../cub3d.h"
void get_images(t_mlx *mlx, t_input *input)
{
	mlx->north_wall_image = get_image_from_xpm(mlx->connect, input->no);
	mlx->south_wall_image = get_image_from_xpm(mlx->connect, input->so);
	mlx->east_wall_image = get_image_from_xpm(mlx->connect, input->ea);
	mlx->west_wall_image = get_image_from_xpm(mlx->connect, input->we);
}

t_img  get_image_from_xpm(void *mlx_ptr, char *path_xpm)
{
  t_img img;

  img.ptr = mlx_xpm_file_to_image(mlx_ptr, path_xpm, &img.width, &img.height);
  if (!img.ptr)
  {
	printf("The xpm file is invalid %s\n", path_xpm);
	// to free the memory
	exit(0);
  }
  img.addr = mlx_get_data_addr(img.ptr, &img.bpp, &img.line_len, &img.endian);
  return (img);
}
void read_matrix(t_input input)
{
    int i = 0;
    while(input.map[i] != NULL)
    {
        printf("%s", input.map[i]);
        printf("\n");
        i++;
    }
}
void copy_image(t_img *image, t_img image_to_copy, int x, int y)
{
	int i = 0;
	int j = 0;
	int color;
	while (i < image_to_copy.width)
	{
		j = 0;
		while (j < image_to_copy.height)
		{
			color = *(int *)(image_to_copy.addr + (j * image_to_copy.line_len + i * (image_to_copy.bpp / 8)));
			my_mlx_pixel_put(image, x + i, y + j, color);
			j++;
		}
		i++;
	}
}
void	my_mlx_pixel_put(t_img *image, int x, int y, int color)
{
	char	*pixel;
	int		offset;

	offset = y * image->line_len + x * (image->bpp / 8);
	pixel = image->addr + offset;
	*(int *)pixel = color;
}