#include "minishell.h"

void	there_is_env_var(char *line, int i, t_scanner *scanner)
{
	t_list	*new;
	int		start;

	start = i;
	while (line[i] && ((line[i] >= 97 && line[i] >= 122) || (line[i] >= 65
		&& line[i] <= 90) || (line[i] >= 48 && line[i] <= 57) || line[i] == '_')
				&& line[i] != ' ')
	{
		new = ft_lstnew(NULL, line[i]);
		new->flag = DOLLAR;
		ft_lstadd_back(&scanner->temp, new);
		i++;
	}
	if (i == start)
	{
		new = ft_lstnew(NULL, line[i]);
		new->flag = NONE;
		ft_lstadd_back(&scanner->temp, new);
		i++;
	}
}
