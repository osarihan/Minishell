/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozcan <oozcan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:50:18 by oozcan            #+#    #+#             */
/*   Updated: 2022/12/16 17:50:38 by oozcan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_counter(void)
{
	t_list	*iter;

	iter = g_shell->arg;
	g_shell->pipe = 0;
	while (iter != NULL)
	{
		if (ft_strcmp(iter->content, "|"))
			g_shell->pipe++;
		iter = iter->next;
	}
}

void	run_cmd_with_pipe(void)
{
	pipe_counter();
	pipe_f();
}
