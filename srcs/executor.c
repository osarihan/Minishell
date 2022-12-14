/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozcan <oozcan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 13:48:30 by oozcan            #+#    #+#             */
/*   Updated: 2022/12/14 15:05:31 by oozcan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_status(void)
{
	t_list	*iter;

	iter = shell->arg;
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
	shell->l_red = 0;
	shell->r_red = 0;
	shell->dr_red = 0;
	shell->dl_red = 0;
}

void	executor(void)
{
	int	status;

	if (shell->arg == NULL)
		return ;
	redirect_check();
	heredoc_check();
	status = pipe_status();
	if (status)
		run_cmd_with_pipe();
	if (!status)
	{
		if (shell->dl_red || shell->r_red || shell->l_red || shell->dr_red)
		{
			if (!fork())
			{
				if (shell->dl_red)
				{
					if (ft_strcmp(shell->arg->next->content, "<<"))
						run_heredoc(1);
					else
						run_heredoc(2); // SAYDIR
				}
				else if (shell->r_red)
				{
					if (ft_strcmp(shell->arg->next->content, ">"))
						right_redirect(1);
					else
						right_redirect(2);
				}
				else if (shell->l_red)
				{
					if (ft_strcmp(shell->arg->next->content, "<"))
						left_redirect(1);
					else
						left_redirect(2);
				}
				else if (shell->dr_red)
				{
					if (ft_strcmp(shell->arg->next->content, ">>"))
						double_right_redirect(1);
					else
						double_right_redirect(2);
				}
				run_cmd(shell->arg);
				exit(0);
			}
			wait(NULL);
		}
		else if (!status && !(shell->dl_red || shell->r_red \
				|| shell->l_red || shell->dr_red))
			run_cmd(shell->arg);
		reset_stdout();
		reset_stdin();
		reset_shellint();
	}
	else
		return ;
}
