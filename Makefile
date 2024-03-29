NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = srcs/*.c libft/*.c
LIBS = readline/lib
INCLUDES = readline/include

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -fcommon -I /goinfre/homebrew/opt/readline/include -L /goinfre/homebrew/opt/readline/lib -lreadline -o $(NAME)

re: fclean all

fclean:
	rm -rf $(NAME)
