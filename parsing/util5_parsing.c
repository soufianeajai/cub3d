#include "parsing.h"
#include"../cub3d.h"
// for 'y' = map[i][j]  we need to : 
// map[i][j - 1] or map[i][j +1] = y -> map[i-1][j] == '0' && map[i+1][j] == 'x' or inverse
// map[i + 1][j] or map[i - 1][j] = y ->  map[i][j - 1] == '0' && map[i][j + 1] == 'x' or inverse


int is_valid_door(t_input input, int i, int j)
{
    if (i == 0 || j == 0)
        return (0);
    if ((input.map[i][j - 1] == '0' && input.map[i][j + 1] == 'x') || (input.map[i][j - 1] == 'x' && input.map[i][j + 1] == '0'))
    {
        if (input.map[i + 1][j] == 'y' && input.map[i - 1][j] == 'y')
            return (1);
    }
    if ((input.map[i - 1][j] == '0' && input.map[i + 1][j] == 'x') || (input.map[i + 1][j] == '0' && input.map[i - 1][j] == 'x'))
    {
        if (input.map[i][j + 1] == 'y' && input.map[i][j - 1] == 'y')
            return (1);
    }
    return (0);
}

void get_doors(t_input *input)
{
    int x;
    int y;
    int i;

    i = -1;
    input->nb_doors = 0;
    while (input->nb_doors < NUM_DOORS)
    {
        if(!get_position_door(*input, &x, &y, input->map))
            break;
        input->door[input->nb_doors].x = x;
        input->door[input->nb_doors].y = y;
        input->map[y][x] = '0';
        input->nb_doors++;
        mise_a_jour_map(input);
        
    }
    mise_a_jour_map(input);
    while (++i < input->nb_doors)
        input->map[(int)input->door[i].y][(int)input->door[i].x] = '1';
        printf("nb doors = %d\n", input->nb_doors);
}
int get_position_door(t_input input, int *x, int *y, char **map)
{
	int i;
	int j;

	i = 0;
    flood_fill(input, input.pos_x, input.pos_y, map);
	while (i < input.H)
	{
		j = 0;
		while (j < input.W)
		{
			if (input.map[i][j] == 'y' && is_valid_door(input, i, j))
			{
				*x = j;
				*y = i;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}


// void flood_fill(t_input input, int x, int y, char **map)
// {
//     if (x < 0 || x >= input.W || y < 0 || y >= input.H || map[y][x] != '0')
//     {
// 		if (map[y][x] == '1' && x != 0 && y != 0 && x != input.W - 1 && y != input.H - 1)
// 			map[y][x] = 'y';
//         return;
//     }
//     map[y][x] = 'x';
//     flood_fill(input, x, y - 1,map);
//     flood_fill(input, x, y + 1,map);
//     flood_fill(input, x - 1, y,map);
//     flood_fill(input, x + 1, y,map);
// }

void flood_fill(t_input input, int x, int y, char **map)
{
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};

    int head = 0, tail = 0;
    t_point *queue = malloc(input.W * input.H * sizeof(t_point));
    queue[tail++] = (t_point){x, y};

    while (head < tail)
    {
        t_point p = queue[head++];
        if (p.x < 0 || p.x >= input.W || p.y < 0 || p.y >= input.H || map[(int)p.y][(int)p.x] != '0')
        {
            if (map[(int)p.y][(int)p.x] == '1' && p.x != 0 && p.y != 0 && p.x != input.W - 1 && p.y != input.H - 1)
                map[(int)p.y][(int)p.x] = 'y';
            continue;
        }

        map[(int)p.y][(int)p.x] = 'x';

       for (int i = 0; i < 4; i++)
        {
            int nx = p.x + dx[i];
            int ny = p.y + dy[i];
            if (nx >= 0 && nx < input.W && ny >= 0 && ny < input.H)
            {
                if (tail >= input.W * input.H)
                {
                    // Queue is full, stop the function or reallocate more memory
                    free(queue);
                    return;
                }
                queue[tail++] = (t_point){nx, ny};
            }
        }
    }

    free(queue);
}

void mise_a_jour_map(t_input *input)
{
    int i;
    int j;

    i = 0;
    while (i < input->H)
    {
        j = 0;
        while (j < input->W)
        {
            if (input->map[i][j] == 'x')
                input->map[i][j] = '0';
            if (input->map[i][j] == 'y')
                input->map[i][j] = '1';
            if (input->map[i][j] == '2')
                input->map[i][j] = '1';
            j++;
        }
        i++;
    }
}

