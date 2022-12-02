#include "minishell.h"

int ft_env(void)
{
	t_list *tmp;

	if (!shell->ctrl)
	{
		ft_fill();
		shell->ctrl++;
	}
	tmp = shell->asd;
	tmp = tmp->next;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
	return (1);
}

void	ft_pwd(void)
{
	t_list *l_tmp;
	char	*tmp;
	char	*tmp2;
	int i = 0;
	int	j = 0;

	if (!shell->asd)
		ft_fill();
	l_tmp = shell->asd;
	tmp2 = malloc(ft_strlen("PWD") + 1);
	while (l_tmp != NULL)
	{
		tmp = l_tmp->content;
		while (tmp[i] != '=' && i < 3)
		{
			tmp2[i] = tmp[i];
			i++;
		}
		tmp2[i] = '\0';
		if (ft_strcmp(tmp2, "PWD"))
		{
			printf("%s\n", &tmp[++i]);
			free(tmp2);
			return ;
		}
		l_tmp = l_tmp->next;
		i = 0;
	}
}

void	 ft_echo()
{
	char	*content;
	int	i;

	i = 1;
	content = list_data(shell->arg, 0);
	if (list_data(shell->arg, i) == NULL)
		printf("\n");
	else
	{
		content = list_data(shell->arg, i);
		while (content != NULL)
		{
			if (ft_strcmp(content, "-n") && list_data(shell->arg, i + 1) == NULL && i == 1)
				return ;
			if (ft_strcmp(content, "-n") && list_data(shell->arg, i + 1) != NULL)
			{
				printf("%s", list_data(shell->arg, i + 1));
				i++;
			}
			else if (list_data(shell->arg, i + 1) == NULL)
				printf("%s\n", content);
			else
				printf("%s ", content);
			i++;
			content = list_data(shell->arg, i);
		}
	}
}

char	**list_to_2D()
{
	t_list	*iter;
	char	**str;
	int		i;

	i = 0;
	iter = shell->arg;
	while (iter != NULL)
	{
		str[i] = malloc(ft_strlen(iter->content) + 1);
		str[i] = iter->content;
		i++;
		iter = iter->next;
	}
	return(str);
}

int	other_cmnds(char **arg)
{
	extern char **environ;
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
	{
		if(execve(path[i], arg, environ) == -1)
		{
			printf("%s: command not found.\n", arg[0]);
			free(path);
			exit(1);
		}
	}
	waitpid(pid, &ret, 0);
	shell->exit_status = ret % 255;
	wait(NULL);
	return (1);
}
