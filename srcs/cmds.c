/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozcan <oozcan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 13:30:38 by oozcan            #+#    #+#             */
/*   Updated: 2022/12/19 18:05:02 by oozcan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(void)
{
	t_list	*tmp;
	t_list	*iter;

	if (!g_shell->ctrl)
	{
		ft_fill();
		g_shell->ctrl++;
	}
	tmp = g_shell->asd;
	while (tmp != NULL)
	{
		iter = tmp;
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
	g_shell->exit_status = 0;
	return (1);
}

void	ft_pwd(void)
{
	char	*pwd;
	if (!g_shell->asd)
		ft_fill();
	pwd = check_env(ft_strdup("PWD"));
	printf("%s\n", pwd);
	free(pwd);
	g_shell->exit_status = 0;
}

void	ft_echo_n(t_list *list, int i)
{
	if (list_data(list, i) == NULL)
		return ;
	while (ft_strcmp(list_data(list, i), "-n"))
	{
		if (list_data(list, i) != NULL)
			i++;
		if (list_data(list, i) == NULL)
			return ;
	}
	while (list_data(list, i) != NULL)
	{
		if (list_data(list, i + 1) == NULL)
			printf("%s", list_data(list, i));
		else
			printf("%s ", list_data(list, i));
		i++;
	}
}

void	ft_echo(t_list *list)
{
	int (i) = 1;
	if (list_data(list, i) == NULL)
		printf("\n");
	else
	{
		if (!ft_strcmp(list_data(list, i), "-n"))
		{
			while (list_data(list, i) != NULL)
			{
				if (list_data(list, i + 1) == NULL)
					printf("%s\n", list_data(list, i));
				else
					printf("%s ", list_data(list, i));
				i++;
			}
		}
		else
			ft_echo_n(list, ++i);
	}
	g_shell->exit_status = 0;
}

void	ft_exit(t_list *list)
{
	if (list->next != NULL)
	{
		list = list->next;
		g_shell->exit_status = ft_atoi(list->content);
	}
	exit(g_shell->exit_status);
}
