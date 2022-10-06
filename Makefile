NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror 
SRCS = srcs/*.c libft/*.c
LIBS = readline/lib
INCLUDES = readline/include

all: $(NAME)

$(NAME): $(SRCS)
	@$(CC) $(CFLAGS) $(SRCS) -lreadline -o $(NAME)

re: fclean all

fclean:
	rm -rf $(NAME)
