# include<stdio.h>
# include<unistd.h>
# include <fcntl.h>
# include <stdlib.h>
#include "gnl/get_next_line.h"

typedef struct s_input {
  char  *no;
  char  *so;
  char  *we;
  char  *ea;
  int    c_color;
  int    f_color;
  double  direction;
  char  **map;
  int    pos_x;
  int    pos_y;
  int   H;
  int   W;
}  t_input;


int init_Data(t_input *input, char *file);
void free_all_elements(t_input *input);

int is_wall(char c);
char	*ft_substr(char *s,  int start, size_t len);
int	ft_strcmp(const char *s1, const char *s2);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int white_space(char c);
int	ft_isdigit(int c);
int is_direction(char c);
long	ft_atoi(const char *p);
void ft_free(char **tab);
void free_tab_len(char **tab, int len);
char	**ft_split(char const *s, char c, int *nbr_lines);
int parsing(char *file, t_input *input);
char *get_full_len(char *line, t_input *input, int *position);
char *replace_spaces(char *line);