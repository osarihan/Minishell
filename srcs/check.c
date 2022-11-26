/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozcan <oozcan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 13:44:54 by oozcan            #+#    #+#             */
/*   Updated: 2022/11/01 14:10:08 by oozcan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*quote(const char *str, int c)
{
	char	*new_str;
	int	i = 0;
	int	j = 0;

	int	quote = 1;

	new_str = malloc(ft_strlen(str) + 1);
	new_str[j] = str[i];
	j++;
	i++;
	while(str[i] != '\0' && shell->d_quote != quote)
	{
		if (str[i] == c && shell->d_quote != quote)
		{
			quote++;
			i++;
			continue;
		}
		new_str[j] = str[i];
		j++;
		i++;
	}
	new_str[j++] = c;
	new_str[j] = '\0';
	return (new_str);
}

int	quote_check(char *str)
{
	int	i = 0;
	int	k = 0;
	int	l = 0;

	while (str[i])
	{
		if (str[i] == 39)
			k++;
		if (str[i] == 34)
			l++;
		i++;
	}
	shell->s_quote = k;
	shell->d_quote = l;
	if (k % 2 == 0 && l % 2 == 0)
		return (1);
	else
	{
		printf("unexpected quote behavior\n");
		return (0);
	}
}
