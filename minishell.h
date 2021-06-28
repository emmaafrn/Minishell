#ifndef MINISHELL_H
# define MINISHELL_H

# include "get_next_line.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <stdio.h>
# include <sys/types.h>

# define NONE 0
# define SPACE 1
# define DOLLAR 2
# define SPECIAL 3

typedef struct	s_lst_content
{
	char	c;
	char	*word;
}				t_lst_content;

struct s_parse;

typedef struct s_list
{
	t_lst_content	content;
	struct s_list	*next;
	struct s_parse	*lst_struct;
	int				flag;
}				t_list;

typedef struct s_parse
{
	t_list		*exec;
	t_list		*redir;
}				t_parse;


typedef struct s_state
{
	int		reading_word;
	int		s_quoted_word;
	int		d_quoted_word;
	int		dollar;
	int		pipe;
	char	redir;
}				t_state;

typedef struct s_tokens
{
	t_state		state;
	t_list		*temp;
	t_list		*words;
}				t_tokens;

t_list			*ft_lstnew(char *str, char c);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstclear(t_list **lst);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lst_struct_new(void);

char			*from_lst_to_str(t_list *a);
void			from_lst_a_to_lst_b(t_list **a, t_list **b);
void			print_lst(t_list *lst);

void			init_states(t_state *state);
int				s_quoted_word(char *line, t_list **lst, int i);
int				d_quoted_word(char *line, t_list **lst, t_list **wrds_lst, int i);
void			ft_scan_line(char *line, t_tokens *tokens);
int				whats_the_state(char *line, t_tokens *tokens, int i);
int				there_is_env_var(char *line, int i, t_list **lst, t_list **wrds_lst);
int				get_env_var_value(t_list *item, t_list *start);

void			get_redirections_list(t_tokens *tokens, t_list *parse);
void			get_exec_list(t_tokens *tokens, t_list *parse);


#endif