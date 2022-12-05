/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarihan <osarihan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:13:41 by osarihan          #+#    #+#             */
/*   Updated: 2022/12/02 10:28:15 by osarihan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int token_compr(void)
{
	int i = 0;
	if (shell->line[i] == '>' || shell->line[i] == '<' || shell->line[i] == '|')
	{
		if ((shell->line[i] == '>' && shell->line[i + 1] == '>') || (shell->line[i] == '<' && shell->line[i + 1] == '<'))
		{
			if (shell->line[i + 2] == '>' || shell->line[i + 2] == '<')
			{
				write(2, "minishell: parse error near '<'\n", 33);
				return (-1);
			}
			else
				return(2);
		}
		else if (shell->line[i] == '|' && shell->line[i + 1] == '|')
		{
			write(2, "minishell: syntax error near expected token '|'\n", 49);
			return (-1);
		}
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
			while (shell->line[i] != ' ' && shell->line[i] != '\0')
				i++;
			return (i);
		}
		if (shell->line[i] == 39)
		{
			i++;
			while (shell->line[i] != 39 && shell->line[i] != '\0')
				i++;
			while (shell->line[i] != ' ' && shell->line[i] != '\0')
				i++;
			return (i);
		}
		i++;
	}
	return (i);
}

void	lexur(int cnt)
{
	char *tmp;
	int i = 0;

	tmp = malloc(sizeof(char *) * cnt + 1);
	while (cnt > 0)
	{
		tmp[i] = *shell->line;
		shell->line++;
		cnt--;
		i++;
	}
	tmp[i] = '\0';
	ft_lstadd_back(&shell->arg, ft_lstnew(tmp));
}

void	space_skip()
{
	int	i;

	i = 0;
	while (shell->line[i] <= 32 && shell->line[i + 1] != '\0')
		shell->line++;
	if (shell->line[i] <= 32 && shell->line[i + 1] == '\0')
	{
		*shell->line = '\0';
		return ;
	}
}


int	cmnd_take(void)
{
	int i = 0;

	if (shell->line[0] == '|')
	{
		write(2, "minishell: syntax error near unexpected token `|'\n", 51);
		return (-1);
	}
	while ((shell->line[i] != ' ' && shell->line[i] != '\0') && (shell->line[i] != '>' && shell->line[i] != '<' && shell->line[i] != '|'))
		i++;
	return(i);
}

void cmnd_cut(int x)
{
	char *tmp;
	int i;

	i = 0;
	tmp = malloc(sizeof(char *) * x);
	while (*shell->line > 32)
	{
		if (*shell->line == 34 || *shell->line == 39)
			shell->line++;
		else if (*shell->line != ' ' && *shell->line != '\0' && *shell->line != '>' && *shell->line != '<' && *shell->line != '|')
		{
			tmp[i] = *shell->line;
			shell->line++;
			i++;
		}
		else
			break;
	}
	tmp[i] = '\0';
	if (tmp[0] != '\0')
		ft_lstadd_back(&shell->arg, ft_lstnew(tmp));
}
