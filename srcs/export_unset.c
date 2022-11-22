#include "minishell.h"

void	ft_unset(void)
{
	ft_lstremover();
}

void	ft_lstremover(void)
{
	int i = 1;
	char *tmp;
	char *tmp2;
	t_list *tmplst;

	int c = 0;
	c += 1;
	while (shell->str[i])
	{
		tmp2 = shell->str[i];
		tmplst = shell->asd;
		tmplst = tmplst->next;
		while(tmplst)
		{
			tmp = (char *)tmplst->content;
			if (ft_strcmp2(tmp, tmp2))
			{
				ft_dstry_node(c);
			}
			tmplst = tmplst->next;
			c++;
		}
		i++;
		c = 1;
	}
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

void	ft_export(void)
{
	int	i = 1;
	if (!shell->ctrl++)
		ft_fill();
	if (shell->str[i] == NULL)
	{
		if (!shell->ctrl++)
			ft_fill();
		printf_alph();
	}
	while (shell->str[i])
	{
		if (lstcmp(shell->str[i]) && ft_strchr(shell->str[i], '='))//var mi yok mu yoksa girer
			ft_lstadd_back(&shell->asd, ft_lstnew(shell->str[i++]));
		else
		{
			ft_dstry_node(shell->cmmp);
			if (ft_strchr(shell->str[i], '='))
				ft_lstadd_back(&shell->asd, ft_lstnew(shell->str[i]));
			i++;
		}
		ultimate_alpha_index_finder();
	}
	return;
}

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

void	ft_fill(void)
{
	int i = 0;
	t_list *dsa;

	shell->asd = malloc(sizeof(t_list));
	shell->asd = NULL;
	while (shell->environ[i] != NULL)
	{
		ft_lstadd_back(&shell->asd, ft_lstnew(shell->environ[i]));
		i++;
	}
	ultimate_alpha_index_finder();
}

void	ultimate_alpha_index_finder(void) //listeyi siralar
{
	t_list *list_iter;
	t_list *arg_iter;
	char *str;
	char *str2;
	int i = 0;
	int j = 0;

	arg_iter = shell->asd->next;
	list_iter = shell->asd;
	while (list_iter)
	{
		str = list_iter->content;
		while (arg_iter != NULL)
		{
			if (i == 0)
				str2 = arg_iter->content;
			if (ft_strcmp(str, str2) == 1)
			{
				arg_iter = arg_iter->next;
				continue;
			}
			if (str[i] > str2[i])
				j++;
			else if (str[i] == str2[i])
			{
				i++;
				continue;
			}
			arg_iter = arg_iter->next;
			i = 0;
		}
		list_iter->index = j;
		list_iter = list_iter->next;
		arg_iter = shell->asd;
		i = 0;
		j = 0;
	}
}

void    printf_alph(void) //sirali baski
{
	t_list *list_iter;
	int i;
	i = 0;
	list_iter = shell->asd;
	while (list_iter->next != NULL)
	{
		while (list_iter && list_iter->index != i)
			list_iter = list_iter->next;
		if (list_iter == NULL)
			return;
		if ((char *)list_iter->content)
			printf("declare -x %ss\n", list_iter->content);
		i++;
		list_iter = shell->asd;
		continue;
	}
}
