/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozcan <oozcan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:47:18 by oozcan            #+#    #+#             */
/*   Updated: 2022/12/21 16:12:01 by oozcan           ###   ########.fr       */
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

	fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	signal(SIGINT, sighandler_heredoc);
	while (true && fd)
	{
		eof = ft_strdup(list_data(g_shell->arg, index + 1));
		to_write = readline(">");
		if (ft_strcmp(to_write, eof))
			heredoc_exit(fd, eof, to_write);
		else
		{
			ft_putstr_fd(to_write, fd);
			ft_putstr_fd("\n", fd);
		}
		if (g_shell->heredoc_quit == 1)
			heredoc_exit(fd, eof, to_write);
		free(eof);
		free(to_write);
	}
}

void	run_heredoc(int i)
{
	int		fd;
	int		pid;
	char	*temp;
	char	*path;

	fd = open(".heredoc", O_RDWR, 0777);
	if (fd < 0)
		return ;
	dup2(fd, 0);
	close(fd);
	cut_heredoc(i);
	run_cmd(g_shell->arg);
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
	int		pid;

	int (i) = 0;
	index = heredoc_finder();
	iter = g_shell->arg;
	pid = fork();
	if (pid == 0)
		heredoc_prompt(index);
	wait(NULL);
}

int	heredoc_check(void)
{
	int (i) = 0;
	while (g_shell->arg)
	{
		if (!lstcmp2(g_shell->arg, "<<"))
		{
			g_shell->heredoc_cnt = heredoc_cnt();
			heredoc();
			return (1);
		}
		else
			return (0);
	}
	return (0);
}
