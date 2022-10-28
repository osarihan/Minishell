#include "minishell.h"

int	job(char **arg, int i)
{
	arg[i] = to_lower(arg[i]);
	if (ft_strcmp(arg[i], "cd"))
		ft_cd(arg, i);
	else if (ft_strcmp(arg[i], "echo"))
		ft_echo(arg, i);
	else if (ft_strcmp(arg[i], "pwd") || \
					ft_strcmp(arg[i], "PWD"))
		ft_pwd();
	// else if (ft_strcmp(arg[i], "env"))
	// 	ft_env();
	else if (ft_strcmp(arg[i], "exit"))
		exit(0);
	else if (other_cmnds(arg))
		return (1);
	else
	{
		i++;
		return (0);
	}
	return (1);
}

void	check_cmnd2(char *arg, int i)
{
	char **str;

	i = 0;
	str = ft_split(arg, ' ');
	job(str, i);
	i++;
}

void	create_pipe(t_shell *shell, int **fd)
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

void	wr_close_pipe(t_shell *shell, int **fd)
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

void	shell_pipe_dup2(t_shell *shell)
{
	int	len;
	int	i = 0;
	int	**fd;
	int	status;

	fd = malloc(sizeof(int *) * shell->pipe + 1);
	while (i <= shell->pipe)
	{
		fd[i] = malloc(sizeof(int) * 2);
		i++;
	}
	create_pipe(shell, fd);
	i = 0;
	if (!fork())//child
	{
		dup2(fd[0][1], 1);
		wr_close_pipe(shell, fd);
		check_cmnd2(shell->str_pipe[0], 0);
		exit(0);
	}
	else
	{
		i++;
		while (i < shell->pipe + 1)
		{
			if (!fork())
			{
				dup2(fd[i - 1][0], STDIN_FILENO);
				if (i != shell->pipe)
					dup2(fd[i][1], STDOUT_FILENO);
				wr_close_pipe(shell, fd);
				check_cmnd2(shell->str_pipe[i], i);
				exit(0);
			}
			i++;
		}
		///parent
		wr_close_pipe(shell, fd);
		wait(NULL);
	}
}
