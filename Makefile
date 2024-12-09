NAME = libftprintf.a
LIB = libft.a

CC = cc
CFLAGS = -Wall -Wextra - Werror

SRC = 

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIB)
	ar rcs 

%.o: %.c
	$(CC) $(CFLAGS) $(LIB) -c $< -o $@

$(LIB): 
	make -C libft
	make bonus -C libft

clean:
	rm -f $(OBJ)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
