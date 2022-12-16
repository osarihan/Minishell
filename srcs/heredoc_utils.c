/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozcan <oozcan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:44:53 by oozcan            #+#    #+#             */
/*   Updated: 2022/12/16 17:45:14 by oozcan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_cnt(void)
{
	int		i;
	t_list	*iter;

	iter = g_shell->arg;
	i = 0;
	while (iter)
	{
		if (ft_strcmp(iter->content, "<<"))
			i++;
		iter = iter->next;
	}
	return (i);
}

int	heredoc_finder(void)
{
	int		i;
	t_list	*iter;

	i = 0;
	iter = g_shell->arg;
	while (iter)
	{
		if (ft_strcmp(iter->content, "<<"))
			return (i);
		i++;
		iter = iter->next;
	}
	return (0);
}
