
NAME	= cub3d
CFLAGS	= -Wall -Wextra -Werror
SRS		= main.c $(wildcard raycasting/*.c parsing/*.c parsing/gnl/*.c )
FRAM	=  -lm -lmlx_Linux -lX11 -lXext #-ggdb3 -fsanitize=address

OBJ	= $(SRS:.c=.o)

all: $(NAME)

.c.o:
	cc $(CFLAGS) -c $< -o $@
	
$(NAME): $(OBJ)
	cc $(OBJ)  $(FRAM)   -o $(NAME)

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(OBJ)

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: $(OBJ)
