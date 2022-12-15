	#include "minishell.h"

void	ft_unset(t_list *list)
{
	if (!shell->ctrl++)
		ft_fill();
	ft_lstremover(list);
	shell->exit_status = 0;
}

void	ft_fill()
{
	int i = 0;

	shell->asd = NULL;
	while (shell->environ[i] != NULL)
	{
		ft_lstadd_back(&shell->asd, ft_lstnew(shell->environ[i]));
		i++;
	}
	ultimate_alpha_index_finder();
}

void	ft_export(t_list *list)
{
	int i = 1;
	char	*content1;
	char 	*content;
	content1 = list_data(list, i);
	if (content1 != NULL)
		content = content1;
	else
		content = NULL;
	if (!shell->ctrl++)
		ft_fill();
	if (content == NULL)
		printf_alph();
	while (content != NULL)
	{
		if (content == NULL)
			break;
		if (lstcmp(content) && ft_strchr(content, '='))//var mi yok mu yoksa girer
			ft_lstadd_back(&shell->asd, ft_lstnew(ft_strdup(content)));
		else if (lstcmp(content) && !ft_strchr(content, '='))
			ft_lstadd_back(&shell->declare, ft_lstnew(ft_strdup(content)));
		else
		{
			printf("ccontent::%s\n", list->content);
					t_list *iter;
			iter = shell->arg;
			while (iter != NULL)
			{
				printf("argsLAST:::::%s\n", iter->content);
				iter = iter->next;
			}
			ft_dstry_node(shell->cmmp);
			if (ft_strchr(content, '='))
				ft_lstadd_back(&shell->asd, ft_lstnew(ft_strdup(content)));
		}
		i++;
		content = list_data(list, i);
	}
	ultimate_alpha_index_finder();
	shell->exit_status = 0;
	return;
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
void	ultimate_alpha_index_finder_declared(void) //listeyi siralar
{
	t_list *list_iter;
	t_list *arg_iter;
	char *str;
	char *str2;
	int i = 0;
	int j = 0;

	if (shell->declare == NULL)
		return;
	arg_iter = shell->declare->next;
	list_iter = shell->declare;
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
		arg_iter = shell->declare;
		i = 0;
		j = 0;
	}
}
void	printf_alph_declared(void) //sirali baski
{
	t_list *list_iter;
	int i;
	i = 0;
	list_iter = shell->declare;
	while (list_iter != NULL)
	{
		while (list_iter && list_iter->index != i)
			list_iter = list_iter->next;
		if (list_iter == NULL)
			return;
		if ((char *)list_iter->content)
			printf("declare -x %s\n", list_iter->content);
		i++;
		list_iter = shell->declare;
		continue;
	}
}
void	printf_alph(void) //sirali baski
{
	t_list *list_iter;
	int i;
	i = 0;
	list_iter = shell->asd;
	while (list_iter != NULL)
	{
		while (list_iter && list_iter->index != i)
			list_iter = list_iter->next;
		if (list_iter == NULL)
			break;
		if ((char *)list_iter->content)
			printf("declare -x %s\n", list_iter->content);
		i++;
		list_iter = shell->asd;
		continue;
	}
	ultimate_alpha_index_finder_declared();
	printf_alph_declared();
}
