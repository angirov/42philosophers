NAME = philo

SRCS = 	main.c

OBJ = ${SRCS:.c=.o}

HEADERS = minishell.h

# ========== compilation ==========
CC = gcc
CFLAGS = -Wall -Wextra -Werror 

# ========== rules ==========
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)
# -fsanitize=address

%.o: %.c $(HEADERS) makelibs
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm $(OBJ)

fclean:
	rm $(OBJ) $(NAME)

re: fclean all

.PHONY: all clean fclean re makelibs re