#include "minishell.h"

void	wr_close_pipe(int **fd)
{
	int	j;

	j = 0;
	while (j < shell->pipe)
	{
		close(fd[j][1]);
		close(fd[j][0]);
		j++;
	}
}

void	check_cmnd2(int **fd, int i)
{
	int	stat;
	int	index;

	index = 0;
	stat = 0;
	while (!ft_strcmp(shell->arg->content, "|") && shell->arg != NULL)
	{
		ft_lstadd_back(&shell->pipe_arg, ft_lstnew(shell->arg->content));
		shell->arg = shell->arg->next;
		if (shell->arg == NULL)
			break;
		if (ft_strcmp(shell->arg->content, ">"))
		{
			stat = 1;
			break;
		}
		index++;
	}
	if (stat)
		right_redirect(index - 1);
	else if (i == 0)
		dup2(fd[0][1], 1);
	else if (i != shell->pipe)
		dup2(fd[i][1], STDOUT_FILENO);
	wr_close_pipe(fd);
	run_cmd(shell->pipe_arg);
}

void	create_pipe(int **fd)
{
	int	i;

	i = 0;
	while (i <= shell->pipe)
	{
		if (pipe(fd[i]) == -1)
		{
			perror("");
			return;
		}
		i++;
	}
}

void	pipe_f()
{
	int	len;
	int	i = 0;
	int	**fd;
	int	status;

	fd = malloc(sizeof(int *) * shell->pipe + 1);
	while (i <= shell->pipe)
		fd[i++] = malloc(sizeof(int) * 2);
	create_pipe(fd);
	i = 0;
	if (!fork())//child
	{
		// dup2(fd[0][1], 1);
		// wr_close_pipe(fd);
		check_cmnd2(fd, i);
		exit(0);
	}
	else
	{
		wait(NULL);
		i++;
		while (i < shell->pipe + 1)
		{
			while (!ft_strcmp(shell->arg->content, "|") && shell->arg != NULL)
				shell->arg = shell->arg->next;
			if (ft_strcmp(shell->arg->content, "|"))
				shell->arg = shell->arg->next;
			if (!fork())
			{
				dup2(fd[i - 1][0], STDIN_FILENO);
				// if (i != shell->pipe)
				// 	dup2(fd[i][1], STDOUT_FILENO);
				// wr_close_pipe(fd);
				check_cmnd2(fd, i);
				exit(0);
			}
			i++;
		}
		///parent
		usleep(5500);
		wr_close_pipe(fd);
		wait(NULL);
	}
}
