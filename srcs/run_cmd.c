/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozcan <oozcan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:59:35 by oozcan            #+#    #+#             */
/*   Updated: 2022/12/19 18:14:30 by oozcan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_cmd(t_list *list)
{
	if (!ft_strcmp(list->content, "CD"))
		to_lower(list, list->content);
	if (ft_strcmp(list->content, "cd")) // leak
		ft_cd(list);
	else if (ft_strcmp(list->content, "export"))
		ft_export(list);
	else if (ft_strcmp(list->content, "unset"))
		ft_unset(list);
	else if (ft_strcmp(list->content, "echo"))
		ft_echo(list);
	else if (ft_strcmp(list->content, "pwd"))
		ft_pwd();
	else if (ft_strcmp(list->content, "env"))
		ft_env();
	else if (ft_strcmp(list->content, "exit")) //leak
		ft_exit(list);
	else
		other_cmnds(list_to_2d(list));
}
