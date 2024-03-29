/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_all.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarihan <osarihan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:42:56 by oozcan            #+#    #+#             */
/*   Updated: 2022/12/22 15:50:35 by osarihan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *asd, char *sda)
{
	int		i;
	size_t	len;

	len = ft_strlen(sda);
	i = 0;
	while (len)
	{
		if (asd[i] == sda[i])
			i++;
		else
			return (0);
		len--;
	}
	if (asd[i] != '\0')
		return (0);
	return (1);
}

int	ft_strcmp2(char *asd, char *sda)
{
	int		i;
	size_t	len;

	len = ft_strlen(sda);
	i = 0;
	while (len)
	{
		if (asd[i] == sda[i])
			i++;
		else
			return (0);
		len--;
	}
	if (asd[i] == '=')
		return (1);
	else
	{
		printf("minishell: unset: `%s': not a valid identifier\n", asd);
		return (0);
	}
}

int	ft_strcmp3(char *asd, char *sda)
{
	int		i;

	i = 0;
	while (asd[i] != '\0')
	{
		if (asd[i] == '=' && sda[i] == '=')
			return (1);
		if (asd[i] == sda[i])
			i++;
		else
			return (0);
	}
	return (1);
}
