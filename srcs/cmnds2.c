/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmnds2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarihan <osarihan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:00:08 by osarihan          #+#    #+#             */
/*   Updated: 2022/10/07 16:39:45 by osarihan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(char *str)
{
	str += 7;
	if (str)
		return(1);
	return(1);
}

char	*ft_maqas(char const *s1, char const set)
{
	int	i;
	int j;
	int len;
	char *new;

	i = 0;
	j = 0;
	len = ft_strlen(s1);
	new = malloc(sizeof(char *) * len);
	if (*s1 == set)
		i++;
	while (s1[i] != set)
	{
		new[j] = s1[i];
		i++;
		j++;
	}
	return(new);
}