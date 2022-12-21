/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozcan <oozcan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:01:15 by oozcan            #+#    #+#             */
/*   Updated: 2022/12/21 17:36:32 by oozcan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fill(void)
{
	int (i) = 0;
	g_shell->asd = NULL;
	while (g_shell->environ[i] != NULL)
	{
		ft_lstadd_back(&g_shell->asd, \
			ft_lstnew(ft_strdup(g_shell->environ[i])));
		i++;
	}
	ultimate_alpha_index_finder();
}

void	reset_stdin(void)
{
	dup2(g_shell->saved_stdin, STDIN_FILENO);
	close(g_shell->saved_stdin);
}

void	reset_stdout(void)
{
	dup2(g_shell->saved_stdout, STDOUT_FILENO);
	close(g_shell->saved_stdout);
}

void	get_name(void)
{
	g_shell->name = getenv("USER");
	g_shell->name = ft_strjoin(g_shell->name, "\033[0;32m@minishell -> \033[0m");
}

void	to_lower(t_list *list, char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] >= 'A' && cmd[i] <= 'Z')
			cmd[i] += 32;
		i++;
	}
	list->content = ft_strdup(cmd);
	free(cmd);
}
