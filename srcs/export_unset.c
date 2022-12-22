/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarihan <osarihan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:34:53 by oozcan            #+#    #+#             */
/*   Updated: 2022/12/22 12:33:53 by osarihan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dstry_node31(int c)
{
	t_list	*cleaner;

	t_list *(tmp) = g_shell->asd;
	t_list *(tmp2) = g_shell->asd;
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
			ft_dstry_node31(g_shell->cmmp);
			if (ft_strchr(content, '='))
				ft_lstadd_back(&g_shell->asd, ft_lstnew(ft_strdup(content)));
		}
		i++;
		content = list_data(list, i);
	}
	free(content);
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
