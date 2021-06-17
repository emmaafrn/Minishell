#include "minishell.h"

int	there_is_env_var(char *line, int i, t_list **lst, t_list **wrds_lst)
{
	t_list	*new;
	int		start;

	start = i;
	while (line[i] && ((line[i] >= 97 && line[i] >= 122) || (line[i] >= 65
		&& line[i] <= 90) || (line[i] >= 48 && line[i] <= 57) || line[i] == '_')
				&& line[i] != ' ' && line[i] != '\'' && line[i] != '\"')
	{
		new = ft_lstnew(NULL, line[i]);
		new->flag = DOLLAR;
		ft_lstadd_back(lst, new);
		i++;
	}
	if (i == start)
	{
		new = ft_lstnew(NULL, line[i]);
		new->flag = NONE;
		ft_lstadd_back(lst, new);
		i++;
	}
	from_lst_a_to_lst_b(lst, wrds_lst);
	return (i);
}
