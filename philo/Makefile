NAME = philo

SRCS =	main.c \
		utils.c \
		init.c \
		init2.c \
		time.c \
		philo.c \
		print.c \
		mutex.c

OBJ = ${SRCS:.c=.o}

HEADERS = minishell.h

# ========== compilation ==========
CC = gcc
CFLAGS = -pthread -Wall -Wextra -Werror -Wno-unused-variable

# ========== rules ==========
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) -g -fsanitize=thread
# -fsanitize=address

%.o: %.c $(HEADERS) makelibs
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm $(OBJ)

fclean:
	rm $(OBJ) $(NAME)

re: fclean all

.PHONY: all clean fclean re makelibs re