/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarihan <osarihan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:22:50 by osarihan          #+#    #+#             */
/*   Updated: 2022/10/07 11:49:44 by osarihan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_name(char *name)
{
	name = getenv("USER");
	name = ft_strjoin(name, "@minishell > ");
	return(name);
}

int	check_cmnd(char *str)
{
	if (ft_strcmp(str, "cd"))
		ft_cd(str);
	else if (ft_strcmp(str, "ls"))
		ft_ls(str);
	else if (ft_strcmp(str, "echo"))
		ft_echo(str);
	else if (ft_strcmp(str, "pwd"))
		ft_pwd(str);
	else if (ft_strcmp(str, "exit"))
		exit(0);
	else
		return(0);
	return (1);
}

int	ft_strcmp(char *asd, char *sda)
{
	int i;

	i = 0;
	while (sda[i] != '\0')
	{
		if (asd[i] == sda[i])
			i++;
		else
			return(0);
	}
	return(1);
}