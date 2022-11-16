/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozcan <oozcan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:22:50 by osarihan          #+#    #+#             */
/*   Updated: 2022/11/01 13:13:39 by oozcan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_name()
{
	shell->name = getenv("USER");
	shell->name = ft_strjoin(shell->name, "\033[0;32m@minishell -> ");
}

int	check_cmnd(int i)
{
	if (!ft_strcmp(shell->str[i], "CD"))
		shell->str[i] = to_lower(shell->str[i]);
	if (ft_strcmp(shell->str[i], "cd"))
		ft_cd(shell->str, i);
	else if (ft_strcmp(shell->str[i], "export"))
		ft_export();
	else if (ft_strcmp(shell->str[i], "unset"))
		ft_unset();
	else if (ft_strcmp(shell->str[i], "echo"))
		ft_echo(shell->str, i);
	else if (ft_strcmp(shell->str[i], "pwd") || \
					ft_strcmp(shell->str[i], "PWD"))
		ft_pwd();
	else if (ft_strcmp(shell->str[i], "env"))
		ft_env();
	else if (ft_strcmp(shell->str[i], "exit"))
		exit(0);
	else if (other_cmnds(shell->str))
		return (1);
	else
		return (0);
	return (1);
}

char *to_lower(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
		i++;
	}
	return (str);
}
