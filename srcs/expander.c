/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarihan <osarihan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:11:32 by oozcan            #+#    #+#             */
/*   Updated: 2022/12/22 15:49:41 by osarihan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand(int index)
{
	char *(tmp) = ft_calloc(10000, sizeof(char));
	char *(content) = list_data(g_shell->arg, index);
	int (i) = 0;
	size_t (j) = 0;
	while (content[i])
	{
		if (content[i] == '$')
		{
			tmp = ft_strjoin3(tmp, dollar_sign(ft_strdup(content), ++i));
			while (content[i] != 32 && content[i] != '$' && content[i] != '\0')
				i++;
			while (j < ft_strlen(tmp))
				++j;
		}
		if (content[i] == '$')
			continue ;
		tmp[j] = content[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	list_f_data(g_shell->arg, index)->content = ft_strdup(tmp);
	free(content);
	free(tmp);
}

int	quote_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == D_QUOTE)
			return (D_QUOTE);
		else if (str[i] == S_QUOTE)
			return (S_QUOTE);
		i++;
	}
	return (0);
}

void	expander(void)
{
	t_list	*iter;
	char	*content;
	int		quote_status;
	int		index;

	index = 0;
	iter = g_shell->arg;
	while (iter != NULL)
	{
		content = ft_strdup(iter->content);
		quote_status = quote_check(content);
		if (quote_status == S_QUOTE)
			s_quote(index);
		else if (quote_status == D_QUOTE)
			d_quote(index);
		else
			expand(index);
		iter = iter->next;
		index++;
		free(content);
	}
}
