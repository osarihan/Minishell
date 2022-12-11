#include "minishell.h"

int heredoc_cnt()
{
	int i;
	t_list *iter;
	iter = shell->arg;
	i = 0;
	while (iter)
	{
		if (ft_strcmp(iter->content, "<<"))
			i++;
		iter = iter->next;
	}
	return (i);
}
int heredoc_finder()
{
	int i;
	t_list *iter;
	i = 0;
	iter = shell->arg;
	while (iter)
	{
		if (ft_strcmp(iter->content, "<<"))
			return (i);
		i++;
		iter = iter->next;
	}
	return (0);
}
