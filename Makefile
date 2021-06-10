NAME	=	minishell

SRCS	=	get_next_line.c list.c minishell.c

OBJ = ${SRCS:.c=.o}

CC  = gcc

RM  = rm -f

CFLAGS = -Wall -Wextra -Werror

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