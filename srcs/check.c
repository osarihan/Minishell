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
	if (k % 2 == 0 && l % 2 == 0)
		return (1);
	else
	{
		printf("unexpected quote behavior\n");
		return (0);
	}
}
