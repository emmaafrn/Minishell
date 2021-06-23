#include "minishell.h"

t_list	*remove_a_list_item(t_list **lst, t_list *item)
{
	t_list	*first;
	t_list	*removed;
	
	first = *lst;
	while (*lst && (*lst)->next != item)
		*lst = (*lst)->next;
	removed = item;
	(*lst)->next = (*lst)->next->next;
	free (removed);
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
