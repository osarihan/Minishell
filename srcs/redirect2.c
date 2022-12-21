/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozcan <oozcan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:06:51 by oozcan            #+#    #+#             */
/*   Updated: 2022/12/21 18:02:57 by oozcan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redirect_cntr(void)
{
	t_list	*iter;

	int (redc) = 0;
	int (index) = 0;
	iter = g_shell->arg;
	while (iter != NULL)
	{
		if (ft_strcmp(list_data(g_shell->arg, index), ">") || \
			ft_strcmp(list_data(g_shell->arg, index), ">>") || \
				ft_strcmp(list_data(g_shell->arg, index), "<") || \
					ft_strcmp(list_data(g_shell->arg, index), "<<"))
		{
			redc++;
			index++;
		}
		else
			index++;
		iter = iter->next;
	}
	return (redc - 1);
}

void	right_redirect(int index, int r_c)
{
	int	fd;
	int	pid;

	while (r_c > 0)
	{
		fd = open (list_data(g_shell->arg, index + 1), \
			O_RDWR | O_CREAT | O_TRUNC, 0777);
		close (fd);
		cut_redirect(index);
		r_c--;
	}
	g_shell->to_open = list_data(g_shell->arg, index + 1);
	cut_redirect(index);
	fd = open(g_shell->to_open, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
		return ;
	dup2(fd, 1);
	close (fd);
}

void	left_redirect(int index, int r_c)
{
	int	fd;
	int	pid;

	while (r_c > 0)
	{
		fd = open (list_data(g_shell->arg, index + 1), \
			O_RDWR | O_CREAT | O_TRUNC, 0777);
		close (fd);
		index += 2;
		r_c--;
	}
	g_shell->to_open = list_data(g_shell->arg, index + 1);
	cut_redirect(index);
	fd = open(g_shell->to_open, O_RDWR, 0777);
	if (fd < 0)
	{
		printf("dosya yok\n") ;
		exit(0);
	}
	dup2(fd, 0);
	close(fd);
}

void	double_right_redirect(int index, int r_c)
{
	int	fd;
	int	pid;

	while (r_c > 0)
	{
		fd = open (list_data(g_shell->arg, index + 1), \
			O_RDWR | O_CREAT | O_TRUNC, 0777);
		close (fd);
		index += 2;
		r_c--;
	}
	g_shell->to_open = list_data(g_shell->arg, index + 1);
	cut_redirect(index);
	fd = open(g_shell->to_open, O_RDWR | O_APPEND, 0777);
	if (fd < 0)
		return ;
	dup2(fd, 1);
	close (fd);
}
