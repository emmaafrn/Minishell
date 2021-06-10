#include "minishell.h"

t_list	*ft_lstnew(t_lst_content *content, int a)
{
	t_list	*liste;

	liste = malloc(sizeof(t_list));
	if (!(liste))
		return (NULL);
	if (a == 0)
	{
		liste->content->c = content->c;
		liste->content->word = NULL;
	}
	else if (a == 1)
	{
		liste->content->c = '0';
		liste->content->word = content->word;
	}
	liste->next = NULL;
	return (liste);
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
