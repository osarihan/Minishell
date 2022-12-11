#include "minishell.h"

int lstcmp2(t_list *iter, char *str)
{
	t_list *temp;
	t_list  *temp2;
	temp = iter;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->content, str))
			return (0);
		temp = temp->next;
	}
	return(1);
}
void ft_dstry_node2(t_list *iter, int c)
{
	t_list *tmp;
	t_list *tmp2;
	tmp = iter;
	tmp2 = iter;
	if (c == 0)
		iter = NULL;
	while (c > 1 && tmp != NULL)
	{
		if (tmp->next != NULL)
			tmp = tmp->next;
		c--;
	}
	if (tmp->next->next != NULL)
		tmp2 = tmp->next->next;
	else
		tmp2 = NULL;
	if (tmp2 != NULL)
		tmp->next = tmp2;
	else
		tmp->next = NULL;
}
