#include "minishell.h"

// void	multi_close(int **fd, int len)
// {
// 	int i = 0;
// 	while (i < len)
// 	{
// 		close(fd[i][0]);
// 		close(fd[i][1]);
// 	}
// }
void    multiple_close(int **fd, int len)
{
    int i;
    int j;
    i = 0;
    j = 0;
    while (i < len)
    {
        if (j == 2)
        {
            j = 0;
            i++;
            if (i == len)
                break ;
        }
        if (close(fd[i][j]) < 0)
            perror("close ");
        j++;
    }
}

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
	else if (ft_strcmp(arg[i], "env"))
		ft_env();
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

void	multiple_pid(int *pid, int len)
{
	int	status;
	int	i = 0;
	while (i < len)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
}

void	shell_pipe_dup2(t_shell *shell)
{
	int	len;
	int	i = 0;
	int	*pid;
	int	**fd;
	int	status;

	pid = malloc(sizeof(int) * shell->pipe + 1);
	if (shell->pipe <= 0)
		return ;
	fd = malloc(sizeof(int *) * shell->pipe + 1);
	while (i <= shell->pipe)
	{
		fd[i] = malloc(sizeof(int) * 2);
		printf("I %d\n", i);
		i++;
	}
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
	i = 0;
	while (i < shell->pipe + 1)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			printf("Burdasin --> %d\n", __LINE__);
			if (i == 0)
			{
				dup2(fd[i][1] , STDOUT_FILENO);
			}
			//if (i != shell->pipe)
			if (i > 0)
			{
				dup2(fd[i - 1][0], STDIN_FILENO);
			}
			if (i != shell->pipe)
				dup2(fd[i][1] , STDOUT_FILENO);
			multiple_close(fd, shell->pipe + 1);
			check_cmnd2(shell->str_pipe[i], i);
			exit(0);
		}
		//multiple_close(fd, shell->pipe + 1);
		//wait(NULL);
		printf("123\n");
		multiple_pid(pid, shell->pipe + 1);
		//waitpid(pid, &status, 0);
		//multi_close(fd, shell->pipe);
		i++;
	}
}
