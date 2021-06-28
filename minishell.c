#include "minishell.h"

void	init_states(t_state *state)
{
	state->reading_word = 1;
	state->d_quoted_word = 0;
	state->s_quoted_word = 0;
	state->dollar = 0;
}

int	s_quoted_word(char *line, t_list **lst, int i)
{
	t_list	*new;

	while (line[i] && line[i] != '\'')
	{
		new = ft_lstnew(NULL, line[i]);
		new->flag = NONE;
		ft_lstadd_back(lst, new);
		i++;
	}
	return (i++);
}

int	d_quoted_word(char *line, t_list **lst, t_list **wrds_lst, int i)
{
	t_list	*new;

	while (line[i] && line[i] != '\"')
	{
		while (line[i] && line[i] != '$' && line[i] != '\"')
		{
			new = ft_lstnew(NULL, line[i]);
			new->flag = NONE;
			ft_lstadd_back(lst, new);
			i++;
		}
		if (line[i] == '$')
		{
			if (*lst)
				from_lst_a_to_lst_b(lst, wrds_lst);
			i++;
			i = there_is_env_var(line, i, lst, wrds_lst);
		}
	}
	return (i++);
}

int	main(void)
{
	char		*line;
	int			result;
	t_scanner	scanner;
	// t_parse		parse;

	result = 1;
	while (result == 1)
	{
		result = get_next_line(0, &line);
		ft_scan_line(line, &scanner);
		if (scanner.words)
			ft_lstclear(&scanner.words);
		if (scanner.words)
			print_lst(scanner.words);
		printf("line = [%s]\n", line);
	}
	if (result == -1)
		return (-1);
	return (0);
}
