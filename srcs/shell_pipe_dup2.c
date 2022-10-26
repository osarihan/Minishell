#include "minishell.h"

void	multi_close(int **fd)
{
	int i = -1;
	while (fd[++i])
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
}

void	shell_pipe_dup2(t_shell *shell)
{
	int	i = 1;
	int	id;
	int	fd[shell->pipe][2];
	//int	**fd;
//
	//fd = malloc(sizeof(int **) * shell->pipe);
	//id = 0;
	//while (id < shell->pipe)
	//{
	//	printf("%d\n", id);
	//	fd[id] = (int *)malloc(sizeof(int *));
	//	id++;
	//}
	if (shell->pipe <= 0)
		return ;
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
		id = fork();
		if (id == 0)
		{
			if (i != shell->pipe)
				dup2(fd[i][1], STDOUT_FILENO);
			if (i != 0)
				dup2(fd[i][0], STDIN_FILENO);
			multi_close(fd);
		}
		wait(NULL);
		printf("abc\n");
		//multi_close(fd);
		i++;
	}
}
