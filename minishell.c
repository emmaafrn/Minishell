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

int	whats_the_state(char *line, t_scanner *scanner, int i)
{
	t_list	*new;

	if (scanner->state.s_quoted_word)
		i = s_quoted_word(line, &scanner->temp, ++i);
	else if (scanner->state.d_quoted_word)
		i = d_quoted_word(line, &scanner->temp, &scanner->words, ++i);
	else if (scanner->state.reading_word == 0)
	{
		if (scanner->temp)
			from_lst_a_to_lst_b(&scanner->temp, &scanner->words);
		init_states(&scanner->state);
	}
	else if (scanner->state.reading_word)
	{
		if (line[i] == '$')
			i = there_is_env_var(line, ++i, &scanner->temp, &scanner->words);
		else
		{
			new = ft_lstnew(NULL, line[i]);
			new->flag = NONE;
			ft_lstadd_back(&scanner->temp, new);
		}
	}
	return (i);
}

void	ft_scan_line(char *line, t_scanner *scanner)
{
	int		i;
	t_list	*new;

	i = 0;
	while (line[i])
	{
		init_states(&scanner->state);
		if (line[i] == '\"')
			scanner->state.d_quoted_word = 1;
		else if (line[i] == '\'')
			scanner->state.s_quoted_word = 1;
		else if (line[i] == '$')
			scanner->state.dollar = 1;
		if (line[i] == ' ')
		{
			if (scanner->temp)
				from_lst_a_to_lst_b(&scanner->temp, &scanner->words);
			new = ft_lstnew(NULL, line[i]);
			new->flag = SPACE;
			ft_lstadd_back(&scanner->temp, new);
			while (line[i] && line[i] == ' ' && line[i + 1] == ' ')
				i++;
			if (scanner->temp)
				from_lst_a_to_lst_b(&scanner->temp, &scanner->words);
		}
		else
			i = whats_the_state(line, scanner, i);
		if (line[i])
			i++;
	}
	if (scanner->temp)
		from_lst_a_to_lst_b(&scanner->temp, &scanner->words);
	if (scanner->words)
	{
		printf("-----------------\n");
		print_lst(scanner->words);
	}
}

int	main(void)
{
	char		*line;
	int			result;
	t_scanner	scanner;

	result = 1;
	while (result == 1)
	{
		result = get_next_line(0, &line);
		ft_scan_line(line, &scanner);
		ft_lstclear(&scanner.words);
		printf("[%s]\n", line);
	}
	if (result == -1)
		return (-1);
	return (0);
}
