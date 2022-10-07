/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmnds.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarihan <osarihan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:17:35 by osarihan          #+#    #+#             */
/*   Updated: 2022/10/07 15:59:59 by osarihan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char *str)
{
	char *tmp;
	int	i;

	str = str + 3;
	if (ft_strcmp(str, "..") == 1)
	{
		tmp = getenv("OLDPATH");
		i = chdir(tmp);
		//tmp = getenv("PWD");
		//printf("%s\n", tmp);
	}
	else
	{
		tmp = getenv(ft_strjoin("/", str));
		i = chdir(tmp);
		printf("%s\n", tmp);
	}
	return(1);
}

int	ft_ls(char *str)
{
	if (str)
		return(1);
	return(1);
}

int	ft_echo(char *str)
{
	str = str + 4;
	if (*str == ' ')
	{
		str++;
		if (ft_strcmp(str, "-n") == 1)
		{
			str = str + 3;
			printf("%s", str);	
		}
		else
			printf("%s\n", str);
	}
	return(1);
}

int	ft_pwd()
{
	char *tmp;

	tmp = getenv("PWD");
	printf("%s\n", tmp);
	return(1);	
}

int ft_env(void)
{
	int i;
	extern char **environ;
	int j;

	i = 0;
	j = 0;
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
	return (1);
}
