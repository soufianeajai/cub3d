
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
  int   nbr_lines;
}  t_input;

char	*ft_substr(char *s, unsigned int start, size_t len);
int	ft_strcmp(const char *s1, const char *s2);
int white_space(char c);
int is_direction(char c);
t_input *parsing(char *file);