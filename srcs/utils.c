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

char	*get_name(char *name)
{
	name = getenv("USER");
	name = ft_strjoin(name, "\033[0;32m@minishell -> ");
	return(name);
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

int	ft_strcmp(char *asd, char *sda)
{
	int i;
	size_t len;

	len = ft_strlen(sda);
	i = 0;
	while (len)
	{
		if (asd[i] == sda[i])
			i++;
		else
			return(0);
		len--;
	}
	if (asd[i] != '\0')
		return(0);
	return(1);
}

int	ft_strcmp2(char *asd, char *sda)
{
	int	i;
	size_t len;

	len = ft_strlen(sda);
	i = 0;
	while (len)
	{
		if (asd[i] == sda[i])
			i++;
		else
			return(0);
		len--;
	}
	if (asd[i] == '=')
		return(1);
	else
	{
		printf("minishell: unset: `%s': not a valid identifier\n", asd);
		return(0);
	}
}

int	ft_strcmp3(char *asd, char *sda)
{
	int	i;
	size_t len;

	i = 0;
	while (asd[i] != '\0')
	{
		if (asd[i] == '=' && sda[i] == '=')
			return(1);
		if (asd[i] == sda[i])
			i++;
		if (asd[i] == '=' && sda[i] == '=')
			return(1);
		// else if (asd[i] != sda[i] && asd[i - 1] == '=' && sda[i - 1] == '=')
		// {
		// 	return(1);
		// }
		else
		{
			//printf("ben sifiriimm\n");
			return (0);
		}
	}
	return(1);
	//if (ft_strchr(asd, '='))
	//	return(1);
	//else
	//{
	//	printf("minishell: export: `%s': not a valid identifier\n", asd);
	//	return(0);
	//}
}

