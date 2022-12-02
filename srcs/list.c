#include "minishell.h"

int	lstcmp(char *str)
{
	t_list *temp;
	t_list	*temp2;

	shell->cmmp = 1;
	temp = shell->asd;
	temp = temp->next;
	while (temp != NULL)
	{
		if (ft_strcmp3(temp->content, str))
			return (0);
		temp = temp->next;
		shell->cmmp++;
	}
	return(1);
}

void ft_dstry_node(int c)
{
	t_list *tmp;
	t_list *tmp2;

	tmp = shell->asd;
	tmp2 = shell->asd;
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

void	ft_lstremover(void)
{
	int i = 1;
	char *tmp;
	char *tmp2;
	char	*content;
	t_list *tmplst;

	int c = 0;
	c += 1;
	content = list_data(shell->arg, 1);
	while (content)
	{
		content = list_data(shell->arg, i);
		tmplst = shell->asd->next;
		while(tmplst)
		{
			tmp = (char *)tmplst->content;
			if (ft_strcmp2(tmp, content))
			{
				ft_dstry_node(c);
				return;
			}
			tmplst = tmplst->next;
			c++;
		}
		i++;
		c = 1;
	}
}

char	*list_data(t_list *root, int index)
{
	t_list	*iter;
	int	i;

	iter = root;
	i = 0;
	while (i++ != index)
		iter = iter->next;
	if (iter == NULL)
		return (NULL);
	return (iter->content);
}

// char	*list_data(t_list **list, int index)
// {
// 	int	i;

// 	i = 0;
// 	while (i++ != index)
// 		(*list) = (*list)->next;
// 	return ((*list)->content);
// }

t_list	*list_f_data(t_list *root, int index)
{
	t_list *list;
	int	i;

	list = root;
	i = 0;
	while (i++ != index)
		list = list->next;
	return (list);
}