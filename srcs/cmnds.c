/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmnds.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozcan <oozcan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:17:35 by osarihan          #+#    #+#             */
/*   Updated: 2022/10/23 16:55:16 by oozcan           ###   ########.fr       */
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

void	ft_cd(t_shell *shell, int i)
{
	char *str = NULL;

	if (shell->str[i + 1] != NULL)
	{
		str = ft_strjoin(getcwd(str, sizeof(str)), "/");
		i++;
		if (!shell->str[i])
			return ;
		str = ft_strjoin(str, shell->str[i]);
		chdir(str);
	}
	else
	{
		str = ft_strjoin(getenv("HOME"), "/");
		chdir(str);
	}
}

int	 ft_echo(t_shell *shell, int i)
{
	if (ft_strcmp(shell->str[i], "-n"))
	{
		i++;
		while (shell->str[i])
		{
			printf("%s", shell->str[i]);
			if (shell->str[i + 1] != NULL)
				printf(" ");
			i++;
		}
	}
	else
	{
		//while (shell->str[i] != '\0' && ft_strcmp(shell->str[i], shell->op[0]) == 0)
		while (shell->str[i] != NULL)
		{
			printf("%s", shell->str[i]);
			if (shell->str[i + 1] != NULL)
				printf(" ");
			i++;
		}
		printf("\n");
	}
	return (1);
}


int ft_env(void)
{
	int i;
	extern char **environ;

	i = 0;
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
	return (1);
}
