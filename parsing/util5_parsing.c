// int is_valid_door(t_input *input, int i, int j)
// {

// }
// int get_position_door(t_input *input)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	while (i < input->H)
// 	{
// 		j = 0;
// 		while (j < input->W)
// 		{
// 			if (input->map[i][j] == 'y' && is_valid_door(input, i, j))
// 			{
// 				input->door_x = j;
// 				input->door_y = i;
// 				return (1);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (0);
// }
// void flood_fill(t_input *input, int x, int y, char new_char)
// {
//     if (x < 0 || x >= input->W || y < 0 || y >= input->H || input->map[y][x] != '0')
//     {
// 		if (input->map[y][x] == '1' && x != 0 && y != 0 && x != input->W - 1 && y != input->H - 1)
// 			input->map[y][x] = 'y';
//         return;
//     }
//     input->map[y][x] = new_char;
//     flood_fill(input, x, y - 1, new_char);
//     flood_fill(input, x, y + 1, new_char);
//     flood_fill(input, x - 1, y, new_char);
//     flood_fill(input, x + 1, y, new_char);
// }
// x  = 0 , y = 1