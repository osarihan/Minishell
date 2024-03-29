/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarihan <osarihan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:51:41 by oozcan            #+#    #+#             */
/*   Updated: 2022/12/22 15:53:27 by osarihan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wr_close_pipe(int **fd)
{
	int	j;

	j = 0;
	while (j < g_shell->pipe)
	{
		close(fd[j][1]);
		close(fd[j][0]);
		j++;
	}
}

void	create_pipe(int **fd)
{
	int	i;

	i = 0;
	while (i <= g_shell->pipe)
	{
		if (pipe(fd[i]) == -1)
		{
			perror("");
			return ;
		}
		i++;
	}
}

void	go_pipe(void)
{
	t_list	*iter;

	while (!ft_strcmp(g_shell->arg->content, "|") \
		&& g_shell->arg != NULL)
	{
		iter = g_shell->arg;
		free(g_shell->arg->content);
		g_shell->arg = g_shell->arg->next;
		free(iter);
	}
}

void	other_pipe_child(int i, int **fd)
{
	t_list	*iter;
	int		pid;

	while (++i < g_shell->pipe + 1)
	{
		go_pipe();
		if (ft_strcmp(g_shell->arg->content, "|"))
		{
			iter = g_shell->arg;
			free(g_shell->arg->content);
			g_shell->arg = g_shell->arg->next;
			free(iter);
		}
		pid = fork();
		if (pid == 0)
		{
			dup2(fd[i - 1][0], STDIN_FILENO);
			check_cmnd2(fd, i);
			exit(0);
		}
	}
	wr_close_pipe(fd);
	waitpid(pid, NULL, 0);
	wait(NULL);
}

void	pipe_f(void)
{
	int	pid;
	int	**fd;

	int (i) = 0;
	fd = malloc(sizeof(int *) * g_shell->pipe + 1);
	while (i <= g_shell->pipe)
		fd[i++] = malloc(sizeof(int) * 2);
	create_pipe(fd);
	i = 0;
	pid = fork();
	if (pid == 0)
	{
		check_cmnd2(fd, i);
		exit(0);
	}
	else
	{
		wait(NULL);
		waitpid(pid, NULL, 0);
		other_pipe_child(i, fd);
	}
	ft_free_fd(fd);
}
