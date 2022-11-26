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

void	pwd_change(void)
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
			printf("%s\n", &tmp[i]);
			free(tmp2);
			return ;
		}
		l_tmp = l_tmp->next;
		i = 0;
	}
}

void	ft_pwd(void)
{
	pwd_change();
}

void	ft_cd(char **arg, int i)
{
	char str[256];
	char *str2 = NULL;
	char *str3;
	char *str4;
	printf("arg:%s\n", arg[i]);
	if (arg[i + 1] != NULL)
	{
		shell->temp = ft_strdup("PWD");
		str4 = ft_strjoin("OLDPWD=", check_env());
		str2 = ft_strjoin(getcwd(str, sizeof(str)), "/");
		i++;
		if (!arg[i])
			return ;
		str2 = ft_strjoin(str2, arg[i]);
		chdir(str2);
		getcwd(str, sizeof(str));
		str3 = ft_strjoin("PWD=", str);
		shell->str[i] = str3;
		ft_export();
		shell->str[i + 1] = str4;
		shell->str[i + 2] = NULL;
		ft_export();
	}
	else
	{
		shell->temp = ft_strdup("PWD");
		str4 = ft_strjoin("OLDPWD=", check_env());
		shell->str[i + 1] = str4;
		shell->str[i + 2] = NULL;
		ft_export();
		str2 = ft_strjoin(getenv("HOME"), "/");
		chdir(str2);
		str3 = ft_strjoin("PWD=", str2);
		shell->str[i + 1] = str3;
		shell->str[i + 2] = NULL;
		ft_export();
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
