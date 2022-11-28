/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarihan <osarihan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:13:41 by osarihan          #+#    #+#             */
/*   Updated: 2022/11/28 16:12:00 by osarihan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *asd, char *sda)
{
	int i;
	size_t len;

	len = ft_strlen(sda);
	i = 0;
	while (len)
	{
		if (asd[i] == sda[i])
			i++;
		else
			return(0);
		len--;
	}
	if (asd[i] != '\0')
		return(0);
	return(1);
}

int	token_compr(void)
{
	int i = 0;
	if (shell->line[i] == '>' || shell->line[i] == '<' || shell->line[i] == '|')
	{
		if ((shell->line[i] == '>' && shell->line[i + 1] == '>') || (shell->line[i] == '<' && shell->line[i + 1] == '<'))
			return(2);
		else
			return (1);
	}
	return(0);
}

int	text_cmpr(void)
{
	int i = 0;
	
	while ((shell->line[i] != ' ' && shell->line[i] != '\0') && (shell->line[i] != '>' && shell->line[i] != '<' && shell->line[i] != '|'))
	{
		if (shell->line[i] == 34)
		{
			i++;
			while (shell->line[i] != 34 && shell->line[i] != '\0')
				i++;
			return (i + 1);
		}
		if (shell->line[i] == 39)
		{
			i++;
			while (shell->line[i] != 39 && shell->line[i] != '\0')
				i++;
			return (i + 1);
		}
		i++;
	}
	return (i);
}

void	lexur(int cnt)
{
	char *tmp;
	int i = 0;

	tmp = malloc(sizeof(char *) * cnt);
	while (cnt > 0)
	{
		tmp[i] = *shell->line;
		shell->line++;
		cnt--;
		i++;
	}
	ft_lstadd_back(&shell->arg, ft_lstnew(tmp));	
}

void	space_skip()
{
	while (*shell->line <= 32)
		shell->line++;
}

int	cmnd_take(void)
{
	int i = 0;

	while ((shell->line[i] != ' ' && shell->line[i] != '\0') && (shell->line[i] != '>' && shell->line[i] != '<' && shell->line[i] != '|'))
		i++;
	return(i);
}
