
NAME	= cub3d
CFLAGS	= -Wall -Wextra -Werror 
SRS		= main.c raycasting/events_hooks.c raycasting/connect_check_set.c raycasting/cast_rays.c raycasting/minimap.c \
		  raycasting/minimap_utils.c raycasting/utils.c raycasting/handle_images.c \
		  parsing/util2_parsing.c parsing/util1_parsing.c parsing/util3_parsing.c parsing/util4_parsing.c parsing/parsing.c \
		  parsing/util_parsing.c parsing/util5_parsing.c parsing/gnl/get_next_line.c parsing/gnl/get_next_line_utils.c

FRAM	= libmlx.a -framework OpenGL -framework AppKit 

OBJ	= $(SRS:.c=.o)

all: $(NAME)

.c.o:
	cc $(CFLAGS) -c $< -o $@
	
$(NAME): $(OBJ)
	cc $(OBJ)  $(FRAM) -ggdb3 -fsanitize=address  -o $(NAME)

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(OBJ)

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: $(OBJ)
