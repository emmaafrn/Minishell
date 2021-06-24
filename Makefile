NAME	=	minishell

SRCS	=	get_next_line.c list.c minishell.c utils.c dollar.c tokenisation.c env_var_value.c

OBJ = ${SRCS:.c=.o}

CC  = gcc

RM  = rm -f

CFLAGS = -g -Wall -Wextra -Werror -g3 -fsanitize=address

all:		$(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) ${CFLAGS} $^ -o $(NAME)

$(OBJ) : minishell.h get_next_line.h

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:		fclean all