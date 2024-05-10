#include"../cub3d.h"

void get_start_point(int *start_x, int *start_y, int player_x, int player_y)
{
	int x;
	int y;
	
	y = 0;
	x = 0;
	while (y < player_y - (MINI_MAP_HEIGHT/ 2))
		y++;
	while (x < player_x - (MINI_MAP_WIDTH / 2))
		x++;
	*start_x = x;
	*start_y = y;
}

void draw_rectangle(t_img *img, int x, int y, int color)
{
	int i = 1;
	int j = 1;

	while (i < MINI_CUBE)
	{
		j = 1;
		while (j < MINI_CUBE)
		{
			my_mlx_pixel_put(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}
// void draw_player(t_img *img, int x, int y, int color)
// {
// 	int i = MINI_CUBE / 4;
// 	int j = MINI_CUBE / 4;

// 	while (i < (3*MINI_CUBE )/ 4)
// 	{
// 		j =  MINI_CUBE / 4;
// 		while (j < (3*MINI_CUBE )/ 4)
// 		{
// 			my_mlx_pixel_put(img, x + i, y + j, color);
// 			j++;
// 		}
// 		i++;
// 	}
	
// }

void draw_player(t_img *img, int x, int y, int color, t_game *game)
{
	int radius;
    int centerX;
    int centerY;
	int i;
	int j;
    radius = MINI_CUBE / 3;
	centerX = x + (MINI_CUBE / 2);
	centerY = y + (MINI_CUBE / 2);
	j = -radius;
    while (j <= radius)
	{
		i = -radius;
		while (i <= radius)
		{
			if (i * i + j * j <= radius * radius)
                my_mlx_pixel_put(img, centerX + i, centerY + j, color);
			i++;
		}
		j++;
	}
	draw_direction(img, centerX, centerY, game, MINI_CUBE);
}
void draw_line(t_img *img, int x, int y, int end_x, int end_y, int color)
{
    int dx;
    int dy;
    int sx;
    int sy;
    int err;

	dx = abs(end_x - x);
	dy = abs(end_y - y);
	err = dx - dy;
	if (end_x > x)
		sx = 1;
	else
		sx = -1;
	if (end_y > y)
		sy = 1;
	else	
		sy = -1;
    while (x != end_x || y != end_y)
	{
        my_mlx_pixel_put(img, x, y, color);
        if (err > -dy) {
            err -= dy;
            x += sx;
        }
        if (err < dx) {
            err += dx;
            y += sy;
        }
    }
}

void draw_direction(t_img *img, int x, int y, t_game *game, int length)
{
    int end_x;
    int end_y;

	end_x = x + (int)(length * game->player.x_dir);
	end_y = y - (int)(length * game->player.y_dir); // - because the Y axe is down in screen
    draw_line(img, x, y, end_x, end_y, 0x00FF0000);
}


// void draw_direction(t_img *img, int x, int y, t_game *game, int length)
// {
//     int end_x;
//     int end_y;
// 	int i;
// 	int j;

// 	end_x = x + (int)(length * game->player.x_dir);
// 	end_y = y + (int)(length * game->player.y_dir);
//     j = y;
// 	while (j <= end_y)
// 	{
// 		i = x;
// 		while (i <= end_x)
// 		{
//             my_mlx_pixel_put(img, x + i, y + j, 0X00FFFFFF);
// 			i++;
// 		}
// 		j++;
// 	}
// }
void draw_minimap(t_mlx *mlx, t_game *game, int player_y, int player_x)
{
	int start_x;
	int start_y;
	int x;
	int y;
	
	get_start_point(&start_x, &start_y, player_x, player_y);
	x = start_x;
	y = start_y;
	while ((y <= (MINI_MAP_HEIGHT/2 + player_y)) && y < game->map_height)
	{
		x = start_x;
		while ((x <= (MINI_MAP_WIDTH/2 + player_x)) && x < game->map_width)
		{
			if (game->map[y][x] == '0')
 				draw_rectangle(&mlx->minimap_image, (x - start_x)*MINI_CUBE, (y - start_y)*MINI_CUBE, 0X00FFFFFF);
			if (game->map[y][x] == '1')
 				draw_rectangle(&mlx->minimap_image, (x - start_x)*MINI_CUBE, (y - start_y)*MINI_CUBE, 0X000000FF);
			if (game->map[y][x] == '2')
 				draw_rectangle(&mlx->minimap_image, (x - start_x)*MINI_CUBE, (y - start_y)*MINI_CUBE, 0XEF00FF00);
			if (game->map[y][x] == 'Z')
 				draw_player(&mlx->minimap_image, (x - start_x)*MINI_CUBE, (y - start_y)*MINI_CUBE, 0X00FF0000, game);
			x++;
		}
		y++;
	}

	mlx_put_image_to_window(mlx->connect, mlx->window, mlx->minimap_image.ptr, WIDTH/2, HEIGHT/2);
}