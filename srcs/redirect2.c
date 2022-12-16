/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozcan <oozcan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:06:51 by oozcan            #+#    #+#             */
/*   Updated: 2022/12/16 18:07:02 by oozcan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	right_redirect(int index)
{
	int	fd;
	int	pid;

	g_shell->to_open = list_data(g_shell->arg, index + 1);
	cut_redirect(index);
	fd = open(g_shell->to_open, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
		return ;
	dup2(fd, 1);
	close (fd);
}

void	left_redirect(int index)
{
	int	fd;
	int	pid;

	g_shell->to_open = list_data(g_shell->arg, index + 1);
	cut_redirect(index);
	fd = open(g_shell->to_open, O_RDWR, 0777);
	if (fd < 0)
		return ;
	dup2(fd, 0);
	close(fd);
}

void	double_right_redirect(int index)
{
	int	fd;
	int	pid;

	g_shell->to_open = list_data(g_shell->arg, index + 1);
	cut_redirect(index);
	fd = open(g_shell->to_open, O_RDWR | O_APPEND, 0777);
	if (fd < 0)
		return ;
	dup2(fd, 1);
	close (fd);
}
