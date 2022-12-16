/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozcan <oozcan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 13:48:30 by oozcan            #+#    #+#             */
/*   Updated: 2022/12/16 18:04:16 by oozcan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_status(void)
{
	t_list	*iter;

	iter = g_shell->arg;
	while (iter != NULL)
	{
		if (ft_strcmp(iter->content, "|"))
		{
			if (iter->next == NULL)
			{
				ft_putstr_fd("Error: A few arguments after pipe\n", 2);
				return (-1);
			}
			return (1);
		}
		iter = iter->next;
	}
	return (0);
}

static void	reset_shellint(void)
{
	g_shell->l_red = 0;
	g_shell->r_red = 0;
	g_shell->dr_red = 0;
	g_shell->dl_red = 0;
}

void	executor(void)
{
	int	status;

	if (g_shell->arg == NULL)
		return ;
	redirect_check();
	heredoc_check();
	status = pipe_status();
	if (status)
		run_cmd_with_pipe();
	if (!status)
	{
		if (g_shell->dl_red || g_shell->r_red \
			|| g_shell->l_red || g_shell->dr_red)
		{
			if (!fork())
			{
				if (g_shell->dl_red)
				{
					if (ft_strcmp(g_shell->arg->next->content, "<<"))
						run_heredoc(1);
					else
						run_heredoc(2); // SAYDIR
				}
				else if (g_shell->r_red)
				{
					if (ft_strcmp(g_shell->arg->next->content, ">"))
						right_redirect(1);
					else
						right_redirect(2);
				}
				else if (g_shell->l_red)
				{
					if (ft_strcmp(g_shell->arg->next->content, "<"))
						left_redirect(1);
					else
						left_redirect(2);
				}
				else if (g_shell->dr_red)
				{
					if (ft_strcmp(g_shell->arg->next->content, ">>"))
						double_right_redirect(1);
					else
						double_right_redirect(2);
				}
				run_cmd(g_shell->arg);
				exit(0);
			}
			wait(NULL);
		}
		else if (!status && !(g_shell->dl_red || g_shell->r_red \
				|| g_shell->l_red || g_shell->dr_red))
			run_cmd(g_shell->arg);
		reset_stdout();
		reset_stdin();
		reset_shellint();
	}
	else
		return ;
}
