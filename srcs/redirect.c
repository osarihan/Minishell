/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarihan <osarihan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:55:42 by oozcan            #+#    #+#             */
/*   Updated: 2022/12/22 14:17:51 by osarihan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandler_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
		exit(0);
	}
}

int	redirect_check(void)
{
	t_list	*iter;

	int (i) = 0;
	if (g_shell->arg == NULL)
		return (0);
	iter = g_shell->arg;
	while (iter)
	{
		if (ft_strcmp(iter->content, "<") || ft_strcmp(iter->content, ">") \
			|| ft_strcmp(iter->content, ">>") || ft_strcmp(iter->content, "<<"))
		{
			if (ft_strcmp(iter->content, "<"))
				g_shell->l_red++;
			else if (ft_strcmp(iter->content, ">"))
				g_shell->r_red++;
			else if (ft_strcmp(iter->content, ">>"))
				g_shell->dr_red++;
			else if (ft_strcmp(iter->content, "<<"))
				g_shell->dl_red++;
			i++;
		}
		iter = iter->next;
	}
	return (i);
}

int	which_red(char *content)
{
	if (ft_strcmp(content, ">"))
		return (1);
	else if (ft_strcmp(content, ">>"))
		return (2);
	else if (ft_strcmp(content, "<"))
		return (3);
	else if (ft_strcmp(content, "<<"))
		return (4);
	return (0);
}

void	redirect_decider(int stat, int index, int r_c)
{
	if (stat == 1)
		right_redirect(index, r_c);
	else if (stat == 2)
		double_right_redirect(index, r_c);
	else if (stat == 3)
		left_redirect(index, r_c);
	else if (stat == 4)
		run_heredoc(index);
}

void	cut_redirect(int index)
{
	ft_dstry_node_for_red(g_shell->arg, index);
	ft_dstry_node_for_red(g_shell->arg, index);
}
