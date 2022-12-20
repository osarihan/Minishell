/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmnd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozcan <oozcan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 19:00:22 by oozcan            #+#    #+#             */
/*   Updated: 2022/12/19 17:49:14 by oozcan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arg_check(void)
{
	int	stat;

	stat = 0;
	if (g_shell->arg == NULL)
		return (0);
	if (ft_strcmp(g_shell->arg->content, ">") || \
			ft_strcmp(g_shell->arg->content, ">>") || \
				ft_strcmp(g_shell->arg->content, "<") || \
					ft_strcmp(g_shell->arg->content, "<<"))
	{
		stat = which_red(g_shell->arg->content);
		return (stat);
	}
	return (0);
}

void	stat_decider(int stat, int index)
{
	int (redc) = 0;
	int (f_index) = index;
	t_list *(iter) = g_shell->arg;
	if (ft_strcmp(list_data(g_shell->arg, index), ">") || \
		ft_strcmp(list_data(g_shell->arg, index), ">>") || \
			ft_strcmp(list_data(g_shell->arg, index), "<") || \
				ft_strcmp(list_data(g_shell->arg, index), "<<"))
	{
		while (!ft_strcmp(list_data(iter, index), "|"))
		{
			if (ft_strcmp(list_data(iter, index), ">") || \
				ft_strcmp(list_data(iter, index), ">>") || \
					ft_strcmp(list_data(iter, index), "<") || \
						ft_strcmp(list_data(iter, index), "<<"))
			{
				redc++;
				index++;
			}
			else
				index++;
		}
		redirect_decider(stat, f_index, redc - 1);
	}
	else
		redirect_decider(stat, f_index - 1, redc - 1);
}

void	check_cmnd2(int **fd, int i)
{
	int	stat;
	int	index;

	index = 0;
	stat = 0;
	while (!ft_strcmp(g_shell->arg->content, "|") && g_shell->arg != NULL)
	{
		ft_lstadd_back(&g_shell->pipe_arg, ft_lstnew(g_shell->arg->content));
		g_shell->arg = g_shell->arg->next;
		if (g_shell->arg == NULL)
			break ;
		stat = arg_check();
		if (stat)
			break ;
		index++;
	}
	g_shell->iter = g_shell->pipe_arg;
	if (stat > 0)
		stat_decider(stat, index);
	else if (i == 0)
		dup2(fd[0][1], 1);
	else if (i != g_shell->pipe)
		dup2(fd[i][1], STDOUT_FILENO);
	wr_close_pipe(fd);
	run_cmd(g_shell->pipe_arg);
}
