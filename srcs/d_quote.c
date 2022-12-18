/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_quote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozcan <oozcan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 13:45:59 by oozcan            #+#    #+#             */
/*   Updated: 2022/12/18 14:46:48 by oozcan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*d_quote_loop(char *content, char *tmp, char *rtn_dollar, char *itr_tmp)
{
	int (i) = 0;
	int (j) = 0;
	while (content[i])
	{
		if (content[i] == D_QUOTE)
			i++;
		if (content[i] == '$')
		{
			rtn_dollar = dollar_sign(ft_strdup(content), ++i);
			itr_tmp = rtn_dollar;
			while (content[i] != 32 && content[i] != '$' && content[i] != '\0' \
					&& content[i] != D_QUOTE && content[i] != S_QUOTE)
				i++;
			while (*rtn_dollar)
				tmp[j++] = (*rtn_dollar++);
			tmp[j] = '\0';
		}
		else
			tmp[j++] = content[i++];
	}
	// if (itr_tmp[0] > 32)
	// 	free(itr_tmp);
	free(content);
	return (tmp);
}

void	d_quote(int index)
{
	char	*content;
	char	*tmp;
	char	*rtn_dollar;
	char	*itr_tmp;

	tmp = malloc(10000);
	ft_bzero(tmp, 10000);
	content = list_data(g_shell->arg, index);
	tmp = d_quote_loop(content, tmp, rtn_dollar, itr_tmp);
	//tmp[j] = '\0';
	list_f_data(g_shell->arg, index)->content = ft_strdup(tmp);
	free(tmp);
	//free(content);
}
