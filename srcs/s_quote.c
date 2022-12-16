/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_quote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozcan <oozcan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:00:40 by oozcan            #+#    #+#             */
/*   Updated: 2022/12/16 18:00:46 by oozcan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	s_quote(int index)
{
	char	*content;
	char	*tmp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	tmp = malloc(10000);
	content = list_data(g_shell->arg, index);
	while (content[i])
	{
		if (content[i] == S_QUOTE)
			i++;
		tmp[j] = content[i];
		j++;
		i++;
	}
	list_f_data(g_shell->arg, index)->content = ft_strdup(tmp);
	free(tmp);
	free(content);
}
