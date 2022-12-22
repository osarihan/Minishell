/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarihan <osarihan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:16:09 by oozcan            #+#    #+#             */
/*   Updated: 2022/12/22 15:51:57 by osarihan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_exit(int fd, char *eof, char *to_write)
{
	close(fd);
	free(eof);
	free(to_write);
	exit (0);
}

int	lstcmp2(t_list *iter, char *str)
{
	t_list	*temp;

	temp = iter;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->content, str))
			return (0);
		temp = temp->next;
	}
	return (1);
}

void	ft_dstry_node_for_red(t_list *iter, int c)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = iter;
	tmp2 = iter;
	if (c == 0)
		iter = NULL;
	while (c > 1 && tmp != NULL)
	{
		if (tmp->next != NULL)
			tmp = tmp->next;
		c--;
	}
	if (tmp->next->next != NULL)
		tmp2 = tmp->next->next;
	else
		tmp2 = NULL;
	if (tmp2 != NULL)
		tmp->next = tmp2;
	else
		tmp->next = NULL;
}

void	ft_dstry_node2(t_list *iter, int c)
{
	t_list *(cleaner);
	t_list *(tmp) = iter;
	t_list *(tmp2) = iter;
	if (c == 0)
		iter = NULL;
	while (c > 1 && tmp != NULL)
	{
		if (tmp->next != NULL)
			tmp = tmp->next;
		c--;
	}
	cleaner = tmp->next;
	if (cleaner)
	{
		free(cleaner->content);
		free(cleaner);
	}
	if (tmp->next->next != NULL)
		tmp2 = tmp->next->next;
	else
		tmp2 = NULL;
	if (tmp2 != NULL)
		tmp->next = tmp2;
	else
		tmp->next = NULL;
}
