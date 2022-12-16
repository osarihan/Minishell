/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_quote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozcan <oozcan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 13:45:59 by oozcan            #+#    #+#             */
/*   Updated: 2022/12/16 17:45:14 by oozcan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	d_quote(int index)
{
	char	*content;
	char	*tmp;
	char	*rtn_dollar;
	char	*iter_tmp;

	int (i) = 0;
	int (j) = 0;
	tmp = malloc(10000);
	ft_bzero(tmp, 10000);
	content = list_data(g_shell->arg, index);
	while (content[i])
	{
		if (content[i] == D_QUOTE)
			i++;
		if (content[i] == '$')
		{
			rtn_dollar = dollar_sign(ft_strdup(content), ++i);
			iter_tmp = rtn_dollar;
			while (content[i] != 32 && content[i] != '$' && content[i] != '\0' \
					&& content[i] != D_QUOTE && content[i] != S_QUOTE)
				i++;
			while (*rtn_dollar)
			{
				tmp[j] = (*rtn_dollar);
				rtn_dollar++;
				j++;
			}
			tmp[j] = '\0';
		}
		else
		{
			tmp[j] = content[i];
			i++;
			j++;
		}
	}
	if (iter_tmp[0] > 32)
		free(iter_tmp);
	tmp[j] = '\0';
	list_f_data(g_shell->arg, index)->content = ft_strdup(tmp);
	free(tmp);
	free(content);
}
