#include "parsing.h"

void fill_desc_map(char *line, t_input *input, int *index, size_t *len)
{
    char *id;

    id = ft_substr(line, 0, 2);
    if (!ft_strcmp(id,"NO"))
        input->no =ft_substr(line, 3, ft_strlen(line + 3) - 1);
    else if (!ft_strcmp(id,"SO"))
        input->so =ft_substr(line, 3, ft_strlen(line + 3) - 1);
    else if (!ft_strcmp(id,"WE"))
        input->we =ft_substr(line, 3, ft_strlen(line + 3) - 1);
    else if (!ft_strcmp(id,"EA"))
        input->ea =ft_substr(line, 3, ft_strlen(line + 3) - 1);
    else if (!ft_strcmp(id,"F "))
        input->f_color = (220 << 16) + (100 << 8) + 0;
    else if (!ft_strcmp(id,"C "))
        input->f_color = (225 << 16) + (30 << 8) + 0;
    else
    {
        if (*len < ft_strlen(line))
            *len = ft_strlen(line);
        *index += 1; 
    }
}
int empty_line(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (!white_space(line[i]))
            return (0);
        i++;
    }
    return (1);
}


int is_not_map(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] == '1' || line[i] == '0' || is_direction(line[i]) || white_space(line[i]))
        {
            i++;
            continue;
        }
        else
            return (1);
    }
    return (0);
}
char *replace_spaces(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (white_space(line[i]) && line[i] != '\n')
            line[i] = '2';
        else if (line[i] == '\n')
            line[i] = '1';
        i++;
    }
    return (line);
}

char *get_full_len(char *line, int len)
{
    char *new_line;
    int i;

    i = 0;
    new_line = malloc(len + 1);
    while (line[i])
    {
        new_line[i] = line[i];
        i++;
    }
    while (i < len)
    {
        new_line[i] = '2';
        i++;
    }
    new_line[i] = '\0';
    return (new_line);
}
void fill_map(t_input *input, char *file, int len)
{
    int fd;
    char *line;
    int i;
    // int j;

    i = 0;
    // j = 0;
    fd = open(file, O_RDONLY);
    input->map = malloc(sizeof(char *) * input->height);
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        if (empty_line(line) || is_not_map(line))
            continue;
        if (i < input->height)
        {
            input->map[i] = get_full_len(line, len);
            input->map[i] = replace_spaces(input->map[i]);
            
            i++;
        }
        if (i == input->height)
        {
            input->map[i] = NULL;
            break;
        }
    }
    close(fd);
}
void get_player(t_input *input)
{
    int x = 0;
    int y = 0;
    int found = 0;
    while (y < input->height)
    {
        x = 0;
        while (x < input->width)
        {
            if (is_direction(input->map[y][x]))
            {
                if (input->map[y][x] == 'N')
                    input->direction = 270;
                else if (input->map[y][x] == 'S')
                    input->direction = 90;
                else if (input->map[y][x] == 'E')
                    input->direction = 0;
                else if (input->map[y][x] == 'W')
                    input->direction = 180;
                input->pos_x = x;
                input->pos_y = y;
                input->map[y][x] = '0';
                found = 1;
                break;
            }
            else
                x++;
        }
        if (found)
            break;
        y++;
    }

}

t_input parsing(char *file)
{
    t_input input;
    int fd;
    char *line;
    int i;
    // int j;
    size_t len;

    i = 0;
    // j = 0;
    len = 0;
    fd = open(file, O_RDONLY);
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        if (empty_line(line))
            continue;
        fill_desc_map(line, &input, &i,&len);
    }
    input.height = i;
    close(fd);
    fill_map(&input, file, len);
    input.width = len;
    get_player(&input);
    return (input);
}


