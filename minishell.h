#ifndef MINISHELL_H
# define MINISHELL_H

# include "get_next_line.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <stdio.h>
# include <sys/types.h>

#define NONE 0
#define SPACE 1
#define DOLLAR 2

typedef struct	s_lst_content
{
	char	c;
	char	*word;
}				t_lst_content;


typedef struct s_list
{
	t_lst_content	*content;
	struct s_list	*next;
	int				flag;
}				t_list;

typedef struct s_state
{
	int	reading_word;
	int	s_quoted_word;
	int	d_quoted_word;
	int	escape_char;
	int	dollar;
	int	end_of_line;
}				t_state;

typedef struct s_scanner
{
	const char	*cursor;
	t_state		state;
	t_list		*temp;
	t_list		*words;
}				t_scanner;

t_list			*ft_lstnew(char *str, char c);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstclear(t_list **lst);
int				ft_lstsize(t_list *lst);

char			*from_lst_to_str(t_list *a);
void			from_lst_a_to_lst_b(t_list **a, t_list **b);

void			there_is_env_var(char *line, int i, t_scanner *scanner);

void			print_lst(t_list *lst);



#endif