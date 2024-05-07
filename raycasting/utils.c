
 #include"../cub3d.h"

double deg_to_rad(double degree)
{
	return (degree * M_PI / 180);
}
double rad_to_deg(double rad)
{
	return (rad * 180 / M_PI);
}

void	free_ptr(void *ptr)
{
	free (ptr);
	ptr = 0;
}
