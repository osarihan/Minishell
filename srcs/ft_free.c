/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozcan <oozcan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:12:47 by oozcan            #+#    #+#             */
/*   Updated: 2022/12/18 17:56:31 by oozcan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_free(void)
{
	t_list	*iter;

	while (g_shell->arg != NULL)
	{
		iter = g_shell->arg;
		free(g_shell->arg->content);
		g_shell->arg = g_shell->arg->next;
		free(iter);
	}
}

void	lst_free2(t_list *list)
{
	t_shell	*iter;

	printf("geldim\n");
	while (list != NULL)
	{
		printf("listcon:%s\n", list->content);
		iter = list;
		free(list->content);
		list = list->next;
		free(iter);
	}
}
