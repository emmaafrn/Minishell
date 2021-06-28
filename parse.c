#include "minishell.h"

void	get_redirections_list(t_scanner *scanner, t_parse *parse)
{
	t_list	*new;

	while (scanner->words && (char)scanner->words->content.word != '|')
	{
		new = ft_lstnew(scanner->words->content.word, '0');
		ft_lstadd_back(&parse->redir, new);
		scanner->words = scanner->words->next; 
	}
}


void	get_exec_list(t_scanner *scanner, t_parse *parse)
{
	t_list	*new;

	while (scanner->words)
	{
		while (scanner->words && (char)scanner->words->content.word != '|')
		{
			if (scanner->words->flag == NONE || scanner->words->flag == DOLLAR)
			{
				new = ft_lstnew(scanner->words->content.word, '0');
				ft_lstadd_back(&parse->exec, new);
			}
			if (scanner->words->flag == SPECIAL)
			{
				if ((char)scanner->words->content.word == '>'
					|| (char)scanner->words->content.word == '<')
					get_redirections_list(scanner, parse);
			}
			if (scanner->words)
				scanner->words = scanner->words->next;
		}
		if (scanner->words)
			scanner->words = scanner->words->next;
	}
}
