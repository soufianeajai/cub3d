#include "cub3d.h"

void fill_desc_map(char *line, t_input *input)
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
}

t_input *parsing(char *file)
{
    t_input *input;
    int fd;
    char *line;

    input = malloc(sizeof(t_input));
    if (!input)
        return (NULL);
    fd = open(file, O_RDONLY);
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        fill_desc_map(line, input);
       // printf("%s\n", line);
    }

    return (NULL);
}