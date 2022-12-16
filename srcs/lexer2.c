/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozcan <oozcan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:13:41 by osarihan          #+#    #+#             */
/*   Updated: 2022/12/16 18:10:22 by oozcan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_compr(void)
{
	int (i) = 0;
	if (g_shell->line[i] == '>' || g_shell->line[i] == '<' \
		|| g_shell->line[i] == '|')
	{
		if ((g_shell->line[i] == '>' && g_shell->line[i + 1] == '>') || \
				(g_shell->line[i] == '<' && g_shell->line[i + 1] == '<'))
		{
			if (g_shell->line[i + 2] == '>' || g_shell->line[i + 2] == '<')
			{
				write(2, "minishell: parse error near '<'\n", 33);
				return (-1);
			}
			else
				return (2);
		}
		else if (g_shell->line[i] == '|' && g_shell->line[i + 1] == '|')
		{
			write(2, "minishell: syntax error near expected token '|'\n", 49);
			return (-1);
		}
		else
			return (1);
	}
	return (0);
}

int	text_cmpr(void)
{
	int (i) = 0;
	while ((g_shell->line[i] != ' ' && g_shell->line[i] != '\0') && \
		(g_shell->line[i] != '>' && g_shell->line[i] != '<' \
			&& g_shell->line[i] != '|'))
	{
		if (g_shell->line[i] == 34)
		{
			i++;
			while (g_shell->line[i] != 34 && g_shell->line[i] != '\0')
				i++;
			while (g_shell->line[i] != ' ' && g_shell->line[i] != '\0')
				i++;
			return (i);
		}
		if (g_shell->line[i] == 39)
		{
			i++;
			while (g_shell->line[i] != 39 && g_shell->line[i] != '\0')
				i++;
			while (g_shell->line[i] != ' ' && g_shell->line[i] != '\0')
				i++;
			return (i);
		}
		i++;
	}
	return (i);
}

void	cmnd_cut(int x)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char *) * x);
	while (*g_shell->line > 32)
	{
		if (*g_shell->line == 34 || *g_shell->line == 39)
			g_shell->line++;
		else if (*g_shell->line != ' ' && *g_shell->line != '\0' \
				&& *g_shell->line != '>' && *g_shell->line != '<' \
					&& *g_shell->line != '|')
		{
			tmp[i] = *g_shell->line;
			g_shell->line++;
			i++;
		}
		else
			break ;
	}
	tmp[i] = '\0';
	if (tmp[0] != '\0')
		ft_lstadd_back(&g_shell->arg, ft_lstnew(tmp));
}
