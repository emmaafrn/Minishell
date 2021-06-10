#include "minishell.h"

void	init_states(t_state *state)
{
	state->reading_word = 1;
	state->d_quoted_word = 0;
	state->s_quoted_word = 0;
	state->escape_char = 0;
	state->dollar = 0;
	state->end_of_instruct = 0;
	state->end_of_line = 0;
}

int	s_quoted_word(char *line, t_list **lst, int i)
{
	t_list	*temp;
	t_list	*temp_new;

	while (line[i] != '\'')
	{
		temp_new->content->c = ft_lstnew(line[i], 0);
		ft_lstadd_back(&temp, temp_new);
		i++;
	}
	if (temp)
		*lst = temp;
	return (i);
}

int	d_quoted_word(char *line, t_scanner *scanner, int i)
{
	t_list	*temp;
	t_list	*temp_new;

	while (line[i] != '\"')
	{
		while (line[i] != '$' && line[i] != '\"')
		{
			temp_new->content->c = ft_lstnew(line[i], 0);
			ft_lstadd_back(&temp, temp_new);
			i++;
		}
		if (line[i] == '$')
		{
			
		}
		
	}
	scanner->temp = temp;
	return (i);
}

void	whats_the_state(char *line, t_scanner *scanner, int i)
{
	if (scanner->state.s_quoted_word)
		i = s_quoted_word(line, &scanner->temp, ++i);
	if (scanner->state.d_quoted_word)
		i = d_quoted_word(line, scanner, ++i);
	if (!scanner->state.reading_word)
	{
		if (scanner->temp)
		{
			wrd_lstadd_back(&scanner->words, scanner->temp);
			ft_lstclear(&scanner->temp);
		}
	}
}

void	ft_scan_line(char *line, t_scanner *scanner)
{
	int	i;

	i = 0;
	init_states(&scanner->state);
	while (!scanner->state.end_of_line)
	{
		while (!scanner->state.end_of_instruct)
		{
			while (scanner->state.reading_word)
			{
				if (line[i] == '\"')
					scanner->state.d_quoted_word = 1;
				else if (line[i] == '\'')
					scanner->state.s_quoted_word = 1;
				else if (line[i] == '\\')
					scanner->state.escape_char = 1;
				else if (line[i] == '$')
					scanner->state.dollar = 1;
				else if (line[i] == ' ')
					scanner->state.reading_word = 0;
				else if (line[i] == 0)
					scanner->state.end_of_line = 1;
				whats_the_state(line, scanner, i);
				i++;
			}
		}
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
		printf("[%s]\n", line);
	}
	if (result == -1)
		return (-1);
	return (0);
}