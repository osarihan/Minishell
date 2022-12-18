/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozcan <oozcan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:08:55 by oozcan            #+#    #+#             */
/*   Updated: 2022/12/18 15:57:21 by oozcan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	space_skip(void)
{
	int	i;

	i = 0;
	while (g_shell->line[i] <= 32 && g_shell->line[i + 1] != '\0')
		g_shell->line++;
	if (g_shell->line[i] <= 32 && g_shell->line[i + 1] == '\0')
	{
		*g_shell->line = '\0';
		return ;
	}
}

int	cmnd_take(void)
{
	int (i) = 0;
	if (g_shell->line[0] == '|')
	{
		write(2, "minishell: syntax error near unexpected token `|'\n", 51);
		return (-1);
	}
	while ((g_shell->line[i] != ' ' && g_shell->line[i] != '\0') && \
			(g_shell->line[i] != '>' && g_shell->line[i] != '<' \
				&& g_shell->line[i] != '|'))
	{
		i++;
	}
	return (i);
}

void	lexur(int cnt)
{
	char	*tmp;

	int (i) = 0;
	tmp = malloc(sizeof(char *) * cnt + 1);
	while (cnt > 0)
	{
		tmp[i] = *g_shell->line;
		g_shell->line++;
		cnt--;
		i++;
	}
	tmp[i] = '\0';
	ft_lstadd_back(&g_shell->arg, ft_lstnew(tmp));
}

int	lexer_cnt(int cnt, int i)
{
	if (i == 1)
	{
		if (cnt > 0)
			lexur(cnt);
		else if (cnt == -1)
			return (0);
	}
	else if (i == 2)
	{
		if (cnt > 0)
			lexur(cnt);
	}
	return (1);
}

int	lexer(void)
{
	int (cnt) = 0;
	char *(tmp) = g_shell->line;
	while (*g_shell->line)
	{
		space_skip();
		if (g_shell->arg == NULL || \
			ft_strcmp("|", ft_lstlast(g_shell->arg)->content))
		{
			cnt = cmnd_take();
			if (cnt == -1)
				return (0);
			else if (cnt > 0)
			{
				cmnd_cut(cnt);
				continue ;
			}
		}
		cnt = token_compr();
		if (lexer_cnt(cnt, 1) == 0)
			return (0);
		cnt = text_cmpr();
		lexer_cnt(cnt, 2);
	}
	free(tmp);
	return (1);
}
