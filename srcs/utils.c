/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarihan <osarihan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:22:50 by osarihan          #+#    #+#             */
/*   Updated: 2022/10/25 14:12:12 by osarihan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_name(char *name)
{
	name = getenv("USER");
	name = ft_strjoin(name, "@minishell -> ");
	return(name);
}

int	check_cmnd(t_shell *shell, int i)
{
	shell->str[i] = to_lower(shell->str[i]);
	if (ft_strcmp(shell->str[i], "cd"))
		ft_cd(shell, i);
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
	{
		i++;
		return (0);
	}
	return (1);
}

int	check_cmnd_pipe(t_shell *shell, int i)
{
	shell->str_pipe[i] = to_lower(shell->str_pipe[i]);
	if (ft_strcmp(shell->str_pipe[i], "cd"))
		ft_cd(shell, i);
	else if (ft_strcmp(shell->str_pipe[i], "pwd") || \
					ft_strcmp(shell->str_pipe[i], "PWD"))
		ft_pwd();
	else if (ft_strcmp(shell->str_pipe[i], "env"))
		ft_env();
	else if (ft_strcmp(shell->str_pipe[i], "exit"))
		exit(0);
	else if (other_cmnds(shell->str_pipe))
		return (1);
	else
	{
		i++;
		return (0);
	}
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
		printf("%c", str[i]);
		i++;
	}
	return (str);
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
