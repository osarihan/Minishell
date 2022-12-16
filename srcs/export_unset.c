/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozcan <oozcan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:34:53 by oozcan            #+#    #+#             */
/*   Updated: 2022/12/16 18:52:55 by oozcan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fill(void)
{
	int (i) = 0;
	g_shell->asd = NULL;
	while (g_shell->environ[i] != NULL)
	{
		ft_lstadd_back(&g_shell->asd, ft_lstnew(g_shell->environ[i]));
		i++;
	}
	ultimate_alpha_index_finder();
}

void	exporter(char *content, int i, t_list *list)
{
	while (content != NULL)
	{
		if (content == NULL)
			break ;
		if (lstcmp(content) && ft_strchr(content, '='))
			ft_lstadd_back(&g_shell->asd, ft_lstnew(ft_strdup(content)));
		else if (lstcmp(content) && !ft_strchr(content, '='))
			ft_lstadd_back(&g_shell->declare, ft_lstnew(ft_strdup(content)));
		else
		{
			ft_dstry_node(g_shell->cmmp);
			if (ft_strchr(content, '='))
				ft_lstadd_back(&g_shell->asd, ft_lstnew(ft_strdup(content)));
		}
		i++;
		content = list_data(list, i);
	}
}

void	ft_export(t_list *list)
{
	char	*content1;
	char	*content;

	int (i) = 1;
	content1 = list_data(list, i);
	if (content1 != NULL)
		content = content1;
	else
		content = NULL;
	if (!g_shell->ctrl++)
		ft_fill();
	if (content == NULL)
		printf_alph();
	exporter(content, i, list);
	ultimate_alpha_index_finder();
	g_shell->exit_status = 0;
	return ;
}

int	baby_index_finder(int i, t_list *arg_iter, char *str, char *str2)
{
	int (j) = 0;
	while (arg_iter != NULL)
	{
		if (i == 0)
			str2 = arg_iter->content;
		if (ft_strcmp(str, str2) == 1)
		{
			arg_iter = arg_iter->next;
			continue ;
		}
		if (str[i] > str2[i])
			j++;
		else if (str[i] == str2[i])
		{
			i++;
			continue ;
		}
		arg_iter = arg_iter->next;
		i = 0;
	}
	return (j);
}

void	ultimate_alpha_index_finder(void)
{
	t_list	*list_iter;
	t_list	*arg_iter;
	char	*str;
	char	*str2;

	int (i) = 0;
	int (j) = 0;
	arg_iter = g_shell->asd->next;
	list_iter = g_shell->asd;
	while (list_iter)
	{
		str = list_iter->content;
		j = baby_index_finder(i, arg_iter, str, str2);
		list_iter->index = j;
		list_iter = list_iter->next;
		arg_iter = g_shell->asd;
		i = 0;
		j = 0;
	}
}
