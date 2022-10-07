/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmnds.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarihan <osarihan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:17:35 by osarihan          #+#    #+#             */
/*   Updated: 2022/10/07 12:00:08 by osarihan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char *str)
{
	char *tmp;

	if (str)
	{
		tmp = getenv("PWD");
		chdir("./");
		tmp = getenv("PWD");
		printf("%s\n", tmp);
	}
	//if (ft_strcmp(str, "cd .."))
	//{
	//	return(0);
	//}
	//if (str)
	//	return(1);
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