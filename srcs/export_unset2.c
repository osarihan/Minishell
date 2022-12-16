/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozcan <oozcan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:12:05 by oozcan            #+#    #+#             */
/*   Updated: 2022/12/16 18:54:02 by oozcan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_list *list)
{
	if (!g_shell->ctrl++)
		ft_fill();
	ft_lstremover(list);
	g_shell->exit_status = 0;
}

int	baby_index_finder_declared(int i, t_list *arg_iter, char *str, char *str2)
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

void	ultimate_alpha_index_finder_declared(void)
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
		j = baby_index_finder_declared(i, arg_iter, str, str2);
		list_iter->index = j;
		list_iter = list_iter->next;
		arg_iter = g_shell->asd;
		i = 0;
		j = 0;
	}
}

void	printf_alph_declared(void)
{
	t_list	*list_iter;

	int (i) = 0;
	list_iter = g_shell->declare;
	while (list_iter != NULL)
	{
		while (list_iter && list_iter->index != i)
			list_iter = list_iter->next;
		if (list_iter == NULL)
			return ;
		if ((char *)list_iter->content)
			printf("declare -x %s\n", list_iter->content);
		i++;
		list_iter = g_shell->declare;
		continue ;
	}
}

void	printf_alph(void)
{
	t_list	*list_iter;

	int (i) = 0;
	list_iter = g_shell->asd;
	while (list_iter != NULL)
	{
		while (list_iter && list_iter->index != i)
			list_iter = list_iter->next;
		if (list_iter == NULL)
			break ;
		if ((char *)list_iter->content)
			printf("declare -x %s\n", list_iter->content);
		i++;
		list_iter = g_shell->asd;
		continue ;
	}
	ultimate_alpha_index_finder_declared();
	printf_alph_declared();
}
