#include "minishell.h"

int	reading_word_state(char *line, int i, t_scanner *scanner, t_list *new)
{
	char	last;

	last = 0;
	if (line[i] == '$')
		i = there_is_env_var(line, ++i, &scanner->temp, &scanner->words);
	else
	{
		new = ft_lstnew(NULL, line[i]);
		if (line[i] == '|' || line[i] == '<' || line[i] == '>')
		{
			if (scanner->temp)
				from_lst_a_to_lst_b(&scanner->temp, &scanner->words);
			new->flag = SPECIAL;
		}
		else
		{
			if (scanner->temp)
				last = ft_lstlast(scanner->temp)->content.c;
			if (last == '|' || last == '<' || last == '>')
				from_lst_a_to_lst_b(&scanner->temp, &scanner->words);
			new->flag = NONE;
		}
		ft_lstadd_back(&scanner->temp, new);
	}
	return (i);
}

int	whats_the_state(char *line, t_scanner *scanner, int i)
{
	t_list	*new;

	new = NULL;
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
		i = reading_word_state(line, i, scanner, new);
	return (i);
}

int	there_is_space(char *line, int i, t_scanner *scanner)
{
	t_list	*new;

	printf("line[%d] = %c\n", i, line[i]);
	if (scanner->temp)
		from_lst_a_to_lst_b(&scanner->temp, &scanner->words);
	new = ft_lstnew(NULL, line[i]);
	new->flag = SPACE;
	ft_lstadd_back(&scanner->temp, new);
	while (line[i] && line[i] == ' ' && line[i + 1] == ' ')
		i++;
	if (scanner->temp)
		from_lst_a_to_lst_b(&scanner->temp, &scanner->words);
	return (i);
}

void	ft_scan_line(char *line, t_scanner *scanner)
{
	int	i;

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
			i = there_is_space(line, i, scanner);
		else
			i = whats_the_state(line, scanner, i);
		if (line[i] && !(scanner->words && !scanner->temp
				&& ft_lstlast(scanner->words)->flag == DOLLAR))
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
