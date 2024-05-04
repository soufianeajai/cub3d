#include "cub3d.h"

void fill_desc_map(char *line, t_input *input, int *index)
{
    char *id;

    id = ft_substr(line, 0, 2);
    if (!ft_strcmp(id,"NO"))
    {
        input->no =ft_substr(line, 3, ft_strlen(line));
        printf("---------->%s\n", input->no);
    }
    else if (!ft_strcmp(id,"SO"))
    {
        input->so =ft_substr(line, 3, ft_strlen(line));
        printf("---------->%s\n", input->so);
    }
    else if (!ft_strcmp(id,"WE"))
    {
        input->we =ft_substr(line, 3, ft_strlen(line));
        printf("---------->%s\n", input->we);
    }
    else if (!ft_strcmp(id,"EA"))
    {
        input->ea =ft_substr(line, 3, ft_strlen(line));
        printf("---------->%s\n", input->ea);
    }
    else if (!ft_strcmp(id,"F "))
    {
        input->f_color = (int)(220 * pow(256, 2) + 100 * pow(256, 1) + 0 * pow(256, 0));
        printf("---------->%d\n", input->f_color);
    }
    else if (!ft_strcmp(id,"C "))
    {
        input->f_color = (int)(225 * pow(256, 2) + 30 * pow(256, 1) + 0 * pow(256, 0));
        printf("---------->%d\n", input->f_color);
    }
    else
        *index += 1;
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
void fill_map(t_input *input, char *file)
{
    int fd;
    char *line;
    int i;

    i = 0;
    fd = open(file, O_RDONLY);
    input->map = malloc(sizeof(char *) * input->nbr_lines);
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        if (empty_line(line) || is_not_map(line))
            continue;
        if (i < input->nbr_lines)
            input->map[i++] = ft_strdup(line);
        if (i == input->nbr_lines)
        {
            input->map[i] = NULL;
            break;
        }
    }
    close(fd);
}

t_input *parsing(char *file)
{
    t_input *input;
    int fd;
    char *line;
    int i;

    i = 0;
    input = malloc(sizeof(t_input));
    if (!input)
        return (NULL);
    fd = open(file, O_RDONLY);
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        if (empty_line(line))
            continue;
        fill_desc_map(line, input, &i);
       // printf("%s\n", line);
    }
    // we have nomber line for map :
    input->nbr_lines = i;
    close(fd);
    fill_map(input, file);
    return (input);
}