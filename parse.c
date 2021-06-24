#include "minishell.h"

t_list	*remove_a_list_item(t_list **lst, t_list *item)
{
	t_list	*first;
	t_list	*removed;
	
	first = *lst;
	if (*lst == item)
	{
		first = (*lst)->next;
		free(*lst);
		*lst = NULL;
		*lst = first;
		return (*lst);
	}
	while ((*lst)->next && (*lst)->next != item)
		*lst = (*lst)->next;
	removed = (*lst)->next;
	(*lst)->next = removed->next;
	free(removed);
	removed = NULL;
	*lst = first;
	return (*lst);
}

int	whats_the_list(t_list *words_lst)
{
	t_list	*start;
	char	*env_var;

	start = words_lst;
	while (words_lst)
	{
		if (words_lst->flag == DOLLAR)
		{
			env_var = getenv(words_lst->content.word);
			if (env_var == NULL)
			{
				words_lst = remove_a_list_item(&start, words_lst);
				printf("-----parse----\n");
				if (words_lst)
					print_lst(words_lst);
				else
					return (-1);
				return (0);
			}
			words_lst->content.word = env_var;
		}
		words_lst = words_lst->next;
	}
	words_lst = start;
	printf("-----parse----\n");
	print_lst(words_lst);
	return (1);
}
