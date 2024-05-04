
#include "cub3d.h"

typedef struct s_input t_input;
char	*ft_substr(char *s, unsigned int start, size_t len);
int	ft_strcmp(const char *s1, const char *s2);
int white_space(char c);
int is_direction(char c);
t_input *parsing(char *file);