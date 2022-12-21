/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmnds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozcan <oozcan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:48:46 by oozcan            #+#    #+#             */
/*   Updated: 2022/12/21 17:37:12 by oozcan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**list_to_2d(t_list *list)
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
	return (str);
}

void	exec(char *path, char **arg)
{
	char	**env;

	env = list_to_2d(g_shell->asd);
	if (execve(path, arg, env) == -1)
	{
		reset_stdout();
		printf("%s: command not found.\n", arg[0]);
		free(path);
		exit(127);
	}
}

char	*f_path(char **arg)
{
	char	**path;
	char	*path_tmp;

	int (i) = 0;
	path_tmp = check_env(ft_strdup("PATH"));
	if (!path_tmp)
		printf("%s: No such file or directory\n", arg[0]);
	if (arg[0][0] == '.')
		path_tmp = ft_strjoin(path_tmp, ":./");
	else if (access(arg[0], F_OK) == 0)
		return (arg[0]);
	path = ft_split(path_tmp, ':');
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], arg[0]);
		if (access(path[i], F_OK) == 0)
			break ;
		i++;
	}
	return (path[i]);
}

void	other_cmnds(char **arg)
{
	int	pid;
	int	i;
	int	ret;

	i = 0;
	pid = fork();
	if (pid == 0)
		exec(f_path(arg), arg);
	waitpid(pid, &ret, 0);
	g_shell->exit_status = ret % 255;
	wait(NULL);
	while (arg[i])
	{
		free(arg[i]);
		i++;
	}
	free(arg);
}
