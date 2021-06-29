#include "minishell.h"

void	get_redirections_list(t_tokens *tokens, t_list *parse)
{
	t_list	*new;

	while (tokens->words && (char)tokens->words->content.word != '|')
	{
		new = ft_lstnew(tokens->words->content.word, '0');
		ft_lstadd_back(&parse->lst_struct->redir, new);
		tokens->words = tokens->words->next; 
	}
}

void	get_exec_list(t_tokens *tokens, t_list *parse)
{
	t_list	*new;

	while (tokens->words)
	{
		new = ft_lst_struct_new();
		ft_lstadd_back(&parse, new);
		parse->lst_struct = malloc(sizeof(t_parse));
		parse->lst_struct->exec = NULL;
		parse->lst_struct->redir = NULL;
		if (!parse->lst_struct)
			return ;
		while (tokens->words && (char)tokens->words->content.word != '|')
		{
			if (tokens->words->flag == NONE || tokens->words->flag == DOLLAR)
			{
				new = ft_lstnew(tokens->words->content.word, '0');
				ft_lstadd_back(&parse->lst_struct->exec, new);
			}
			if (tokens->words->flag == SPECIAL)
			{
				if ((char)tokens->words->content.word == '>'
					|| (char)tokens->words->content.word == '<')
					get_redirections_list(tokens, parse);
			}
			if (tokens->words)
				tokens->words = tokens->words->next;
		}
		if (tokens->words)
			tokens->words = tokens->words->next;
	}
	printf("-----exec-----\n");
	print_lst_after_parse(parse->lst_struct->exec);
	printf("-----redir-----\n");
	print_lst_after_parse(parse->lst_struct->redir);
}
