#include "minishell.h"

t_list	*ft_lstnew(char *str, char c)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!(list))
		return (NULL);
	if (str == NULL)
	{
		printf("c = %c\n", c);
		list->content->c = c;
		list->content->word = "NULL";
	}
	else
	{
		list->content->c = '0';
		list->content->word = str;
	}
	list->next = NULL;
	return (list);
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*ok;

	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	ok = *alst;
	while (ok->next != NULL)
		ok = ok->next;
	ok->next = new;
}

void	ft_lstclear(t_list **lst)
{
	t_list	*next;
	t_list	*tmp;

	next = *lst;
	while (next != NULL)
	{
		tmp = next;
		next = next->next;
		free(tmp);
	}
	(*lst) = NULL;
}

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
