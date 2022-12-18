/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozcan <oozcan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:51:41 by oozcan            #+#    #+#             */
/*   Updated: 2022/12/18 17:17:46 by oozcan           ###   ########.fr       */
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

void	other_pipe_child(int i, int **fd)
{
	i++;
	while (i < g_shell->pipe + 1)
	{
		while (!ft_strcmp(g_shell->arg->content, "|") \
			&& g_shell->arg != NULL)
			g_shell->arg = g_shell->arg->next;
		if (ft_strcmp(g_shell->arg->content, "|"))
			g_shell->arg = g_shell->arg->next;
		if (!fork())
		{
			dup2(fd[i - 1][0], STDIN_FILENO);
			check_cmnd2(fd, i);
			exit(0);
		}
		i++;
	}
	usleep(5500);//
	wr_close_pipe(fd);
	wait(NULL);
}

void	pipe_f(void)
{
	int	len;
	int	**fd;
	int	status;

	int (i) = 0;
	fd = malloc(sizeof(int *) * g_shell->pipe + 1);
	while (i <= g_shell->pipe)
		fd[i++] = malloc(sizeof(int) * 2);
	create_pipe(fd);
	i = 0;
	if (!fork())
	{
		check_cmnd2(fd, i);
		exit(0);
	}
	else
	{
		wait(NULL);
		other_pipe_child(i, fd);
	}
}
