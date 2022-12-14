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
	t_list *cleaner;

	tmp = shell->asd;
	tmp2 = shell->asd;
	while (c > 1 && tmp != NULL)
	{
		if (tmp->next != NULL)
			tmp = tmp->next;
		c--;
	}

	cleaner = tmp->next;
	free(cleaner->content);
	free(cleaner);
	if (tmp->next->next != NULL)
		tmp2 = tmp->next->next;
	else
		tmp2 = NULL;
	if (tmp2 != NULL)
		tmp->next = tmp2;
	else
		tmp->next = NULL;
}

void	ft_lstremover(t_list *list)
{
	int i = 1;
	char *tmp;
	char *tmp2;
	char	*content;
	t_list *tmplst;

	int c;

	c = 1;
	content = list_data(list, 1);
	while (content)
	{
		content = list_data(list, i);
		tmplst = shell->asd->next;
		while(tmplst)
		{
			tmp = (char *)tmplst->content;
			if (tmplst == NULL || content == NULL)
				break;
			if (ft_strcmp2(tmp, content))
			{
				ft_dstry_node(c);
				break;
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
