
NAME	= cub3d
CFLAGS	= -Wall -Wextra -Werror #-fsanitize=address
SRS		= main.c raycasting/events_hooks.c raycasting/connect_check_set.c \
		raycasting/utils.c gnl/get_next_line.c gnl/get_next_line_utils.c parsing.c util_parsing.c 

FRAM	= -lmlx -framework OpenGL -framework AppKit 

OBJ	= $(SRS:.c=.o)

all: $(NAME)

.c.o:
	cc $(CFLAGS) -c $< -o $@
	
$(NAME): $(OBJ)
	cc $(OBJ) $(FRAM)  -o $(NAME)

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(OBJ)

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: $(OBJ)
