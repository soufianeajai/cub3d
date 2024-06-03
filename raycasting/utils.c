#include "../cub3d.h"

double	deg_to_rad(double degree)
{
	return (degree * M_PI / 180);
}
double	rad_to_deg(double rad)
{
	return (rad * 180 / M_PI);
}
float	calculate_distance(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

float	normalize_angle(float angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

void	free_ptr(void *ptr)
{
	free(ptr);
	ptr = 0;
}
