/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 17:44:47 by afanidi           #+#    #+#             */
/*   Updated: 2024/06/02 17:44:48 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "gnl/get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# define NBR_DOORS 50

typedef struct s_point
{
	float	x;
	float	y;
}			t_point;

typedef struct s_input
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		c_color;
	int		f_color;
	double	direction;
	char	**map;
	int		pos_x;
	int		pos_y;
	int		door_x;
	int		door_y;
	t_point	door[NBR_DOORS];
	int		nb_doors;
	int		h;
	int		w;
}			t_input;

t_input		init_data(void);
void		free_all_elements(t_input *input);
void		read_matrix(t_input input);
void		get_doors(t_input *input);
void		mise_a_jour_map(t_input *input);
int			get_position_door(t_input input, int *x, int *y, char **map);
void		flood_fill(t_input input, int x, int y, char **map);
void		fill_desc_map(char *line, t_input *input, int *index_start_map,
				int *error);
int			is_texture(char *line, t_input *input);
int			check_espace(t_input *input, int i, int j, char c);
int			is_not_map(char *line);
int			all_elements_set(t_input *input, int flag);
int			empty_line(char *line);
char		*fill_elements(char *line, int i);
int			check_digits(char **str);
int			fill_rgb(char *line, int i);
int			is_wall(char c);
char		*ft_substr(char *s, int start, size_t len);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			white_space(char c);
int			ft_isdigit(int c);
void		*ft_memcpy(void *dst, const void *src, size_t n);
int			is_direction(char c);
long		ft_atoi(const char *p);
void		ft_free(char **tab);
void		free_tab_len(char **tab, int len);
char		**ft_split(char const *s, char c, int *nbr_lines);
int			parsing(char *file, t_input *input);
char		*get_full_len(char *line, t_input *input, int *position);
char		*replace_spaces(char *line);
int			get_position_door(t_input input, int *x, int *y, char **map);
int			is_valid_door(t_input input, int i, int j);
void		get_doors(t_input *input);
char		*replace_spaces(char *line);
void		free_tab_len(char **tab, int len);
int			is_wall(char c);
void		*ft_memcpy(void *dst, const void *src, size_t n);
int			is_texture(char *line, t_input *input);
int			white_space(char c);
int			get_position_door(t_input input, int *x, int *y, char **map);
char		**fill_map(t_input *input, char *file, int index_start_map,
				char *line);
int			parsing_map(char **map, t_input *input);
char		**avance_line(int index_start_map, char *file, int *fd, int len);
int			check_error_espace(char **map, int i, t_input *input);
int			error_first_last_element(char **map, t_input *input, int i);
#endif
