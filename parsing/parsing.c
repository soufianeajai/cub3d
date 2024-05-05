#include "parsing.h"
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

char *fill_elements(char *line, int i)
{
    char *str;
    if (empty_line(line))
        return (NULL);
    while (white_space(line[i]))
        i++;
    str = ft_substr(line, i, ft_strlen(line) - i);
    return (str);
}
int fill_rgb(char *line, int i)
{
    long r;
    long g;
    long b;
    char **tab;
    int j;

    j = 0;
    tab = ft_split(line + i, ',');
    if (tab[0] && tab[1] && tab[2])
    {
        r = ft_atoi(tab[0]);
        printf("\n\n=> %s\n\n", tab[0]);
        g = ft_atoi(tab[1]);
        printf("\n\n=> %s\n\n", tab[1]);
        b = ft_atoi(tab[2]);
        printf("\n\n=> %s\n\n", tab[2]);
        if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255)
        {
            printf("\n0000000000 -> %d\n\n", (int)((r << 16) | (g << 8) | b));
            ft_free(tab);
            return ((int)((r << 16) | (g << 8) | b));
        }
    }
    ft_free(tab);
    return (-1);
}

int is_texture(char *line, t_input *input)
{
    int i;

    i = 0;
    while (white_space(line[i]))
        i++;
    if (line[i] && line[i + 1])
    {
        if (line[i] == 'N' && line[i + 1] == 'O' && !input->no)
            input->no = fill_elements(line, i + 2);
        else if (line[i] == 'S' && line[i + 1] == 'O' && !input->so)
            input->so = fill_elements(line, i + 2);
        else if (line[i] == 'W' && line[i + 1] == 'E' && !input->we)
            input->we = fill_elements(line, i + 2);
        else if (line[i] == 'E' && line[i + 1] == 'A' && !input->ea)
            input->ea = fill_elements(line, i + 2);
        else if (line[i] == 'F' && line[i + 1] == ' ' && input->f_color == -1)
        {
            input->f_color = fill_rgb(line, i + 1);
            printf("\n\n=----> %s   -   %d\n\n", line + i + 1, input->f_color);
        }
        else if (line[i] == 'C' && input->c_color == -1)
        {
            input->c_color = fill_rgb(line, i + 1);
            printf("\n\n=----> %s   -   %d\n\n", line + i + 1, input->f_color);
        }else
            return (0);
        return (1);
    }
    return (0);
}


int all_elements_set(t_input *input)
{
    if (input->no && input->so && input->we && input->ea && input->f_color != -1 && input->c_color != -1)
        return (1);
    return (0);
}

void fill_desc_map(char *line, t_input *input, int *index)
{
    if(is_texture(line, input))
        return;
    else
    {
        // also add if all other elements are set (not NULL)
        if (all_elements_set(input)) // last element set is map !!
            *index += 1;
    } 
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
void init_Data(t_input *input)
{
    input->no = NULL;
    input->so = NULL;
    input->we = NULL;
    input->ea = NULL;
    input->f_color = -1;
    input->c_color = -1;
    input->map = NULL;
}

void fill_map(t_input *input, char *file)
{
    int fd;
    char *line;
    int i;

    i = 0;
    fd = open(file, O_RDONLY);
    input->map = malloc(sizeof(char *) * input->nbr_lines);
    if (!input->map)
        return;
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        if (empty_line(line) || is_not_map(line))
            continue;
        if (i < input->nbr_lines)
            input->map[i++] = ft_substr(line, 0, ft_strlen(line) - 1);
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
    init_Data(input);
    fd = open(file, O_RDONLY);
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        if (empty_line(line))
            continue;
        fill_desc_map(line, input, &i);
    }
    // we have nomber line for map :
    input->nbr_lines = i;
    close(fd);
    fill_map(input, file);
    return (input);
}