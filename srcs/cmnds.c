/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmnds.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozcan <oozcan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:17:35 by osarihan          #+#    #+#             */
/*   Updated: 2022/11/01 13:56:03 by oozcan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	other_cmnds(char **arg)
{
	extern char **environ;
	char	**path;
	int	pid;
	int	i;

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
			exit(0);
		}
	}
	wait(NULL);
	return (1);
}

void	ft_pwd(void)
{
	char	cwd[256];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("");
}

void	ft_cd(char **arg, int i)
{
	char str[256];
	char *str2 = NULL;

	if (arg[i + 1] != NULL)
	{
		str2 = ft_strjoin(getcwd(str, sizeof(str)), "/");
		i++;
		if (!arg[i])
			return ;
		str2 = ft_strjoin(str2, arg[i]);
		chdir(str2);
	}
	else
	{
		str2 = ft_strjoin(getenv("HOME"), "/");
		chdir(str2);
	}
}

void	 ft_echo(char **str, int i)
{
	if (str[i + 1] == NULL)
		printf("\n");
	else
	{
		i++;
		while (str[i])
		{
			if (ft_strcmp(str[i], "-n") && str[i + 1] == NULL && i == 1)
				return ;
			if (ft_strcmp(str[i], "-n") && str[i + 1] != NULL)
				printf("%s", str[i + 1]);
			else if (str[i + 1] == NULL)
				printf("%s\n", str[i]);
			else
				printf("%s ", str[i]);
			i++;
		}
	}
}


int ft_env(void)
{
	t_list *tmp;

	if (!shell->ctrl)
	{
		printf("ft_fill\n");
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
