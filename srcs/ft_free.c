/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozcan <oozcan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:12:47 by oozcan            #+#    #+#             */
/*   Updated: 2022/12/19 18:08:37 by oozcan           ###   ########.fr       */
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

void	ft_free_fd(int **fd)
{
	int	i;

	i = 0;
	while (i <= g_shell->pipe)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}
