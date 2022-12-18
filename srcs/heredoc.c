/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozcan <oozcan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:47:18 by oozcan            #+#    #+#             */
/*   Updated: 2022/12/18 15:43:01 by oozcan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_prompt(int index)
{
	char	*to_write;
	char	*tmp;
	char	*eof;
	char	*path;
	int		fd;

	eof = list_data(g_shell->arg, index + 1);
	fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	while (true && fd)
	{
		to_write = readline(">");
		if (ft_strcmp(to_write, eof))
		{
			close(fd);
			return ;
		}
		else
		{
			ft_putstr_fd(to_write, fd);
			ft_putstr_fd("\n", fd);
		}
		free(to_write);
	}
	close(fd);
}

void	run_heredoc(int i)
{
	int		fd;
	int		pid;
	char	*temp;
	char	*path;

	pid = fork();
	if (pid == 0)
	{
		fd = open(".heredoc", O_RDWR, 0777);
		if (fd < 0)
			return ;
		dup2(fd, 0);
		close(fd);
		run_cmd(g_shell->arg);
		exit(0);
	}
	wait(NULL);
	waitpid(pid, NULL, -1);
}
//NU3NLL9F

void	cut_heredoc(int index)
{
	ft_dstry_node2(g_shell->arg, index);
	ft_dstry_node2(g_shell->arg, index);
}

void	heredoc(void)
{
	t_list	*iter;
	int		index;

	int (i) = 0;
	index = heredoc_finder();
	iter = g_shell->arg;
	heredoc_prompt(index);
	cut_heredoc(index);
	if (g_shell->heredoc_cnt == 1)
	{
		run_heredoc(index);
		g_shell->heredoc_cnt--;
	}
	else
		g_shell->heredoc_cnt--;
	if (g_shell->heredoc_cnt == 0)
		return ;
	if (!lstcmp2(iter, "<<"))
		heredoc();
}

int	heredoc_check(void)
{
	int (i) = 0;
	while (g_shell->arg)
	{
		if (!lstcmp2(g_shell->arg, "<<"))
		{
			printf ("heredoca gitt\n");
			g_shell->heredoc_cnt = heredoc_cnt();
			heredoc();
			return (1);
		}
		else
			return (0);
	}
	return (0);
}
