#include "minishell.h"

char	**list_to_2D(t_list *list)
{
	t_list	*iter;
	char	**str;
	int		i;

	i = 0;
	iter = list;
	str = malloc(sizeof(char **) * ft_lstsize(list) + 1);
	while (iter != NULL)
	{
		str[i] = ft_strdup(iter->content);
		i++;
		iter = iter->next;
	}
	str[i] = NULL;
	return(str);
}

void	exec(char *path, char **arg)
{
	if(execve(path, arg, shell->environ) == -1)
	{
		reset_stdout();
		printf("%s: command not found.\n", arg[0]);
		free(path);
		exit(127);
	}
}

void	other_cmnds(char **arg)
{
	char	**path;
	int	pid;
	int	i;
	int	fd;
	int	ret;

	i = 0;
	path = ft_split(ft_strdup(getenv("PATH")),':');
	while (path[i])
	{
		path[i] = ft_strjoin(path[i],"/");
		path[i] = ft_strjoin(path[i], arg[0]);
		if(access(path[i], F_OK) == 0)
			break;
		i++;
	}
	pid = fork();
	if (pid == 0)
		exec(path[i], arg);
	waitpid(pid, &ret, 0);
	shell->exit_status = ret % 255;
	wait(NULL);
	free(path);
	free(arg);
}
