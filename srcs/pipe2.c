/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozcan <oozcan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:51:41 by oozcan            #+#    #+#             */
/*   Updated: 2022/12/16 19:53:01 by oozcan           ###   ########.fr       */
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
	usleep(5500);
	wr_close_pipe(fd);
	wait(NULL);
}

void    check_cmnd2(int **fd, int i)
{
	int stat;
	int index;
	index = 0;
	stat = 0;
	while (!ft_strcmp(g_shell->arg->content, "|") && g_shell->arg != NULL)
	{
		ft_lstadd_back(&g_shell->pipe_arg, ft_lstnew(g_shell->arg->content));
		g_shell->arg = g_shell->arg->next;
		if (g_shell->arg == NULL)
			break;
		if (ft_strcmp(g_shell->arg->content, ">") || ft_strcmp(g_shell->arg->content, ">>") || ft_strcmp(g_shell->arg->content, "<") || ft_strcmp(g_shell->arg->content, "<<"))
		{
			stat = which_red(g_shell->arg->content);
			break;
		}
		index++;
	}
	if (stat > 0)
	{
		if (ft_strcmp(list_data(g_shell->arg, index), ">") || ft_strcmp(list_data(g_shell->arg, index), ">>") || ft_strcmp(list_data(g_shell->arg, index), "<") || ft_strcmp(list_data(g_shell->arg, index), "<<"))
			redirect_decider(stat, index);
		else
			redirect_decider(stat, index - 1);
	}
	else if (i == 0)
		dup2(fd[0][1], 1);
	else if (i != g_shell->pipe)
		dup2(fd[i][1], STDOUT_FILENO);
	wr_close_pipe(fd);
	run_cmd(g_shell->pipe_arg);
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
	// else
	// {
	// 	wait(NULL);
	// 	i++;
	// 	while (i < g_shell->pipe + 1)
	// 	{
	// 		while (!ft_strcmp(g_shell->arg->content, "|") && g_shell->arg != NULL)
	// 			g_shell->arg = g_shell->arg->next;
	// 		if (ft_strcmp(g_shell->arg->content, "|"))
	// 			g_shell->arg = g_shell->arg->next;
	// 		if (!fork())
	// 		{
	// 			dup2(fd[i - 1][0], STDIN_FILENO);
	// 			// if (i != shell->pipe)
	// 			// 	dup2(fd[i][1], STDOUT_FILENO);
	// 			// wr_close_pipe(fd);
	// 			check_cmnd2(fd, i);
	// 			exit(0);
	// 		}
	// 		i++;
	// 	}
	// 	///parent
	// 	usleep(5500);
	// 	wr_close_pipe(fd);
	// 	wait(NULL);
	// }
}
